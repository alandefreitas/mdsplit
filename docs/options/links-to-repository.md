---
layout: default
title: Links to Repository
nav_order: 1
has_children: false
parent: Options
has_toc: false
---
# Links to Repository

The `--repository` (or `-r`) option should be used to provide your repository name to `mdsplit`. This option enables `mdsplit` to create links to files inside the repository.

Although all internal repository links work in GitHub, not all internal links are adjusted to work with GitHub Pages. Documentation files can only contain links to other markdown files in the documentation directory.

If your documentation needs to refer to a file in the repository and this file is not under `.docs/`, links need to use the absolute repository link as a parent path. 

For instance, conside a file `source/main.cpp` outside `docs`. Then

```markdown
[My Internal Link](source/main.cpp)
```

should become

```markdown
[My Internal Link](https://github.com/my_username/my_repository/blob/master/source/main.cpp)
```

so that the link works correctly on GitHub pages.

You can use the `--repository` (or `-r`) option to provide the repository `mdsplit` should consider to generate these links:

```
mdsplit -r alandefreitas/matplotplusplus
```





<!-- Generated with mdsplit: https://github.com/alandefreitas/mdsplit -->
