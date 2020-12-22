---
layout: default
title: Install from Source
nav_order: 2
has_children: false
parent: Installing
has_toc: false
---
# Install from Source

```bash
mkdir build
cmake -version
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS="-O2"
cmake --build . -j 2 --config Release
cmake --install .
cpack
```

On windows, replace `-O2` with `/O2`. On Linux, you might need `sudo` for this last command.



<!-- Generated with mdsplit: https://github.com/alandefreitas/mdsplit -->
