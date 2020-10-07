---
layout: default
title: Github Actions
nav_order: 4
has_children: false
parent: Examples
has_toc: false
---
# Github Actions

You can integrate `mdsplit` with GitHub actions to regenerate the documentation whenever you change your `README.md` file. Just create a workflow with the following steps:

Download `mdsplit` to the virtual machine:

```yaml
- name: Download mdsplit
  run: curl <mdsplit_url> -o md_split
``` 

You can get the executable link from the [Release Page](https://GitHub.com/alandefreitas/mdsplit/releases/). You can also change this step to uncompress files or build `mdsplit` from source if you want. 

Run `mdsplit` on the virtual machine:

```yaml
- name: Generate Docs
  run: mdsplit -r my_username/my_repository
``` 

Commit the new doc files:

```yaml
- name: Commit Docs
  run: |
    git add docs
    git config --local user.email "action@github.com"
    git config --local user.name "GitHub Action"
    git commit -m "Update Docs" -a
  continue-on-error: true
```

We allow this step to continue on error because there will be nothing to commit sometimes.

Push the new documentation to your repository:

```yaml
- name: Push changes
  uses: ad-m/github-push-action@master
  if: ${ { success() }}
  with:
    github_token: ${ { secrets.GITHUB_TOKEN }}
```

See an example in [`.github/workflows/docs.yml`](https://github.com/alandefreitas/mdsplit/blob/master/.github/workflows/docs.yml).




<!-- Generated with mdsplit: https://github.com/alandefreitas/mdsplit -->
