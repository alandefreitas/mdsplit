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
        void run_update_links();

        /// Create a table of contents at the end of each new file
        void create_subsection_links();

        // Remove consecutive {{ (jekyll requirement) without messing with the
        // original README.md
        void escape_jekyll();

        /// Reduce header levels in sections
        void reindent_headers();

        void run_add_front_matter();

        void save_sections();

        fs::path relative_path(const fs::path &path, const fs::path &base);

        bool is_subdirectory(const fs::path &path, const fs::path &base);

        bool is_external(const std::string &url);

        void list_doc_outsiders();

      public /* getters and setters */:
        [[nodiscard]] const fs::path &input() const;
        void input(const fs::path &input);
        [[nodiscard]] const fs::path &output_dir() const;
        void output_dir(const fs::path &output_dir);
        [[nodiscard]] const std::vector<std::string> &clear_html_tags() const;
        void clear_html_tags(const std::vector<std::string> &clear_html_tags);
        [[nodiscard]] const std::string &repository() const;
        void repository(const std::string &repository);
        [[nodiscard]] short max_split_level() const;
        void max_split_level(short max_split_level);
        [[nodiscard]] bool include_toc() const;
        void include_toc(bool include_toc);
        [[nodiscard]] bool jekyll_escape() const;
        void jekyll_escape(bool jekyll_escape);
        [[nodiscard]] bool indent_headers() const;
        void indent_headers(bool indent_headers);
        [[nodiscard]] bool add_front_matter() const;
        void add_front_matter(bool add_front_matter);
        [[nodiscard]] bool update_links() const;
        void update_links(bool update_links);
        [[nodiscard]] bool remove_autotoc() const;
        void remove_autotoc(bool remove_autotoc);
        [[nodiscard]] const fs::path &current_output_file() const;
        void current_output_file(const fs::path &current_output_file);
        [[nodiscard]] const std::vector<mdsection> &sections() const;
        void sections(const std::vector<mdsection> &sections);
        bool trace() const;
        void trace(bool trace);
      private /* options */:
        fs::path input_ = "README.md";
        fs::path output_dir_ = fs::current_path() / "docs";
        std::vector<std::string> clear_html_tags_{"details", "summary"};
        std::string repository_;
        short max_split_level_{3};
        bool include_toc_{true};
        bool jekyll_escape_{true};
        bool indent_headers_{true};
        bool add_front_matter_{true};
        bool update_links_{true};
        bool remove_autotoc_{true};
        bool trace_{true};

      private /* processing */:
        fs::path current_output_file_ = output_dir_ / "index.md";
        std::vector<mdsection> sections_;
    };
} // namespace mdsplit

#endif // MDSPLIT_MDSPLITTER_H
