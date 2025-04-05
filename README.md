# Fast-DDS-modern-cpp-api

This is a modern c++ api wrapper for the FastDDS-API.

## How to build

### Windows

Install FastDDS via installer.

```bash
mkdir build
cd build
cmake -DOPENSSL_INCLUDE_DIR="C:\Program Files\OpenSSL-Win64\include" ..
cmake --build . --config Release
```
