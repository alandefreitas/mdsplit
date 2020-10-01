---
layout: default
title: GitHub Pages
nav_order: 2
has_children: false
parent: Examples
has_toc: false
---
# GitHub Pages

To use the new `.md` files with GitHub Pages to create the documentation:

* Go to settings and turn on GitHub Pages
* Set `./docs` as your root directory
* Run `mdsplit` on your root directory to save the files in `./docs`
* Go to `docs/_config.yml`:
    * Uncomment `#remote_theme: pmarsceill/just-the-docs`
    * Comment `theme: "just-the-docs"`
    * Adapt `docs/_config.yml` as needed





<!-- Generated with mdsplit: https://github.com/alandefreitas/mdsplit -->