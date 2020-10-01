#######################################################
### Executable                                      ###
#######################################################
add_executable(mdsplit main.cpp)
target_link_libraries(mdsplit PRIVATE mdsplitlib)

#######################################################
### Installer                                       ###
#######################################################
if(BUILD_INSTALLER)
    # Install the executable only
    install(TARGETS mdsplit
            EXPORT MdSplitTargets
            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
            ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
            )
endif()
