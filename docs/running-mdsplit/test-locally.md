---
layout: default
title: Test Locally
nav_order: 3
has_children: false
parent: Running mdsplit
has_toc: false
---
# Test Locally

To test the GitHub Pages locally, see the example of a Jekyll configuration file in [`docs/_config.yml`](../_config.yml).
 
 * Install Jekyll and Bundle.
 * Add `gem "github-pages", group: :jekyll_plugins` to you Gemfile (see [`docs/Gemfile`](../Gemfile))
 * Add `gem "just-the-docs"` to you Gemfile (see [`docs/Gemfile`](../Gemfile))
 * Adapt [`docs/_config.yml`](../_config.yml) as needed
 * Run `bundle install` or `bundle update`
 * Run the jekyll server: `bundle exec jekyll serve --trace --incremental`



