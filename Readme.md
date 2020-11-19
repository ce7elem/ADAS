# Bolerplate for a C-project
> _For lazy people._

A clean and simple boilerplate for C-project, `make` rules and a specially crafted doc generator from source code comments.


## Dependencies

- make
- gcc (or you can edit the `CC` varable in `config/make.global`)
- golang (only used in the doc generator)

## Project architecture
> A Makefile Odyssey

### Tree view

- Root: holds the **main** src file
  - Makefile: the top Makefile
  - main-src-file
  - src-file1
  - src1: holds some src dirs and files
    - Makefile: rules to make objects in current dir
    - src-file2
    - src-file3
    - sub-src-dir1: holds some src dirs and files
      - src-file4
      - src-file5
      - Makefile: rules to make objects in current dir
  - ...

To follow this architecture, you may want to :
1. Add all the src folders to variable `DIRS`, and all the objects in the current folder to variable `OBJS`
2. Create Makefile in each sub src dir, following the template shown in *Template/src/Makefile*, or *Example/.../Makefile*


<details><summary>More on the makefile stategy</summary>
<p>

### Work flow

When executing `make` at the root folder, it will first look into the `TARGET` file, which depend on all the objects `ALL_OBJS` specified by the PHONY target `find-all-objs`.

If any of the objects are not updated, it will be re-generated at its own folder, and `TARGET` will use it for linking.

When linking, compiler link all the object files under all the src dirs, recursively. Since there are path prefixs, it is ok to have filename conflict in different dir(like having *src1/f1.c* and *src2/f1.c* is ok)

### Discussions

1. Why a Makefile in each src dir ?
    1. This gives us the chance to maintain the objects under their sources' dirs, which further prevent the filename conflict under different path, since the objects will have a path prefix to eliminate the filename conflict.
1. Why manually specify the `DIRS` and `OBJS` ?
    1. Just in case some source file are not to be compiled(e.g. a test file named `test.c` may not need to be compiled), or some dirs does not contain any source files(e.g. a dir `doc` contains documents), nor in their sub-dirs.
    1. It's easy to add some auto-find rules for `DIRS` and `OBJS`, using `wildcard`.
    1. For simplicity, we do not provide this kind of auto-find which may cause some trouble unintentionally.
1. Why use a `submake.global`, but put all rules in `make.global`  ?
    1. The `all` and `clean` rules in sub-dirs is different from the root-dir, these are to specified seperately.
1. Why re-link and re-generate the target even if all the objects are updated ?
    1. Since the target`$(TARGET)` depend on some PHONY targets, it may be re-generated even all non-PHONY dependencies are updated. But consider about the simplicity of the Makefile, this redundency is endurable. If anyone has a better idea, feel free to raise an issue or pull-request.

</p>
</details>

## Toubleshooting

* Running `make` may not work properly if the path of the projet contains blank spaces

## References

* (Makefile)[https://github.com/TheNetAdmin/Makefile-Templates]
* Documentation
  * (HTML)[https://github.com/egoist/docute]