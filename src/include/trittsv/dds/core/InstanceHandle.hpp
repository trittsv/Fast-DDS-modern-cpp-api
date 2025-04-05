#pragma once

#include <fastdds/dds/common/InstanceHandle.hpp>
#include <ostream>
#include <sstream>


namespace trittsv {
namespace dds {
namespace core {


class InstanceHandle {
public:
    InstanceHandle(){}
    InstanceHandle(const eprosima::fastdds::dds::InstanceHandle_t& handle) : m_handle(handle) {

    }
    bool is_nil() {
        return false;
    }
    operator eprosima::fastdds::dds::InstanceHandle_t() const {
        return m_handle;
    }

    std::string get_native_handle_string() const {
        std::stringstream ss;
        ss << m_handle;
        return ss.str();
    }

    friend std::ostream& operator<< (std::ostream& os, const InstanceHandle& handle) {
        os << handle.get_native_handle_string();
        return os;
    }



private:
    eprosima::fastdds::dds::InstanceHandle_t m_handle;
};


}
}
}