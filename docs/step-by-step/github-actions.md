---
layout: default
title: Github Actions
nav_order: 3
has_children: false
parent: Step-by-Step
has_toc: false
---
# Github Actions

You can integrate `mdsplit` with GitHub actions to regenerate the documentation whenever you change your `README.md`
file.

Use this workflow to get started:

=== ".github/workflows/docs.yml"

    ```yaml hl_lines="21 22 31-44 48"
    --8<-- ".github/workflows/docs.yml"
    ```

Replace the settings with your repository information.

Most steps in this workflow are optional:

* The step `technote-space/toc-generator@v2` creates a table of contents for your README.md file
* The second step downloads and builds the master version of mdsplit. This is the version we use in this repository, but
  you probably want to use a more stable version in your own repository. To do that, comment this step and use the third
  and forth steps instead.
* The third and fourth steps (commented out) download the latest release version of mdsplit. That's probably what you
  want for your repository. Uncomment these steps to do that.
* The next steps are pushing the docs to your master branch. Make any adjustments you might need.
* The last steps are taking the docs from your master branch and publishing them to your gh-pages branch.



<!-- Generated with mdsplit: https://github.com/alandefreitas/mdsplit -->
