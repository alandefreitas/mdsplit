//
// Created by Alan Freitas on 30/09/20.
//

#ifndef MDSPLIT_MDSECTION_H
#define MDSPLIT_MDSECTION_H

#include <filesystem>
#include <regex>
#include <string>
#include <vector>

namespace mdsplit {
    namespace fs = std::filesystem;

    struct mdsection {
        short level{0};
        std::string header_name;
        std::vector<std::string> parent_headers;
        std::vector<std::string> lines;
        fs::path filepath;

        [[nodiscard]] inline bool
        has_content(bool count_header_as_content = false,
                    bool count_front_matter_as_content = false) const {
            bool has_been_inside_frontmatter = false;
            bool inside_frontmatter = false;
            for (auto &line : lines) {
                // identify frontmatter
                if (line == "---") {
                    if (!has_been_inside_frontmatter) {
                        inside_frontmatter = true;
                        has_been_inside_frontmatter = true;
                    } else {
                        inside_frontmatter = false;
                    }
                    continue;
                }
                // skip if inside frontmatter
                if (!count_front_matter_as_content && inside_frontmatter) {
                    continue;
                }
                // if content is found
                if (!line.empty()) {
                    if (count_header_as_content) {
                        return true;
                    } else {
                        std::regex header_regex{"(#+) +(.*)"};
                        if (!std::regex_match(line, header_regex)) {
                            return true;
                        }
                    }
                }
            }
            return false;
        }
    };

} // namespace mdsplit

#endif // MDSPLIT_MDSECTION_H
