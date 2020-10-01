//
// Created by Alan Freitas on 30/09/20.
//

#include <algorithm>
#include <cassert>

#include "mdsplitter.h"

namespace mdsplit {

    int mdsplitter::run() {
        fs::create_directory(output_dir_);

        std::cout << "# Find Sections" << std::endl;
        find_sections();

        if (remove_autotoc_) {
            std::cout << "\n# Remove Auto TOC" << std::endl;
            remove_auto_toc();
        }

        if (clear_html_tags_.empty()) {
            std::cout << "\n# Remove HTML Tags" << std::endl;
            remove_html_tags();
        }

        if (update_links_) {
            std::cout << "\n# Update Links" << std::endl;
            run_update_links();
        }

        if (include_toc_) {
            std::cout << "\n# Create Subsection links" << std::endl;
            create_subsection_links();
        }

        if (jekyll_escape_) {
            std::cout << "\n# Escape Jekyll" << std::endl;
            escape_jekyll();
        }

        if (indent_headers_) {
            std::cout << "\n# Reindent Headers" << std::endl;
            reindent_headers();
        }

        if (add_front_matter_) {
            std::cout << "\n# Add Front Matter" << std::endl;
            run_add_front_matter();
        }

        std::cout << "\n# Save Sections" << std::endl;
        save_sections();

        list_doc_outsiders();

        return 0;
    }

