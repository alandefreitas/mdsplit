//
// Created by Alan Freitas on 30/09/20.
//

#include <algorithm>

#include "mdsplitter.h"

namespace mdsplit {

    int mdsplitter::run() {
        fs::create_directory(output_dir_);
        std::cout << "# Find Sections" << std::endl;
        find_sections();
        std::cout << "\n# Remove Auto TOC" << std::endl;
        remove_auto_toc();
        std::cout << "\n# Remove HTML Tags" << std::endl;
        remove_html_tags();
        std::cout << "\n# Update Links" << std::endl;
        update_links();
        std::cout << "\n# Create Subsection links" << std::endl;
        create_subsection_links();
        std::cout << "\n# Escape Jekyll" << std::endl;
        escape_jekyll();
        std::cout << "\n# Reindent Headers" << std::endl;
        reindent_headers();
        std::cout << "\n# Add Front Matter" << std::endl;
        add_front_matter();
        std::cout << "\n# Save Sections" << std::endl;
        save_sections();
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

        while (std::getline(fin, current_line)) {
            std::smatch sm;

            if (is_codeblock(current_line)) {
                inside_codeblock = 1 - inside_codeblock;
            }

            if (!inside_codeblock) {
                bool found_header =
                    std::regex_search(current_line, sm, header_regex);
                if (found_header) {
                    // Create new section
                    mdsection new_section;
                    new_section.level = sm[1].length();
                    new_section.header_name = sm[2].str();
                    for (int i = new_section.level - 1; i > 1; --i) {
                        auto it = std::find_if(
                            sections_.rbegin(), sections_.rend(),
                            [&i](const mdsection &s) { return s.level == i; });
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
                    fs::create_directory(new_section.filepath.parent_path());
                    sections_.push_back(new_section);
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
            std::cout << "Saving " << section.filepath << "(Section: " << section.header_name << ")" << std::endl;
            for (const auto &line : section.lines) {
                fout << line << std::endl;
            }
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
                std::cout << "Found Auto TOC in " << section.header_name << std::endl;
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

    void mdsplitter::update_links() {
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
                auto line_copy = line;
                while (std::regex_search(line_copy, match, url_or_img_regex)) {
                    std::string url = match[2];
                    bool is_http = url.rfind("http://", 0) == 0;
                    bool is_https = url.rfind("https://", 0) == 0;
                    bool is_www = url.rfind("www.", 0) == 0;
                    bool is_external = is_http || is_https || is_www;
                    if (!is_external) {
                        bool same_file = url.rfind('#', 0) == 0;
                        if (!same_file) {
                            fs::path absolute_from = fs::current_path() / input_.parent_path() / url;
                            fs::path relative_to = absolute_from.lexically_relative(section.filepath.parent_path());
                            std::cout << url << "->" << relative_to.c_str() << std::endl;
                            line.replace(match.position(2), match[2].length(), relative_to.c_str());
                        } else {
                            std::string header_slug = url.substr(1);
                            auto it = std::find_if(sections_.begin(), sections_.end(), [&](const mdsection& s){
                                return slugify(s.header_name) == header_slug;
                            });
                            if (it != sections_.end()) {
                                fs::path absolute_destination = fs::current_path() / input_.parent_path() / it->filepath;
                                fs::path relative_to = absolute_destination.lexically_relative(section.filepath.parent_path());
                                std::cout << url << "->" << relative_to.c_str() << std::endl;
                                line.replace(match.position(2), match[2].length(), relative_to.c_str());
                            } else {
                                std::cout << "Cannot find file for a header " << url << " whose slug is " << header_slug << std::endl;
                            }
                        }
                    } else {
                        std::cout << url << "-> <external>" << std::endl;
                    }
                    line_copy.replace(match.position(0), match[0].length(),"");
                }
            }
        }
    }

    void mdsplitter::create_subsection_links() {
        for (auto section_it = sections_.begin(); section_it != sections_.end(); ++ section_it) {
            auto& section = *section_it;
            section.lines.emplace_back("");
            section.lines.emplace_back("");
            for (auto subsection_it = std::next(section_it);
                 subsection_it != sections_.end(); ++subsection_it) {
                auto& subsection = *subsection_it;
                if (subsection.level <= section.level) {
                    break;
                } else {
                    int level_difference = subsection.level - section.level;
                    assert(level_difference > 0);
                    std::string padding((level_difference-1) * 2, ' ');
                    fs::path absolute_destination = fs::current_path() / input_.parent_path() / subsection.filepath;
                    fs::path relative_destination = absolute_destination.lexically_relative(section.filepath.parent_path());
                    section.lines.emplace_back(padding + "- [" + subsection.header_name + "](" + relative_destination.string() + ")");
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
                    line = "# " + section.header_name;
                }
            }
        }
    }

    void mdsplitter::add_front_matter() {
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
            bool has_children = next_section_it != sections_.end() && next_section_it->level - 1 > current_level;

            std::vector<std::string> front_matter;
            front_matter.emplace_back("---");
            front_matter.emplace_back("layout: default");
            front_matter.emplace_back("title: " + section.header_name);
            front_matter.emplace_back("nav_order: " + std::to_string(level_order.back()));
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
                    front_matter.emplace_back("grand_parent: " + level_parent[level_parent.size()-2]);
                }
            }
            front_matter.emplace_back("has_toc: false");
            front_matter.emplace_back("---");

            std::cout << section.filepath.c_str() << std::endl;
            for (const auto &l : front_matter) {
                std::cout << l << std::endl;
            }

            section.lines.insert(section.lines.begin(), front_matter.begin(), front_matter.end());
        }
    }

} // namespace mdsplit
