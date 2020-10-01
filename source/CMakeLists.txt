#######################################################
### Dependencies                                    ###
#######################################################
# Filesystem
find_package(Filesystem QUIET)
if (NOT CXX_FILESYSTEM_HAVE_FS)
    message(FATAL_ERROR "Your C++ compiler does not have the filesystem library. Please update your C++ compiler.")
endif()

# Threads
find_package(Threads REQUIRED)

#######################################################
### Mdsplit library                                 ###
#######################################################
add_library(mdsplitlib
        mdsplit/mdsplitter.h
        mdsplit/mdsplitter.cpp
        mdsplit/mdsection.h
)

target_link_libraries(mdsplitlib PUBLIC std::filesystem)

target_include_directories(mdsplitlib
        PUBLIC $<BUILD_INTERFACE:${MDSPLIT_ROOT_DIR}/source>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

if (CXX_FILESYSTEM_IS_EXPERIMENTAL)
    target_compile_definitions(mdsplitlib PUBLIC CXX_FILESYSTEM_IS_EXPERIMENTAL)
endif()

if (BUILD_WITH_UTF8 AND MSVC)
    target_compile_options(mdsplitlib PRIVATE /utf-8)
endif()

include(CheckSymbolExists)
check_symbol_exists(min "Windows.h" HAVE_WINDOWS_MINMAX)
if (HAVE_WINDOWS_MINMAX)
    target_compile_definitions(mdsplitlib PUBLIC NOMINMAX)
endif()

if (BUILD_WITH_PEDANTIC_WARNINGS)
    if (MSVC)
        target_compile_options(mdsplitlib PRIVATE /W4 /WX)
    else ()
        target_compile_options(mdsplitlib PRIVATE -Wall -Wextra -pedantic -Werror)
    endif ()
endif ()
