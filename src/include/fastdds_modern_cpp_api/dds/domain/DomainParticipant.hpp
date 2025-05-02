#pragma once

#include <fastdds_modern_cpp_api/dds/core/InstanceHandle.hpp>

#include <fastdds_modern_cpp_api/dds/sub/qos/SubscriberQos.hpp>
#include <fastdds_modern_cpp_api/dds/sub/qos/DataReaderQos.hpp>
#include <fastdds_modern_cpp_api/dds/pub/qos/DataWriterQos.hpp>
#include <fastdds_modern_cpp_api/dds/pub/qos/PublisherQos.hpp>
#include <fastdds_modern_cpp_api/dds/topic/Topic.hpp>
#include <fastdds_modern_cpp_api/dds/topic/qos/TopicQos.hpp>

#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/dds/topic/Topic.hpp>
#include <fastdds/dds/subscriber/ReadCondition.hpp>
#include <fastdds/dds/subscriber/Subscriber.hpp>
#include <fastdds/dds/subscriber/SampleInfo.hpp>
#include <fastdds/dds/subscriber/qos/DataReaderQos.hpp>
#include <fastdds/dds/subscriber/DataReaderListener.hpp>
#include <fastdds/dds/subscriber/InstanceState.hpp>
#include <fastdds/dds/subscriber/qos/SubscriberQos.hpp>
#include <fastdds/dds/subscriber/SampleState.hpp>
#include <fastdds/dds/subscriber/ViewState.hpp>
#include <fastdds/dds/subscriber/DataReader.hpp>
#include <fastdds/dds/subscriber/SubscriberListener.hpp>

#include <map>


namespace fastdds_modern_cpp_api {
namespace dds {
namespace domain {
namespace qos {

class DomainParticipantQos {

public:

    DomainParticipantQos() : m_qos(eprosima::fastdds::dds::PARTICIPANT_QOS_DEFAULT){
                
    }

    DomainParticipantQos(eprosima::fastdds::dds::DomainParticipantQos qos) : m_qos(qos) {
        
    }

    operator eprosima::fastdds::dds::DomainParticipantQos&() {
        return m_qos;
    }

private:
    eprosima::fastdds::dds::DomainParticipantQos m_qos;
};

} // namespace qos

class DomainParticipant {

public:
    DomainParticipant(uint32_t id) {
        init(id);
    }

    DomainParticipant(uint32_t id, fastdds_modern_cpp_api::dds::domain::qos::DomainParticipantQos qos) {
        init(id, qos);
    }

    ~DomainParticipant() {
        if (nullptr != m_pariticpant) {
            m_pariticpant->delete_contained_entities();
            eprosima::fastdds::dds::DomainParticipantFactory::get_instance()->delete_participant(m_pariticpant);
        }
    }

    const dds::core::InstanceHandle& instance_handle() const {
        return dds::core::InstanceHandle(m_pariticpant->get_instance_handle());
    }

    eprosima::fastdds::dds::DomainParticipant* get_participant() const {
        return m_pariticpant;
    }

    template <typename T>
    void register_type() {
        auto* pubSubType = new T();
        auto typeSupport = eprosima::fastdds::dds::TypeSupport(pubSubType);
        m_typeSupports[typeSupport.get_type_name()] = typeSupport;
        m_typeSupports[typeSupport.get_type_name()].register_type(m_pariticpant);
        DomainParticipant::setIsKeyedTopic(typeSupport.get_type_name(), pubSubType->is_compute_key_provided);
    }

    static void setIsKeyedTopic(const std::string& typeName, bool isKeyed) {
        getKeyedTopicMap()[typeName] = isKeyed;
    }

    static bool getIsKeyedTopic(const std::string& typeName) {
        if (getKeyedTopicMap().count(typeName) >= 1) {
            return getKeyedTopicMap()[typeName];
        }
        return false;
    }

    static fastdds_modern_cpp_api::dds::domain::qos::DomainParticipantQos default_participant_qos() {
        eprosima::fastdds::dds::DomainParticipantQos qos = eprosima::fastdds::dds::PARTICIPANT_QOS_DEFAULT;
        auto ret = eprosima::fastdds::dds::DomainParticipantFactory::get_instance()->get_default_participant_qos(qos);
        if (ret != 0) {
            throw std::runtime_error("Failed to get_default_participant_qos " + std::to_string(ret));
        }
        return dds::domain::qos::DomainParticipantQos(qos);
    }

    fastdds_modern_cpp_api::dds::sub::qos::SubscriberQos default_subscriber_qos() const {
        eprosima::fastdds::dds::SubscriberQos sub_qos = eprosima::fastdds::dds::SUBSCRIBER_QOS_DEFAULT;
        auto ret = m_pariticpant->get_default_subscriber_qos(sub_qos);
        if (ret != 0) {
            throw std::runtime_error("Failed to get_default_subscriber_qos " + std::to_string(ret));
        }
        return dds::sub::qos::SubscriberQos(sub_qos);
    }

    fastdds_modern_cpp_api::dds::pub::qos::PublisherQos default_publisher_qos() const {
        eprosima::fastdds::dds::PublisherQos pub_qos = eprosima::fastdds::dds::PUBLISHER_QOS_DEFAULT;
        auto ret = m_pariticpant->get_default_publisher_qos(pub_qos);
        if (ret != 0) {
            throw std::runtime_error("Failed to get_default_publisher_qos " + std::to_string(ret));
        }
        return dds::pub::qos::PublisherQos(pub_qos);
    }

    fastdds_modern_cpp_api::dds::topic::qos::TopicQos default_topic_qos() {
        eprosima::fastdds::dds::TopicQos topic_qos = eprosima::fastdds::dds::TOPIC_QOS_DEFAULT;
        auto ret = m_pariticpant->get_default_topic_qos(topic_qos);
        if (ret != 0) {
            throw std::runtime_error("Failed to get_default_topic_qos " + std::to_string(ret));
        }
        return fastdds_modern_cpp_api::dds::topic::qos::TopicQos(topic_qos);
    }

private:
    void init(uint32_t id, fastdds_modern_cpp_api::dds::domain::qos::DomainParticipantQos& qos) {
        auto factory = eprosima::fastdds::dds::DomainParticipantFactory::get_instance();
        m_pariticpant = factory->create_participant(id, qos);
        if (m_pariticpant == nullptr) {
            throw std::runtime_error("Participant initialization failed");
        }
    }

    void init(uint32_t id) {
        init(id, m_qos);
    }

    static std::map<std::string, bool>& getKeyedTopicMap() {
        static std::map<std::string, bool> s_keyedTopics;
        return s_keyedTopics;
    }

    eprosima::fastdds::dds::DomainParticipant* m_pariticpant;
    fastdds_modern_cpp_api::dds::domain::qos::DomainParticipantQos m_qos;

    std::map<std::string, eprosima::fastdds::dds::TypeSupport> m_typeSupports;
};


} // namepsace domain
}
}
