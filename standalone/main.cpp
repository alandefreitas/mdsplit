// C++
#include <iostream>

// External
#include <cxxopts.hpp>

// Internal
#include <mdsplit/mdsplitter.h>

int main(int argc, char *argv[]) {
    ///////////////////////////////////////////////////////
    /// Define command line options                     ///
    ///////////////////////////////////////////////////////
    cxxopts::Options options("mdsplit",
                             "Generate documentation from README.md files");
    std::string input = "README.md";
    std::string output = "docs";
    std::string repository;
    options.add_options("File")(
        "i,input", "Input file",
        cxxopts::value(input)->default_value("README.md"))(
        "o,output", "Output directory",
        cxxopts::value(output)->default_value("docs"))(
        "r,repository", "Output repository", cxxopts::value(repository));

    short max_split_level{6};
    std::vector<std::string> clear_html_tags{};
    bool include_toc{true};
    bool jekyll_escape{true};
    bool indent_headers{true};
    bool add_front_matter{true};
    bool update_links{true};
    bool remove_autotoc{true};
    bool trace{true};
    bool erase_old_mdsplit_files{true};
    options.add_options("Behaviour")(
        "l,level", "Max level for which we should split the file",
        cxxopts::value(max_split_level)->default_value("6"))(
        "c,clear-html", "List of HTML tags mdsplit should clear",
        cxxopts::value(clear_html_tags)->default_value("details,summary"))(
        "t,toc", "Create a table of contents for the new files",
        cxxopts::value(include_toc)->default_value("true"))(
        "e,erase-old-mdsplit-files",
        "Erase old md files also generated with mdsplit",
        cxxopts::value(erase_old_mdsplit_files)->default_value("true"))(
        "j,jekyll-escape", "Escape consecutive \"{{\"s for Jekyll processing",
        cxxopts::value(jekyll_escape)->default_value("true"))(
        "header-reindent", "Reindent headers to match the new files",
        cxxopts::value(indent_headers)->default_value("true"))(
        "f,front-matter", "Include a front-matter in the new files",
        cxxopts::value(add_front_matter)->default_value("true"))(
        "u,url-update", "Update relative URLs to their new relative paths",
        cxxopts::value(update_links)->default_value("true"))(
        "remove-auto-toc", "Remove automatic table of contents",
        cxxopts::value(remove_autotoc)->default_value("true"))(
        "trace", "Trace commands",
        cxxopts::value(trace)->default_value("true"));

    bool show_help{true};
    bool show_version{false};
    options.add_options("Help")(
        "h,help", "Print usage",
        cxxopts::value(show_help)->default_value("false"))(
        "v,version", "Print version",
        cxxopts::value(show_version)->default_value("false"));

    ///////////////////////////////////////////////////////
    /// Parse command line options                      ///
    ///////////////////////////////////////////////////////
    auto result = options.parse(argc, argv);

    if (input.empty()) {
        std::cerr << "Please provide an input file" << std::endl;
    }

    if (show_help || result.count("help")) {
        options.custom_help(
            "-i input_directory -o output_directory -r username/repository");
        std::cout << options.help({"File", "Behaviour", "Help"}) << std::endl;
        return input.empty() ? 1 : 0;
    }

    // Show version
    if (show_version) {
        std::cout << "mdsplit: version 0.0.1" << std::endl;
        return 0;
    }

    ///////////////////////////////////////////////////////
    /// Run                                             ///
    ///////////////////////////////////////////////////////
    mdsplit::mdsplitter m;
    m.input(input);
    m.output_dir(output);
    m.repository(repository);
    m.max_split_level(max_split_level);
    std::sort(clear_html_tags.begin(), clear_html_tags.end());
    clear_html_tags.erase(
        std::unique(clear_html_tags.begin(), clear_html_tags.end()),
        clear_html_tags.end());
    m.clear_html_tags(clear_html_tags);
    m.include_toc(include_toc);
    m.jekyll_escape(jekyll_escape);
    m.indent_headers(indent_headers);
    m.add_front_matter(add_front_matter);
    m.update_links(update_links);
    m.remove_autotoc(remove_autotoc);
    m.trace(trace);
    m.erase_old_mdsplit_files(erase_old_mdsplit_files);
    return m.run();
}
