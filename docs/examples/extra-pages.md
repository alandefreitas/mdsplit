---
layout: default
title: Extra pages
nav_order: 3
has_children: false
parent: Examples
has_toc: false
---
# Extra pages

The documentation often needs some extra `.md` files. Just put these files in the `docs` directory and it will also be included in your documentation navigation links.

To define where these files will fall inside your documentation, you can edit their YAML front matter (the first lines in your `.md` file). If using the `just-the-docs` theme, you can define the title, navigation order, and page hierarchy with the parameters `title`, `nav_order`, `parent`, and `has_children` You can also use the parameter `nav_exclude` to hide a certain page from the navigation links.

```yaml
---
layout: default
title: Customization
nav_order: 4
parent: UI Components
has_children: true
nav_exclude: false
---  
```




<!-- Generated with mdsplit: https://github.com/alandefreitas/mdsplit -->
