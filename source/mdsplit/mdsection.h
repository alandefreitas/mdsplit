//
// Created by Alan Freitas on 30/09/20.
//

#ifndef MDSPLIT_MDSECTION_H
#define MDSPLIT_MDSECTION_H

#include <filesystem>
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
    };
} // namespace mdsplit

#endif // MDSPLIT_MDSECTION_H
