---
layout: default
title: Links to Repository
nav_order: 1
has_children: false
parent: Options
has_toc: false
---
# Links to Repository

Although all internal links in the repository work OK, not all of them work with github pages. In that case, links need to use the absolute repository link as parent path reference. 

For instance,

```markdown
[![example_fcontour_1](../contour_plots/fcontour/fcontour_1.svg)](examples/contour_plots/fcontour/fcontour_1.cpp)
```

should become

```markdown
[![example_fcontour_1](../contour_plots/fcontour/fcontour_1.svg)](https://github.com/alandefreitas/matplotplusplus/blob/master/examples/contour_plots/fcontour/fcontour_1.cpp)
```

so that the link works correctly on GitHub pages.

You can use the the option `--repository` or `-r` to provide the repository mdsplit should consider to generate these links:

```
mdsplit -r alandefreitas/matplotplusplus
```

https://github.com/alandefreitas/mdsplit

https://github.com/alandefreitas/mdsplit/blob/master/docs/COMPLETE_GALLERY.html#plot_1





<!-- Generated with mdsplit: https://github.com/alandefreitas/mdsplit -->