    std::string mdsplitter::slugify(std::string_view str) {
        std::string r;
        for (const auto &c : str) {
            if ((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '-') {
                r += c;
            } else if (c >= 'A' && c <= 'Z') {
                r += std::tolower(c);
            } else if (c == ' ') {
                r += '-';
            }
        }
        return r;
    }

    void mdsplitter::find_sections() {
        // # some text
        std::regex header_regex{"(#+) +(.*)"};

        std::regex ignore_begin_regex{R"(<!-- START mdsplit-ignore -->)"};
        std::regex ignore_end_regex{R"(<!-- END mdsplit-ignore -->)"};

        /*
         * # some text
         * std::regex h1_regex{"# +(.*)"};
         * // ## some text
         * std::regex h2_regex{"## +(.*)"};
         * // ### some text
         * std::regex h3_regex{"### +(.*)"};
         */
        std::ifstream fin(input_);

        std::string current_line;
        bool inside_codeblock = false;
        bool inside_ignoreblock = false;

        while (std::getline(fin, current_line)) {
            std::smatch sm;

            if (is_codeblock(current_line)) {
                inside_codeblock = 1 - inside_codeblock;
            }

            if (!inside_codeblock) {
                if (std::regex_match(current_line, ignore_begin_regex)) {
                    inside_ignoreblock = true;
                    continue;
                } else if (std::regex_match(current_line, ignore_end_regex)) {
                    inside_ignoreblock = false;
                    continue;
                } else if (inside_ignoreblock) {
                    continue;
                }

                bool found_header =
                    std::regex_search(current_line, sm, header_regex);
                if (found_header) {
                    short level = sm[1].length();
                    if (level <= max_split_level_) {
                        // Create new section
                        mdsection new_section;
                        new_section.level = level;
                        new_section.header_name = sm[2].str();
                        for (int i = new_section.level - 1; i > 1; --i) {
                            auto it = std::find_if(sections_.rbegin(),
                                                   sections_.rend(),
                                                   [&i](const mdsection &s) {
                                                       return s.level == i;
                                                   });
                            if (it != sections_.rend()) {
                                new_section.parent_headers.insert(
                                    new_section.parent_headers.begin(),
                                    it->header_name);
                            }
                        }
                        if (sections_.empty()) {
                            new_section.filepath = output_dir_ / "index.md";
                        } else {
                            new_section.filepath = output_dir_;
                            for (const auto &parent_section :
                                 new_section.parent_headers) {
                                new_section.filepath /= slugify(parent_section);
                            }
                            new_section.filepath /=
                                slugify(new_section.header_name);
                            new_section.filepath += ".md";
                        }
                        fs::create_directory(
                            new_section.filepath.parent_path());
                        sections_.push_back(new_section);
                    }
                }
            }

            // Make sure there's at least one default section
            if (sections_.empty()) {
                mdsection new_section;
                new_section.level = 0;
                new_section.header_name = "";
                new_section.filepath = output_dir_ / "index.md";
                sections_.push_back(new_section);
            }

            // Store line
            sections_.back().lines.push_back(std::move(current_line));
        }
    }

    bool mdsplitter::is_codeblock(const std::string &str) {
        // ```
        std::regex codeblock_regex{"```(.*)"};

        std::smatch sm;
        std::regex_match(str, sm, codeblock_regex);
        return !sm.empty();
    }

    void mdsplitter::save_sections() {
        for (const auto &section : sections_) {
            std::ofstream fout(section.filepath);
            std::cout << "Saving " << section.filepath
                      << "(Section: " << section.header_name << ")"
                      << std::endl;
            for (const auto &line : section.lines) {
                fout << line << std::endl;
            }
            fout << std::endl;
            fout << std::endl;
            fout << "<!-- Generated with mdsplit: "
                    "https://github.com/alandefreitas/mdsplit -->"
                 << std::endl;
        }
    }
    void mdsplitter::remove_auto_toc() {
        std::regex toc_begin_regex{
            R"(<!-- START doctoc generated TOC please keep comment here to allow auto update -->)"};
        std::regex toc_end_regex{
            R"(<!-- END doctoc generated TOC please keep comment here to allow auto update -->)"};
        for (auto &section : sections_) {
            auto line_it = section.lines.begin();
            auto line_it_end = section.lines.end();
            auto toc_line_it = line_it_end;
            auto toc_line_it_end = line_it_end;
            bool in_codeblock = false;
            for (; line_it != line_it_end; ++line_it) {
                if (is_codeblock(*line_it)) {
                    in_codeblock = 1 - in_codeblock;
                }
                if (in_codeblock) {
                    continue;
                }
                bool found_toc_begin =
                    std::regex_search(*line_it, toc_begin_regex);
                if (found_toc_begin) {
                    toc_line_it = line_it;
                } else {
                    bool found_toc_end =
                        std::regex_search(*line_it, toc_end_regex);
                    if (found_toc_end) {
                        toc_line_it_end = line_it;
                        break;
                    }
                }
            }
            if (toc_line_it != line_it_end && toc_line_it_end != line_it_end) {
                std::cout << "Found Auto TOC in " << section.header_name
                          << std::endl;
                section.lines.erase(toc_line_it, std::next(toc_line_it_end));
            }
        }
    }
    void mdsplitter::remove_html_tags() {
        for (const auto &tag : clear_html_tags_) {
            std::string complete_html_tag_format =
                "< *" + tag + "( +[^>]*)?>(.*?)</ *" + tag + " *>";
            std::regex complete_html_tag_regex{complete_html_tag_format};
            std::string html_tag_format = "< */? *" + tag + "( +[^>]*)?>";
            std::regex html_tag_regex{html_tag_format};
            for (auto &section : sections_) {
                bool in_codeblock = false;
                for (auto &line : section.lines) {
                    if (is_codeblock(line)) {
                        in_codeblock = 1 - in_codeblock;
                    }
                    if (in_codeblock) {
                        continue;
                    }
                    std::smatch match;
                    while (std::regex_search(line, match,
                                             complete_html_tag_regex)) {
                        std::cout << match[0] << "->" << match[2] << std::endl;
                        line.replace(match.position(0), match[0].length(),
                                     match[2]);
                        // Removing tags might leave a lot of white space in the
                        // left which would be interpreted as something
                        // different by markdown. We have to remove these
                        line.erase(0, line.find_first_not_of(" \t"));
                    }
                    while (std::regex_search(line, match, html_tag_regex)) {
                        std::cout << match[0] << "-> <empty>" << std::endl;
                        line.erase(match.position(0), match[0].length());
                    }
                }
            }
        }
    }

    void mdsplitter::run_update_links() {
        // [some text](URL) -> std::regex{R"([^!]*\[(.*)\]\((.*)\))"};
        // ![some text](URL) -> std::regex{R"(!\[(.*)\]\((.*)\))"};
        std::regex url_or_img_regex{R"(\[([^\[\]]*)\]\(([^\)]*)\))"};
        for (auto &section : sections_) {
            bool in_codeblock = false;
            for (auto &line : section.lines) {
                if (is_codeblock(line)) {
                    in_codeblock = 1 - in_codeblock;
                }
                if (in_codeblock) {
                    continue;
                }
                std::smatch match;
                auto line_begin = line.cbegin();
                auto line_end = line.cend();
                size_t replacement_size = 0;
                while (std::regex_search(line_begin, line_end, match,
                                         url_or_img_regex)) {
                    size_t line_begin_pos = line_begin - line.cbegin();
                    std::string url = match[2];
                    if (!is_external(url)) {
                        bool same_file = url.rfind('#', 0) == 0;
                        if (!same_file) {
                            fs::path relative_url =
                                relative_path(url, section.filepath);
                            std::cout << section.filepath.c_str() << ": " << url
                                      << " -> " << relative_url.c_str()
                                      << std::endl;
                            size_t pos =
                                std::distance(line.cbegin(), line_begin) +
                                match.position(2);
                            line.replace(pos, match[2].length(),
                                         relative_url.string());
                            replacement_size = relative_url.string().size();
                        } else {
                            std::string header_slug = url.substr(1);
                            auto it = std::find_if(
                                sections_.begin(), sections_.end(),
                                [&](const mdsection &s) {
                                    return slugify(s.header_name) ==
                                           header_slug;
                                });
                            if (it != sections_.end()) {
                                fs::path absolute_destination =
                                    fs::current_path() / input_.parent_path() /
                                    it->filepath;
                                fs::path relative_to =
                                    absolute_destination.lexically_relative(
                                        section.filepath.parent_path());
                                std::cout << url << "->" << relative_to.c_str()
                                          << std::endl;
                                size_t pos =
                                    std::distance(line.cbegin(), line_begin) +
                                    match.position(2);
                                line.replace(pos, match[2].length(),
                                             relative_to.string());
                                replacement_size = relative_to.string().size();
                            } else {
                                std::cout << "Cannot find file for a header "
                                          << url << " whose slug is "
                                          << header_slug << std::endl;
                                replacement_size = url.size();
                            }
                        }
                    } else {
                        std::cout << url << " <- (external)" << std::endl;
                        replacement_size = url.size();
                    }
                    if (replacement_size == 0) {
                        replacement_size = match[2].length();
                    }
                    line_begin = line.cbegin() + line_begin_pos +
                                 match.position(2) + replacement_size;
                    line_end = line.cend();
                }
            }
        }

        // [![example_area_1](docs/examples/line_plot/area/area_1.svg)](examples/line_plot/area/area_1.cpp)
        std::regex second_order_url_or_img_regex{
            R"(\[(!?)\[([^\[\]]*)\]\(([^\)]*)\)\]\(([^\)]*)\))"};
        for (auto &section : sections_) {
            bool in_codeblock = false;
            for (auto &line : section.lines) {
                if (is_codeblock(line)) {
                    in_codeblock = 1 - in_codeblock;
                }
                if (in_codeblock) {
                    continue;
                }
                std::smatch match;
                auto line_begin = line.cbegin();
                auto line_end = line.cend();
                size_t replacement_size = 0;
                while (std::regex_search(line_begin, line_end, match,
                                         second_order_url_or_img_regex)) {
                    size_t line_begin_pos = line_begin - line.cbegin();
                    std::string url = match[4];
                    bool is_http = url.rfind("http://", 0) == 0;
                    bool is_https = url.rfind("https://", 0) == 0;
                    bool is_www = url.rfind("www.", 0) == 0;
                    bool is_external = is_http || is_https || is_www;
                    if (!is_external) {
                        bool same_file = url.rfind('#', 0) == 0;
                        if (!same_file) {
                            fs::path absolute_from =
                                fs::current_path() / input_.parent_path() / url;
                            fs::path relative_to =
                                absolute_from.lexically_relative(
                                    section.filepath.parent_path());
                            std::cout << url << "->" << relative_to.c_str()
                                      << std::endl;
                            size_t pos =
                                std::distance(line.cbegin(), line_begin) +
                                match.position(4);
                            line.replace(pos, match[4].length(),
                                         relative_to.string());
                            replacement_size = relative_to.string().size();
                        } else {
                            std::string header_slug = url.substr(1);
                            auto it = std::find_if(
                                sections_.begin(), sections_.end(),
                                [&](const mdsection &s) {
                                    return slugify(s.header_name) ==
                                           header_slug;
                                });
                            if (it != sections_.end()) {
                                fs::path absolute_destination =
                                    fs::current_path() / input_.parent_path() /
                                    it->filepath;
                                fs::path relative_to =
                                    absolute_destination.lexically_relative(
                                        section.filepath.parent_path());
                                std::cout << url << "->" << relative_to.c_str()
                                          << std::endl;
                                size_t pos =
                                    std::distance(line.cbegin(), line_begin) +
                                    match.position(4);
                                line.replace(pos, match[4].length(),
                                             relative_to.string());
                                replacement_size = relative_to.string().size();
                            } else {
                                std::cout << "Cannot find file for a header "
                                          << url << " whose slug is "
                                          << header_slug << std::endl;
                                replacement_size = url.size();
                            }
                        }
                    } else {
                        std::cout << url << " <- (external)" << std::endl;
                        replacement_size = url.size();
                    }
                    if (replacement_size == 0) {
                        replacement_size = match[4].length();
                    }
                    line_begin = line.cbegin() + line_begin_pos +
                                 match.position(2) + replacement_size;
                    line_end = line.cend();
                }
            }
        }
    }

    void mdsplitter::create_subsection_links() {
        for (auto section_it = sections_.begin(); section_it != sections_.end();
             ++section_it) {
            auto &section = *section_it;
            section.lines.emplace_back("");
            section.lines.emplace_back("");
            for (auto subsection_it = std::next(section_it);
                 subsection_it != sections_.end(); ++subsection_it) {
                auto &subsection = *subsection_it;
                if (subsection.level <= section.level) {
                    break;
                } else {
                    int level_difference = subsection.level - section.level;
                    assert(level_difference > 0);
                    std::string padding((level_difference - 1) * 2, ' ');
                    fs::path absolute_destination = fs::current_path() /
                                                    input_.parent_path() /
                                                    subsection.filepath;
                    fs::path relative_destination =
                        absolute_destination.lexically_relative(
                            section.filepath.parent_path());
                    section.lines.emplace_back(
                        padding + "- [" + subsection.header_name + "](" +
                        relative_destination.string() + ")");
                }
            }
        }
    }

    void mdsplitter::escape_jekyll() {
        for (auto &section : sections_) {
            for (auto &line : section.lines) {
                size_t pos = line.find("{{");
                while (pos != std::string::npos) {
                    std::cout << line << "->";
                    line.replace(pos, 2, "{ {");
                    std::cout << line << std::endl;
                    pos = line.find("{{", pos + 3);
                }
            }
        }
    }

    void mdsplitter::reindent_headers() {
        std::regex header_regex{"(#+) +(.*)"};
        for (auto &section : sections_) {
            for (auto &line : section.lines) {
                std::smatch sm;
                if (std::regex_match(line, sm, header_regex)) {
                    auto level = static_cast<short>(sm[1].length());
                    auto level_diff = level - section.level;
                    if (level_diff < 0) {
                        std::cerr
                            << section.filepath.c_str()
                            << ": level_diff should not be less than zero."
                            << std::endl;
                        level_diff = 0;
                    }
                    line = std::string(level_diff + 1, '#') + " " +
                           section.header_name;
                }
            }
        }
    }

    void mdsplitter::run_add_front_matter() {
        short current_level = 0;
        std::vector<int> level_order;
        std::vector<std::string> level_parent;
        for (auto it = sections_.begin(); it != sections_.end(); ++it) {
            auto &section = *it;

            // we consider level 1 and 2 to be the same
            short adjusted_level = section.level == 1 ? 1 : section.level - 1;
            bool is_new_level = adjusted_level != current_level;
            if (is_new_level) {
                level_order.resize(adjusted_level, 1);
                if (adjusted_level < current_level) {
                    ++level_order.back();
                }
                level_parent.resize(adjusted_level - 1);
                if (adjusted_level > current_level && it != sections_.begin()) {
                    level_parent.back() = std::prev(it)->header_name;
                }
            } else {
                ++level_order.back();
            }
            current_level = adjusted_level;
            auto next_section_it = std::next(it);
            bool has_children = next_section_it != sections_.end() &&
                                next_section_it->level - 1 > current_level;

            std::vector<std::string> front_matter;
            front_matter.emplace_back("---");
            front_matter.emplace_back("layout: default");
            front_matter.emplace_back("title: " + section.header_name);
            front_matter.emplace_back("nav_order: " +
                                      std::to_string(level_order.back()));
            if (has_children) {
                front_matter.emplace_back("has_children: true");
            } else {
                front_matter.emplace_back("has_children: false");
            }
            if (adjusted_level > 1) {
                front_matter.emplace_back("parent: " + level_parent.back());
            }
            if (adjusted_level > 2) {
                if (level_parent.size() >= 2) {
                    front_matter.emplace_back(
                        "grand_parent: " +
                        level_parent[level_parent.size() - 2]);
                }
            }
            front_matter.emplace_back("has_toc: false");
            front_matter.emplace_back("---");

            std::cout << section.filepath.c_str() << std::endl;
            for (const auto &l : front_matter) {
                std::cout << l << std::endl;
            }

            section.lines.insert(section.lines.begin(), front_matter.begin(),
                                 front_matter.end());
        }
    }
    const fs::path &mdsplitter::input() const { return input_; }
    void mdsplitter::input(const fs::path &input) { input_ = input; }
    const fs::path &mdsplitter::output_dir() const { return output_dir_; }
    void mdsplitter::output_dir(const fs::path &output_dir) {
        output_dir_ = output_dir;
    }
    const std::vector<std::string> &mdsplitter::clear_html_tags() const {
        return clear_html_tags_;
    }
    void mdsplitter::clear_html_tags(
        const std::vector<std::string> &clear_html_tags) {
        clear_html_tags_ = clear_html_tags;
    }
    const std::string &mdsplitter::repository() const { return repository_; }
    void mdsplitter::repository(const std::string &repository) {
        repository_ = repository;
    }
    short mdsplitter::max_split_level() const { return max_split_level_; }
    void mdsplitter::max_split_level(short max_split_level) {
        max_split_level_ = max_split_level;
    }
    bool mdsplitter::include_toc() const { return include_toc_; }
    void mdsplitter::include_toc(bool include_toc) {
        include_toc_ = include_toc;
    }
    bool mdsplitter::jekyll_escape() const { return jekyll_escape_; }
    void mdsplitter::jekyll_escape(bool jekyll_escape) {
        jekyll_escape_ = jekyll_escape;
    }
    bool mdsplitter::indent_headers() const { return indent_headers_; }
    void mdsplitter::indent_headers(bool indent_headers) {
        indent_headers_ = indent_headers;
    }
    void mdsplitter::add_front_matter(bool add_front_matter) {
        add_front_matter_ = add_front_matter;
    }
    void mdsplitter::update_links(bool update_links) {
        update_links_ = update_links;
    }
    bool mdsplitter::remove_autotoc() const { return remove_autotoc_; }
    void mdsplitter::remove_autotoc(bool remove_autotoc) {
        remove_autotoc_ = remove_autotoc;
    }
    const fs::path &mdsplitter::current_output_file() const {
        return current_output_file_;
    }
    void mdsplitter::current_output_file(const fs::path &current_output_file) {
        current_output_file_ = current_output_file;
    }
    const std::vector<mdsection> &mdsplitter::sections() const {
        return sections_;
    }
    void mdsplitter::sections(const std::vector<mdsection> &sections) {
        sections_ = sections;
    }
    bool mdsplitter::add_front_matter() const { return add_front_matter_; }
    bool mdsplitter::update_links() const { return update_links_; }
    bool mdsplitter::trace() const { return trace_; }
    void mdsplitter::trace(bool trace) { trace_ = trace; }

    /// Returns path is inside base
    bool mdsplitter::is_subdirectory(const fs::path &path,
                                     const fs::path &base) {
        fs::path p = path;
        if (p.is_relative()) {
            p = fs::current_path() / input_.parent_path() / p;
        }

        fs::path b = base;
        if (b.is_relative()) {
            b = fs::current_path() / b;
        }
        if (!fs::is_directory(b)) {
            b = b.parent_path();
        }

        while (b != p && p.parent_path() != p) {
            p = p.parent_path();
        }

        return b == p;
    }

    fs::path mdsplitter::relative_path(const fs::path &path,
                                       const fs::path &base) {
        fs::path base_dir = fs::is_directory(base) ? base : base.parent_path();
        bool is_in_docs_dir = is_subdirectory(path, base_dir);
        if (is_in_docs_dir) {
            return fs::relative(path, base_dir);
        } else {
            bool is_in_project_dir = is_subdirectory(path, fs::current_path());
            if (is_in_project_dir) {
                if (!repository_.empty()) {
                    fs::path url;
                    if (!is_external(repository_)) {
                        url /= "https://github.com";
                    }
                    url /= repository_;
                    url /= "blob/master";
                    url /= fs::relative(path, fs::current_path());
                    return url;
                } else {
                    std::cerr << fs::relative(path, fs::current_path())
                              << " is outside the output directory but you "
                                 "have not provided a repository to mdsplit. "
                                 "This will generate a broken link."
                              << std::endl;
                    return fs::relative(path, fs::current_path());
                }
            } else {
                std::cerr
                    << fs::relative(path, fs::current_path())
                    << " is outside the project directory. There's no way to "
                       "generate a relative link that will work elsewhere. "
                       "This will generate a broken link in your documentation."
                    << std::endl;
                return fs::relative(path, fs::current_path());
            }
        }
    }

    bool mdsplitter::is_external(const std::string &url) {
        bool is_http = url.rfind("http://", 0) == 0;
        bool is_https = url.rfind("https://", 0) == 0;
        bool is_www = url.rfind("www.", 0) == 0;
        return is_http || is_https || is_www;
    }

    void mdsplitter::list_doc_outsiders() {
        bool first = true;
        for (auto &p : fs::recursive_directory_iterator(output_dir_)) {
            if (p.path().extension() == ".md") {
                fs::path outsider = fs::relative(p.path(), fs::current_path());
                auto it = std::find_if(
                    sections_.begin(), sections_.end(),
                    [&](const mdsection &s) { return s.filepath == outsider; });
                if (it == sections_.end()) {
                    if (first) {
                        std::cout << "\n# The following .md files were not "
                                     "generated by mdsplit"
                                  << std::endl;
                        std::cout << "# Please make sure that is on purpose:"
                                  << std::endl;
                        first = false;
                    }
                    std::cout << "Outsider doc file: " << outsider.c_str()
                              << '\n';
                }
            }
        }
    }

} // namespace mdsplit
