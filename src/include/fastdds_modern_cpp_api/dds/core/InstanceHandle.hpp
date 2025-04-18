#pragma once

#include <fastdds/dds/common/InstanceHandle.hpp>
#include <ostream>
#include <sstream>


namespace fastdds_modern_cpp_api {
namespace dds {
namespace core {


class InstanceHandle {
public:
    InstanceHandle(){}
    InstanceHandle(void* data) : m_data(data) {}
    InstanceHandle(const eprosima::fastdds::dds::InstanceHandle_t& handle) : m_handle(handle) {

    }
    bool is_nil() {
        return !m_handle.isDefined();
    }
    operator const eprosima::fastdds::dds::InstanceHandle_t&() {
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

    void* get_data() const {
        return m_data;
    }



private:
    eprosima::fastdds::dds::InstanceHandle_t m_handle;
    void* m_data;
};


}
}
}
