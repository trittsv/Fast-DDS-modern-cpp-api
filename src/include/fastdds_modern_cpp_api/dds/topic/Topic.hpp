#pragma once

#include <fastdds_modern_cpp_api/dds/domain/DomainParticipant.hpp>
#include <fastdds_modern_cpp_api/dds/core/status/Status.hpp>
#include <fastdds_modern_cpp_api/dds/core/Exception.hpp>
#include <fastdds_modern_cpp_api/dds/topic/qos/TopicQos.hpp>

#include <fastdds/dds/topic/Topic.hpp>
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

template <typename T>
class Topic {

public:
    Topic(dds::core::NullType null): nativeTopic(nullptr) {

    }

    Topic(const dds::domain::DomainParticipant& dp,
            const std::string& name,
            const dds::topic::qos::TopicQos& qos,
            fastdds_modern_cpp_api::dds::topic::TopicListener<T>* listener,
            const dds::core::status::StatusMask& mask) {

        nativeTopic = dp.get_participant()->create_topic(name, topic_type_name<T>::value(), qos.nativeQos);
        if (nativeTopic == nullptr) {
            throw std::runtime_error("Topic initialization failed");
        }
    }

    eprosima::fastdds::dds::Topic* get_topic() const {
        return nativeTopic;
    }

    bool operator==(const dds::core::NullType&) const {
        return nativeTopic == nullptr;
    }

    Topic<T>& operator=(Topic<T>& other) {
        if (this != &other) {
            nativeTopic = other.nativeTopic;
        }
        return *this;
    }

private:
    eprosima::fastdds::dds::Topic* nativeTopic;

};

template<typename T>
inline T find(const dds::domain::DomainParticipant& dp, const std::string& topicName) {
    auto* foundTopic = dp.get_participant()->find_topic(topicName, eprosima::fastdds::dds::Duration_t(1, 0));
    if (foundTopic == nullptr) {
        return T(dds::core::NullType());
    } else {
        return T(foundTopic);
    }
}

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
