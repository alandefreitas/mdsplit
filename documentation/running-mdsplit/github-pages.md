---
layout: default
title: GitHub Pages
nav_order: 2
has_children: false
parent: Running mdsplit
has_toc: false
---
# GitHub Pages

To use the new .md files with GitHub Pages:

* Go to settings and turn on GitHub Pages
* Set `./documentation` as your root directory
* Run `mdsplit` on your root directory to save the files in `./documentation`
* Go to [`documentation/_config.yml`](../_config.yml):
    * Uncomment `#remote_theme: pmarsceill/just-the-docs`
    * Comment `theme: "just-the-docs"`
    * Adapt [`documentation/_config.yml`](../_config.yml) as needed



