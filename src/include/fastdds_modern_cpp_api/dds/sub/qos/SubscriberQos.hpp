#pragma once

#include <fastdds_modern_cpp_api/dds/core/policy/CorePolicy.hpp>

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


namespace fastdds_modern_cpp_api {
namespace dds {
namespace sub {
namespace qos {

class SubscriberQos {

public:
    SubscriberQos() : m_qos(eprosima::fastdds::dds::SUBSCRIBER_QOS_DEFAULT) {
        
    }

    SubscriberQos(eprosima::fastdds::dds::SubscriberQos qos) : m_qos(qos) {
        
    }

    SubscriberQos& operator<<(const fastdds_modern_cpp_api::dds::core::policy::Partition& rhs) {
        m_qos.partition().push_back(rhs.m_name.c_str());
        return *this;
    }

    operator eprosima::fastdds::dds::SubscriberQos() const {
        return m_qos;
    }

private:
    eprosima::fastdds::dds::SubscriberQos m_qos;

};

}
}
}
}
