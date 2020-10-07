---
layout: default
title: Hiding sections from docs
nav_order: 6
has_children: false
parent: Options
has_toc: false
---
# Hiding sections from docs

Use the comments `<!-- START mdsplit-ignore -->` and `<!-- END mdsplit-ignore -->` to ignore sections from your `README.md`. For instance:

```markdown
<!-- START mdsplit-ignore -->
# Section to ignore

`mdsplit` will remove this whole section from your documentation.

<!-- END mdsplit-ignore -->
```

or

```markdown
# Section to ignore

<!-- START mdsplit-ignore -->
`mdsplit` will remove this paragraph from your documentation.
<!-- END mdsplit-ignore -->
```

If you ignore the complete section, `mdsplit` will create no file for that section.

If you're reading this from [`README.md`](https://github.com/alandefreitas/mdsplit/blob/master/README.md) you will see this section has a subsection that will be completely ignored in the documentation. 





<!-- Generated with mdsplit: https://github.com/alandefreitas/mdsplit -->
