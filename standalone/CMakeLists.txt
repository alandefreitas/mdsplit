#######################################################
### Dependencies                                    ###
#######################################################
# Command line options: https://github.com/jarro2783/cxxopts
CPMAddPackage(NAME cxxopts GIT_REPOSITORY https://github.com/jarro2783/cxxopts GIT_TAG v2.2.0 VERSION 2.2 DOWNLOAD_ONLY TRUE)
if (cxxopts_ADDED)
    add_library(cxxopts INTERFACE IMPORTED)
    target_include_directories(cxxopts INTERFACE ${cxxopts_SOURCE_DIR}/include)
elseif ()
    if (NOT TARGET cxxopts)
        message(FATAL_ERROR "Cannot find or download cxxopts")
    endif ()
endif ()

#######################################################
### Executable                                      ###
#######################################################
add_executable(mdsplit main.cpp)
target_link_libraries(mdsplit PRIVATE mdsplitlib cxxopts)

#######################################################
### Installer                                       ###
#######################################################
if(BUILD_INSTALLER)
    # Install the executable only
    install(TARGETS mdsplit
            EXPORT mdsplitTargets
            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
            ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
            )
endif()
