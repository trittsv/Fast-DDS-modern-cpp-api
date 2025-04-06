# Fast-DDS-modern-cpp-api

This is a [ISO/IEC C++ PSM](https://www.omg.org/spec/DDS-PSM-Cxx/) (aka modern c++ api) wrapper for the FastDDS-API.

## Example

```cpp
#include <fastdds_modern_cpp_api/dds/dds.hpp>

int main(int argc, char** argv) {

    namespace dds = fastdds_modern_cpp_api::dds;

    try {

        dds::domain::DomainParticipant participant(0);

    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
```

For more examples see subfolder `examples`.

## How to build

### Windows

Install FastDDS via installer.

```bash
mkdir build
cd build
cmake -DOPENSSL_INCLUDE_DIR="C:\Program Files\OpenSSL-Win64\include" ..
cmake --build . --config Release
```

## Contributing

Everyone is welcome to participate, just make a pull-request.
