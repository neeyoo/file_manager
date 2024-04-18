# Timestamped Data File Manager

|  General  | [![c++17](https://img.shields.io/badge/standard-C++17-blue.svg?style=flat&logo=c%2B%2B)](https://isocpp.org) [![License](https://img.shields.io/badge/License-BSD_3--Clause-orange.svg)](./LICENSE) |
| :-------: | :----------------------------------------------------------: |

## Usage
This C++ library is used for managing timestamped datefiles (ex. sensor information) stored in a certain folder. Due to the fact that there datafile can take a lot of disc space which runing the hardware system, this **Data File Manager** can be used for monitoring if the total size of the datafiles exceeds a certain threshhould.

Managed files have a name struction of [prefix][timestamp][extention] (ex. `telemetry_2023-11-09T10:59:26Z.mcap` with `telemetry_` as prefixe, `2023-11-09T10:59:26Z` as timestamp and `.mcap` as extention). **prefix and extention are optional** but **a valid timestamp is obligatory!!!**, otherwise the file will be ignored and an error information will be generated.

**Note:** The timestamp in the file name is used to determine whether it's old or new. (the reason to not use embeded last file written time is to prevent file has been modified after creation)

This library provide the class `TimestampedFileManager` which can be initialized by giving following argument to the constructor:
- `const std::string &directory_path`: the path to the directory including datefiles to be managed
- `const std::string &timestamp_format`: timestamp format in the file name
- `const long long &max_size`: maximum allowable size of all datafiles
- `const std::string &file_prefix`: prefix in the datafile name (optional, can be just empty string)
- `const std::string &file_suffix`: extension of the datafile (optional, can be just empty string)

## Build from source
1. Use cmake to build
```bash
mkdir build && cd build
cmake ..
make
```
2. run `ctest` to see if test cases are passed.

