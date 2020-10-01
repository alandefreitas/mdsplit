# mdsplit

`mdsplit` is a tool to split a bulky markdown file into smaller files. The main purpose of `mdsplit` is to generate documentation with GitHub Pages from README.md files. It can be integrated with GitHub actions to regenerate the documentation whenever the README.md file is updated.

<!-- https://gist.github.com/jbroadway/2836900 -->
<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
<details>
<summary>Table of Contents</summary>

- [Running mdsplit](#running-mdsplit)
  - [Splitting README.md](#splitting-readmemd)
  - [GitHub Pages](#github-pages)
  - [Test Locally](#test-locally)
- [Contributing](#contributing)
  - [Developers](#developers)

</details>
<!-- END doctoc generated TOC please keep comment here to allow auto update -->

## Running mdsplit

### Splitting README.md

Just run 

```
mdsplit
```

from your project root directory. `mdsplit` will split your `README.md` file into smaller files. The results will go to the documentation directory.

### GitHub Pages

To use the new .md files with GitHub Pages:

* Go to settings and turn on GitHub Pages
* Set `./docs` as your root directory
* Run `mdsplit` on your root directory to save the files in `./docs`
* Go to `docs/_config.yml`:
    * Uncomment `#remote_theme: pmarsceill/just-the-docs`
    * Comment `theme: "just-the-docs"`
    * Adapt `docs/_config.yml` as needed

### Test Locally

To test the GitHub Pages locally, see the example of a Jekyll configuration file in `docs/_config.yml`.
 
 * Install Jekyll and Bundle.
 * Add `gem "github-pages", group: :jekyll_plugins` to you Gemfile (see `docs/Gemfile`)
 * Add `gem "just-the-docs"` to you Gemfile (see `docs/Gemfile`)
 * Adapt `docs/_config.yml` as needed
 * Run `bundle install` or `bundle update`
 * Run the jekyll server: `bundle exec jekyll serve`

## Contributing

If contributing with code, please leave the pedantic mode ON (` -DBUILD_WITH_PEDANTIC_WARNINGS=ON`), use cppcheck, and clang-format.

<details markdown="1">
    <summary>Example: CLion</summary>
    
![CLion Settings with Pedantic Mode](docs/images/pedantic_clion.png)
    
</details>

### Developers

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
