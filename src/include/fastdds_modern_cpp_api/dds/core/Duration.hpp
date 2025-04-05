#pragma once

#include <fastdds/rtps/common/Time_t.hpp>

#include <limits>
#include <cstdint>

namespace fastdds_modern_cpp_api {
namespace dds {
namespace core {

class Duration {

public:
    Duration(){}
    Duration(int32_t s, uint32_t ns): m_duration(s, ns) {

    }
    static Duration infinite() {
        return Duration(std::numeric_limits<int32_t>::max(), std::numeric_limits<uint32_t>::max());
    };

    operator eprosima::fastdds::dds::Duration_t() const {
        return m_duration;
    }

    int32_t sec;
    uint32_t nsec;

private:
    eprosima::fastdds::dds::Duration_t m_duration;

};

}
}
}