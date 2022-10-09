# filter test task

### Table of contents
- [Usage](#usage)
- [Features](#features)
- [Tuning](#tuning)


---
## Usage

Type `make test` to build project and perform tests from './tests' folder.

'filter.exe' will appear in './build' folder if the project is build by `make` or `make test` commands.

---
## Features

'./build/filter.map' file is generated during program linking to simplify further debugging.

---
## Tuning

Change value of `FILTER_MEMORY_CHUNK_DATA_SIZE_IN_CHARS` in './include/filter_config.h' to vary length of string stored in one chunk of data.

