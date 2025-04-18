#pragma once

#include <fastdds_modern_cpp_api/dds/core/InstanceHandle.hpp>
#include <fastdds_modern_cpp_api/dds/core/status/Status.hpp>
#include <fastdds_modern_cpp_api/dds/pub/DataWriterListener.hpp>
#include <fastdds_modern_cpp_api/dds/pub/qos/DataWriterQos.hpp>
#include <fastdds_modern_cpp_api/dds/pub/Publisher.hpp>
#include <fastdds_modern_cpp_api/dds/topic/Topic.hpp>

#include <fastdds/dds/core/condition/Condition.hpp>
#include <fastdds/dds/core/Entity.hpp>
#include <fastdds/dds/core/ReturnCode.hpp>
#include <fastdds/dds/core/policy/QosPolicies.hpp>
#include <fastdds/dds/core/status/BaseStatus.hpp>
#include <fastdds/dds/core/status/SubscriptionMatchedStatus.hpp>
#include <fastdds/dds/core/status/StatusMask.hpp>
#include <fastdds/dds/publisher/qos/DataWriterQos.hpp>
#include <fastdds/dds/publisher/qos/PublisherQos.hpp>
#include <fastdds/dds/publisher/DataWriter.hpp>
#include <fastdds/dds/common/InstanceHandle.hpp>
#include <fastdds/dds/xtypes/exception/Exception.hpp>
#include <fastdds/rtps/common/Time_t.hpp>

#include <map>


namespace fastdds_modern_cpp_api {
namespace dds {
namespace pub {


template <typename T>
class DataWriter {

public:
    DataWriter(
        const dds::pub::Publisher& pub,
        const dds::topic::Topic<T>& topic,
        const dds::pub::qos::DataWriterQos& qos,
        dds::pub::DataWriterListener<T>* listener,
        const dds::core::status::StatusMask& mask){

        nativewriter = pub.m_publisher->create_datawriter(topic.get_topic(), qos);
        if (nativewriter == nullptr) {
            throw std::runtime_error("DataWriter initialization failed");
        }
    }

    void write(const T& sample) {
        auto ret = nativewriter->write(&sample);
        if (ret != 0) {
            throw std::runtime_error("DataWriter failed to write, return code: " + std::to_string(ret));
        }
    }

    dds::core::InstanceHandle lookup_instance(const T& key) const {
        return dds::core::InstanceHandle((void*)&key);
    }

    void dispose_instance(dds::core::InstanceHandle& handle){
        auto ret = nativewriter->dispose(handle.get_data(), handle);
        if (ret != 0) {
            throw std::runtime_error("DataWriter failed to unregister_instance, return code: " + std::to_string(ret));
        }
    }

    void unregister_instance(dds::core::InstanceHandle& handle) {
        auto ret = nativewriter->unregister_instance(handle.get_data(), handle);
        if (ret != 0) {
            throw std::runtime_error("DataWriter failed to unregister_instance, return code: " + std::to_string(ret));
        }
    }

    void close() {

    }

    eprosima::fastdds::dds::DataWriter* nativewriter;

private:

    std::map<eprosima::fastdds::rtps::InstanceHandle_t, T> m_instanceIds;
    
};

}
}
}
