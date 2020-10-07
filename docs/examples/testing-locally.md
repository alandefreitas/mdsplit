---
layout: default
title: Testing Locally
nav_order: 5
has_children: false
parent: Examples
has_toc: false
---
# Testing Locally

You might want to test your documentation locally before pushing it to your repository. 

To test your GitHub Page locally, you first need to install [Jekyll](https://jekyllrb.com/docs/installation/) and [Bundler](https://bundler.io) locally.

Then adjust your Jekyll configuration file in [`docs/_config.yml`](../_config.yml) to use a local repository for the theme. 

```yaml
#remote_theme: pmarsceill/just-the-docs
theme: "just-the-docs"
```

Create a [`docs/Gemfile`](../Gemfile) with 

```bash
bundle init
```

And include the following commands to install `github-pages` and `just-the-docs`:   

```
gem "github-pages", group: :jekyll_plugins
gem "just-the-docs"
```

See an example in [`docs/Gemfile`](../Gemfile).

Install these gems with 

```bash
bundle install
```

for the first time or 

```bash
bundle update
```

after that.

Adjust your Jekyll configuration file in [`docs/_config.yml`](../_config.yml) to use the local repository for the theme. 

```yaml
#remote_theme: pmarsceill/just-the-docs
theme: "just-the-docs"
```

Run the jekyll server with: 

```bash
bundle exec jekyll serve
```




<!-- Generated with mdsplit: https://github.com/alandefreitas/mdsplit -->
