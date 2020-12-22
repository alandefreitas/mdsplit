---
layout: default
title: Testing Locally
nav_order: 2
has_children: false
parent: Step-by-Step
has_toc: false
---
# Testing Locally

You might want to test your documentation locally before pushing it to your repository.

Install mkdocs with

```bash
pip install mkdocs-material
```

After generating the docs with mdsplit, run the mkdocs server with

```bash
mkdocs serve
```

Or build the static documentation with

```bash
mkdocs serve
```

Use this mkdocs configuration file to get started:

=== "mkdocs.yml"

```yaml hl_lines="1 2 3 4 6 30"
--8<-- "mkdocs.yml"
```

Replace the settings with your repository information.



<!-- Generated with mdsplit: https://github.com/alandefreitas/mdsplit -->
