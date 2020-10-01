---
layout: default
title: mdsplit
nav_order: 1
has_children: false
has_toc: false
---
# mdsplit

[![Build Status](https://img.shields.io/github/workflow/status/alandefreitas/mdsplit/Build%20mdsplit?event=push&label=Build&logo=Github-Actions)](https://github.com/alandefreitas/mdsplit/actions?query=workflow%3A%22Build+mdsplit%22+event%3Apush)
[![Latest Release](https://img.shields.io/github/release/alandefreitas/mdsplit.svg?label=Download)](https://GitHub.com/alandefreitas/mdsplit/releases/)
[![Documentation](https://img.shields.io/website-up-down-green-red/http/alandefreitas.github.io/mdsplit.svg?label=Documentation)](https://alandefreitas.github.io/mdsplit/)

![mdsplit](https://img.icons8.com/nolan/2x/split-files.png)

`mdsplit` is a tool to split a bulky markdown file into smaller files. The main purpose of `mdsplit` is to generate documentation with GitHub Pages from README.md files. It can be integrated with GitHub actions to regenerate the documentation whenever the README.md file is updated.

See a [LIVE DEMO](https://alandefreitas.github.io/mdsplit/) and compare it with this [README.md](https://github.com/alandefreitas/mdsplit/blob/master/README.md) file.

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



- [Gallery]()
- [Examples]()
  - [Splitting your README.md]()
  - [GitHub Pages]()
  - [Github Actions]()
  - [Testing Locally]()
- [Options]()
  - [Links to Repository]()
  - [Input file]()
  - [Output directory]()
  - [Remove HTML Tags]()
  - [Hiding sections from docs]()
- [Integration]()
  - [Binaries]()
  - [Install from Source]()
- [Caveats]()
- [Contributing]()
- [Developers]()


<!-- Generated with mdsplit: https://github.com/alandefreitas/mdsplit -->
