# mdsplit

[![Build Status](https://img.shields.io/github/workflow/status/alandefreitas/mdsplit/Build%20mdsplit?event=push&label=Build&logo=Github-Actions)](https://github.com/alandefreitas/mdsplit/actions?query=workflow%3A%22Build+mdsplit%22+event%3Apush)
[![Latest Release](https://img.shields.io/github/release/alandefreitas/mdsplit.svg?label=Download)](https://GitHub.com/alandefreitas/mdsplit/releases/)
[![Documentation](https://img.shields.io/website-up-down-green-red/http/alandefreitas.github.io/mdsplit.svg?label=Documentation)](https://alandefreitas.github.io/mdsplit/)

![mdsplit](https://img.icons8.com/nolan/2x/split-files.png)

`mdsplit` is a tool to split a bulky markdown file into smaller files. The main purpose of `mdsplit` is to generate documentation with GitHub Pages from README.md files. It can be integrated with GitHub actions to regenerate the documentation whenever the README.md file is updated.

<!-- START mdsplit-ignore -->
See the [LIVE DEMO](https://alandefreitas.github.io/mdsplit/) and compare it with this very [`README.md`](README.md) file.
<!-- END mdsplit-ignore -->

[![Facebook](https://img.shields.io/twitter/url/http/shields.io.svg?style=social&label=Share+on+Facebook&logo=facebook)](https://www.facebook.com/sharer/sharer.php?t=mdsplit:%20split%20a%20bulky%20README.md%20into%20a%20nice%20documentation&u=https://github.com/alandefreitas/mdsplit/)
[![QZone](https://img.shields.io/twitter/url/http/shields.io.svg?style=social&label=Share+on+QZone&logo=qzone)](http://sns.qzone.qq.com/cgi-bin/qzshare/cgi_qzshare_onekey?url=https://github.com/alandefreitas/mdsplit/&title=mdsplit:%20split%20a%20bulky%20README.md%20into%20a%20nice%20documentation&summary=mdsplit:%20split%20a%20bulky%20README.md%20into%20a%20nice%20documentation)
[![Weibo](https://img.shields.io/twitter/url/http/shields.io.svg?style=social&label=Share+on+Weibo&logo=sina-weibo)](http://sns.qzone.qq.com/cgi-bin/qzshare/cgi_qzshare_onekey?url=https://github.com/alandefreitas/mdsplit/&title=mdsplit:%20split%20a%20bulky%20README.md%20into%20a%20nice%20documentation&summary=mdsplit:%20split%20a%20bulky%20README.md%20into%20a%20nice%20documentation)
[![Reddit](https://img.shields.io/twitter/url/http/shields.io.svg?style=social&label=Share+on+Reddit&logo=reddit)](http://www.reddit.com/submit?url=https://github.com/alandefreitas/mdsplit/&title=mdsplit:%20split%20a%20bulky%20README.md%20into%20a%20nice%20documentation)
[![Twitter](https://img.shields.io/twitter/url/http/shields.io.svg?label=Share+on+Twitter&style=social)](https://twitter.com/intent/tweet?text=mdsplit:%20split%20a%20bulky%20README.md%20into%20a%20nice%20documentation&url=https://github.com/alandefreitas/mdsplit/&hashtags=Markdown,Documentation,DocumentationGenerator,GithubPages)
[![LinkedIn](https://img.shields.io/twitter/url/http/shields.io.svg?style=social&label=Share+on+LinkedIn&logo=linkedin)](https://www.linkedin.com/shareArticle?mini=false&url=https://github.com/alandefreitas/mdsplit/&title=mdsplit:%20split%20a%20bulky%20README.md%20into%20a%20nice%20documentation)
[![WhatsApp](https://img.shields.io/twitter/url/http/shields.io.svg?style=social&label=Share+on+WhatsApp&logo=whatsapp)](https://api.whatsapp.com/send?text=mdsplit:%20split%20a%20bulky%20README.md%20into%20a%20nice%20documentation:+https://github.com/alandefreitas/mdsplit/)
[![Line.me](https://img.shields.io/twitter/url/http/shields.io.svg?style=social&label=Share+on+Line.me&logo=line)](https://lineit.line.me/share/ui?url=https://github.com/alandefreitas/mdsplit/&text=mdsplit:%20split%20a%20bulky%20README.md%20into%20a%20nice%20documentation)
[![Telegram.me](https://img.shields.io/twitter/url/http/shields.io.svg?style=social&label=Share+on+Telegram.me&logo=telegram)](https://telegram.me/share/url?url=https://github.com/alandefreitas/mdsplit/&text=mdsplit:%20split%20a%20bulky%20README.md%20into%20a%20nice%20documentation)
[![HackerNews](https://img.shields.io/twitter/url/http/shields.io.svg?style=social&label=Share+on+HackerNews&logo=y-combinator)](https://news.ycombinator.com/submitlink?u=https://github.com/alandefreitas/mdsplit/&t=mdsplit:%20split%20a%20bulky%20README.md%20into%20a%20nice%20documentation)

<!-- https://gist.github.com/jbroadway/2836900 -->
<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
<details>
<summary>Table of Contents</summary>

- [Gallery](#gallery)
- [Examples](#examples)
  - [Splitting your README.md](#splitting-your-readmemd)
  - [GitHub Pages](#github-pages)
  - [Github Actions](#github-actions)
  - [Testing Locally](#testing-locally)
- [Options](#options)
  - [Links to Repository](#links-to-repository)
  - [Input file](#input-file)
  - [Output directory](#output-directory)
  - [Remove HTML Tags](#remove-html-tags)
  - [Hiding sections from docs](#hiding-sections-from-docs)
- [Integration](#integration)
  - [Binaries](#binaries)
  - [Install from Source](#install-from-source)
- [Caveats](#caveats)
- [Contributing](#contributing)
- [Developers](#developers)

</details>
<!-- END doctoc generated TOC please keep comment here to allow auto update -->

## Gallery

These are some demonstrative projects that use mdsplit for their documentation:

|                 |     Documentation    |    README.md    |
|-----------------|----------------------|-----------------|
| Matplot++       | [URL](https://alandefreitas.github.io/matplotplusplus/) | [URL](https://github.com/alandefreitas/matplotplusplus/blob/master/README.md) |
| pareto-front    | [URL](https://alandefreitas.github.io/pareto-front/) | [URL](https://github.com/alandefreitas/pareto-front/blob/master/README.md) |
| BibExplorer    | [URL](https://alandefreitas.github.io/bibexplorer/) | [URL](https://github.com/alandefreitas/bibexplorer/blob/master/README.md) |
| mdsplit         | [URL](https://alandefreitas.github.io/mdsplit/) | [URL](https://github.com/alandefreitas/mdsplit/blob/master/README.md) |

You can visit these repositories and compare the documentation with the README.md files. 

Please let me know if you want to list your project here.

## Examples

### Splitting your README.md

Just run 

```
mdsplit -r username/repository
```

from your project root directory. 

`mdsplit` will split your `README.md` file into smaller files and save the results to the `docs` directory. 

### GitHub Pages

To use the new `.md` files with GitHub Pages to create the documentation:

* Go to settings and turn on GitHub Pages
* Set `./docs` as your root directory
* Run `mdsplit` on your root directory to save the files in `./docs`
* Go to `docs/_config.yml`:
    * Uncomment `#remote_theme: pmarsceill/just-the-docs`
    * Comment `theme: "just-the-docs"`
    * Adapt `docs/_config.yml` as needed

### Github Actions



### Testing Locally

To test the GitHub Pages locally, see the example of a Jekyll configuration file in `docs/_config.yml`.
 
 * Install Jekyll and Bundle.
 * Add `gem "github-pages", group: :jekyll_plugins` to you Gemfile (see `docs/Gemfile`)
 * Add `gem "just-the-docs"` to you Gemfile (see `docs/Gemfile`)
 * Adapt `docs/_config.yml` as needed
 * Run `bundle install` or `bundle update`
 * Run the jekyll server: `bundle exec jekyll serve`

## Options

### Links to Repository

Although all internal links in the repository work OK, not all of them work with github pages. In that case, links need to use the absolute repository link as parent path reference. 

For instance,

```markdown
[![example_fcontour_1](../contour_plots/fcontour/fcontour_1.svg)](examples/contour_plots/fcontour/fcontour_1.cpp)
```

should become

```markdown
[![example_fcontour_1](../contour_plots/fcontour/fcontour_1.svg)](https://github.com/alandefreitas/matplotplusplus/blob/master/examples/contour_plots/fcontour/fcontour_1.cpp)
```

so that the link works correctly on GitHub pages.

You can use the the option `--repository` or `-r` to provide the repository mdsplit should consider to generate these links:

```
mdsplit -r alandefreitas/matplotplusplus
```

https://github.com/alandefreitas/mdsplit

https://github.com/alandefreitas/mdsplit/blob/master/docs/COMPLETE_GALLERY.html#plot_1

### Input file

### Output directory

### Remove HTML Tags

### Hiding sections from docs

Use the comments `<!-- START mdsplit-ignore -->` and `<!-- END mdsplit-ignore -->` to ignore sections from your README.md. For instance, if you're reading this from [`README.md`](README.md) you will see this section has a subsection that will be completely ignored in the documentation. 

<!-- START mdsplit-ignore -->
#### Ignored section

This section will be completely ignored from the documentation.
<!-- END mdsplit-ignore -->

## Integration

### Binaries

Get the latest release from the [Release Page](https://GitHub.com/alandefreitas/mdsplit/releases/) or download the latest binaries from the [CI Artifacts](https://github.com/alandefreitas/mdsplit/actions?query=workflow%3A%22Build+mdsplit%22+event%3Apush).

### Install from Source

```bash
mkdir build
cmake -version
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS="-O2"
cmake --build . -j 2 --config Release
cmake --install .
cpack
```

On windows, replace `-O2` with `/O2`. You might need `sudo` for this last command.

## Caveats

It won't delete old files.

## Contributing

If contributing with code, please leave the pedantic mode ON (` -DBUILD_WITH_PEDANTIC_WARNINGS=ON`), use cppcheck, and clang-format.

<details markdown="1">
    <summary>Example: CLion</summary>
    
![CLion Settings with Pedantic Mode](docs/images/pedantic_clion.png)
    
</details>

## Developers

<!-- readme: collaborators,contributors -start --> 
<table>
<tr>
    <td align="center">
        <a href="https://github.com/alandefreitas">
            <img src="https://avatars0.githubusercontent.com/u/5369819?v=4" width="100;" alt="alandefreitas"/>
            <br />
            <sub><b>Alan De Freitas</b></sub>
        </a>
    </td></tr>
</table>
<!-- readme: collaborators,contributors -end -->

