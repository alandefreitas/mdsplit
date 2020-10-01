//
// Created by Alan Freitas on 30/09/20.
//

#ifndef MDSPLIT_MDSPLITTER_H
#define MDSPLIT_MDSPLITTER_H

#include "mdsection.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>

namespace mdsplit {
    namespace fs = std::filesystem;

    class mdsplitter {
      public:
        mdsplitter() = default;
        int run();

      public:
        static std::string slugify(std::string_view);

      private:
        /// Go through the file, read all lines and put them
        /// in mdsection objects
        void find_sections();

        /// Identify a codeblock
        /// Most operations need to ignore codeblocks
        bool is_codeblock(const std::string& str);

        /// Remove the automatic github actions autotoc
        /// because we are going to include a TOC for
        /// all files later
        void remove_auto_toc();

        /// Remove undesirable html tags
        /// For instance, jekyll does not handle details and summary well
        void remove_html_tags();

        /// Make links relative to the new directories
        void update_links();

        /// Create a table of contents at the end of each new file
        void create_subsection_links();

        // Remove consecutive {{ (jekyll requirement) without messing with the
        // original README.md
        void escape_jekyll();

        /// Reduce header levels in sections
        void reindent_headers();

        void save_sections();


      private /* options */:
        fs::path input_ = "README.md";
        fs::path output_dir_ = fs::current_path() / "documentation";
        std::vector<std::string> clear_html_tags_{"details", "summary"};
      private /* processing */:
        fs::path current_output_file_ = output_dir_ / "index.md";
        std::vector<mdsection> sections_;
        void add_front_matter();
    };
} // namespace mdsplit

#endif // MDSPLIT_MDSPLITTER_H
