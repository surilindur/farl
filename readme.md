# Filesystem Access Redirection Layer

Experimental library for redirecting filesystem access in a somewhat configurable manner. The main motivation behind this learning project is to find a way to make programs see files in certain paths without having to actually copy, move or symlink those files into the intended paths.

The library is written in C and compiles with C99 using Clang 13. There is a makefile available for building the project. The project has the following dependencies:

* [tidwall/btree.c](https://github.com/tidwall/btree.c) for the B+ tree

There is a simple stub for testing whether the thing compiles and works, that can be used as follows, within the [testing](./testing) folder:

    make all
    FARL_LOG=./test.log FARL_YAML=./test.yaml ./test

The following compile-time definitions can be toggled on if needed:

| Build flag           | Effect                                                     |
|:---------------------|:-----------------------------------------------------------|
| `FARL_LOG_STDOUT`    | Enables logging to stdout                                  |
| `FARL_LOG_RESOLVING` | Enables logging of virtual to physical resolving           |
| `FARL_LOG_BUILDING`  | Enables logging of path mappings while reading from config |
| `FARL_LOG_PATHS`     | Enables logging of path resolving                          |

The tool is driven using the following environment variables at runtime:

| Environment variable | Optional | Purpose                                          |
|:---------------------|:---------|:-------------------------------------------------|
| `FARL_MAPPINGS`      | no       | Path to the `YAML` file with path mappings in it |
| `FARL_LOG`           | yes      | Path to the logfile to write to                  |

Please note that the project is first and foremost an experimental learning tool, rather than something useful. Please do not use this with anything that is supposed to work.
