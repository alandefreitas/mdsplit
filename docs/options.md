---
layout: default
title: Options
nav_order: 4
has_children: true
has_toc: false
---
# Options

Run `mdsplit` with the `--help` (or `-h`) option to see all command-line options:

```bash
mdsplit -h
```

```console
Generate documentation from README.md files
Usage:
  mdsplit -i input_directory -o output_directory -r username/repository

 File options:
  -i, --input arg       Input file (default: README.md)
  -o, --output arg      Output directory (default: docs)
  -r, --repository arg  Output repository

 Behaviour options:
  -l, --level arg        Max level for which we should split the file
                         (default: 6)
  -c, --clear-html arg   List of HTML tags mdsplit should clear (default:
                         details,summary)
  -t, --toc              Create a table of contents for the new files
                         (default: true)
  -j, --jekyll-escape    Escape consecutive "{ {"s for Jekyll processing
                         (default: true)
      --header-reindent  Reindent headers to match the new files (default:
                         true)
  -f, --front-matter     Include a front-matter in the new files (default:
                         true)
  -u, --url-update       Update relative URLs to their new relative paths
                         (default: true)
      --remove-auto-toc  Remove automatic table of contents (default: true)
      --trace            Trace commands (default: true)

 Help options:
  -h, --help     Print usage
  -v, --version  Print version
```



- [Links to Repository](options/links-to-repository.md)
- [Input file](options/input-file.md)
- [Output directory](options/output-directory.md)
- [Remove HTML Tags](options/remove-html-tags.md)
- [Front matter ](options/front-matter-.md)
- [Hiding sections from docs](options/hiding-sections-from-docs.md)


<!-- Generated with mdsplit: https://github.com/alandefreitas/mdsplit -->
