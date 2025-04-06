#pragma once

#include <fastdds_modern_cpp_api/dds/domain/DomainParticipant.hpp>
#include <fastdds_modern_cpp_api/dds/core/status/Status.hpp>

#include <fastdds/dds/topic/Topic.hpp>
#include <fastdds/dds/topic/qos/TopicQos.hpp>
#include <fastdds/dds/topic/TypeSupport.hpp>

#ifdef _MSC_VER
#include <Windows.h>
#elif defined(__GNUC__) || defined(__clang__)
#include <cxxabi.h>
#include <memory>
#endif

namespace fastdds_modern_cpp_api {
namespace dds {
namespace topic {
namespace qos {

class TopicQos {

public:
    TopicQos& operator<<(const eprosima::fastdds::dds::OwnershipQosPolicy& rhs) {
        nativeQos.ownership(rhs);
        return *this;
    }
    TopicQos& operator<<(const eprosima::fastdds::dds::DurabilityQosPolicy& rhs) {
        nativeQos.durability(rhs);
        return *this;
    }
    TopicQos& operator<<(const eprosima::fastdds::dds::ReliabilityQosPolicy& rhs) {
        nativeQos.reliability(rhs);
        return *this;
    }
    TopicQos& operator<<(const eprosima::fastdds::dds::HistoryQosPolicy& rhs) {
        nativeQos.history(rhs);
        return *this;
    }
    operator eprosima::fastdds::dds::TopicQos() const {
        return nativeQos;
    }

    eprosima::fastdds::dds::TopicQos nativeQos;
};

}


template <typename T>
class TopicListener;


template <typename T>
struct topic_type_name;

#ifdef _MSC_VER
template <typename T>
struct topic_type_name {
    static std::string value() {
        std::string result = typeid(T).name();
        if (result.find("class ") == 0) {
            result.erase(0, 6);
        }
        return result;
    }
};
#endif

#if defined(__GNUC__) || defined(__clang__)
template <typename T>
struct topic_type_name {
    static std::string value() {
        int status;
        char* name = abi::__cxa_demangle(typeid(T).name(), 0, 0, &status);
        std::string result(name);
        std::free(name);
        return result;
    }
};
#endif

#define REGISTER_PUBSUB_TYPE(TypeName, Participant) \
    eprosima::fastdds::dds::TypeSupport type_(new TypeName##PubSubType()); type_.register_type(Participant)

template <typename T>
class Topic {

public:
    Topic(const dds::domain::DomainParticipant& dp,
            const std::string& name,
            const dds::topic::qos::TopicQos& qos,
            fastdds_modern_cpp_api::dds::topic::TopicListener<T>* listener,
            const dds::core::status::StatusMask& mask) {

        //fastdds_modern_cpp_api::dds::topic::register_type_name<T>::register_type(dp.m_pariticpant); // second registering will have no effect, but will not issue any error.
        //type_.register_type(dp.m_pariticpant);

        nativeTopic = dp.get_participant()->create_topic(name, topic_type_name<T>::value(), qos.nativeQos);
        if (nativeTopic == nullptr) {
            throw std::runtime_error("Topic initialization failed");
        }
    }

    eprosima::fastdds::dds::Topic* nativeTopic;
private:
    //eprosima::fastdds::dds::TypeSupport type_;

};

template <typename T>
class TopicListener {

public:
    // currently not implemented by FastDDS
    virtual void on_inconsistent_topic(
        dds::topic::Topic<T>& topic, //dds::core::status::InconsistentTopicStatus const& status) {
        dds::core::status::InconsistentTopicStatus const& status) {

    }
};

}
}
}
