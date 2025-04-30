#pragma once

#include <fastdds_modern_cpp_api/dds/domain/DomainParticipant.hpp>
#include <fastdds_modern_cpp_api/dds/core/status/Status.hpp>

#include <fastdds/dds/topic/qos/TopicQos.hpp>


namespace fastdds_modern_cpp_api {
namespace dds {
namespace topic {
namespace qos {

class TopicQos {

public:
    TopicQos() : nativeQos(/*eprosima::fastdds::dds::SUBSCRIBER_QOS_DEFAULT*/) {
            
    }

    TopicQos(eprosima::fastdds::dds::TopicQos qos) : nativeQos(qos) {
        
    }

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

    TopicQos& operator<<(const fastdds_modern_cpp_api::dds::core::policy::DataRepresentation& rhs) {
        nativeQos.representation() = rhs;
        return *this;
    }

    TopicQos& operator<<(const fastdds_modern_cpp_api::dds::core::policy::TypeConsistencyEnforcement& rhs) {
        return *this;
    }

    operator eprosima::fastdds::dds::TopicQos&() {
        return nativeQos;
    }

    eprosima::fastdds::dds::TopicQos nativeQos;
};

}
}
}
}
