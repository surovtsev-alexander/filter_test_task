# filter test task

## Table of contents
- [Usage](#usage)
- [Features](#features)
- [Tuning](#tuning)
- [Environment](#environment)

---
## Usage

Type `make test` to build project and perform tests from './tests' folder.

'filter.exe' will appear in './build' folder if the project is build by `make` or `make test` commands.

---
## Features

'./build/filter.map' file is generated during the program linking to simplify debugging.

---
## Tuning

Change value of `FILTER_MEMORY_CHUNK_DATA_SIZE_IN_CHARS` in './include/filter_config.h' to vary length of string stored in one chunk of data.

---
## Environment

Tested in:
- Windows 10: Cygwin (gcc, make, vim, ctags);
- Ubuntu 22.04.1 LST (required package: build-essential).
