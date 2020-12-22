---
layout: default title: Install from Source nav_order: 2 has_children: false parent: Installing has_toc: false
---

# Install from Source

To install from the source files:

=== "Windows"

    ```bash
    mkdir build
    cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS="/O2"
    cmake --build . -j 2 --config Release
    cmake --install .
    ```

=== "Linux"

    ```bash
    mkdir build
    cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS="-O2"
    cmake --build . -j 2 --config Release
    sudo cmake --install .
    ```

=== "Mac OS"

    ```bash
    mkdir build
    cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS="-O2"
    cmake --build . -j 2 --config Release
    cmake --install .
    ```

The dependencies are CMake 3.17 and C++17.



<!-- Generated with mdsplit: https://github.com/alandefreitas/mdsplit -->
