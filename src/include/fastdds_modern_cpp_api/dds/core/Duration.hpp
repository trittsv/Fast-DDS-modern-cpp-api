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
    Duration(int32_t s, uint32_t ns): sec(s), nsec(ns) {

    }
    static Duration infinite() {
        return Duration(std::numeric_limits<int32_t>::max(), std::numeric_limits<uint32_t>::max());
    };

    eprosima::fastdds::dds::Duration_t toFastDdsDuration() {
        return eprosima::fastdds::dds::Duration_t(sec, nsec);
    }

    int32_t sec;
    uint32_t nsec;
};

}
}
}