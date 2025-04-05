#pragma once

#include <fastdds/dds/subscriber/ReadCondition.hpp>
#include <fastdds/dds/subscriber/Subscriber.hpp>
#include <fastdds/dds/subscriber/SampleInfo.hpp>
#include <fastdds/dds/subscriber/qos/DataReaderQos.hpp>
#include <fastdds/dds/subscriber/DataReaderListener.hpp>
#include <fastdds/dds/subscriber/InstanceState.hpp>
#include <fastdds/dds/subscriber/qos/DataReaderQos.hpp>
#include <fastdds/dds/subscriber/qos/SubscriberQos.hpp>
#include <fastdds/dds/subscriber/SampleState.hpp>
#include <fastdds/dds/subscriber/ViewState.hpp>
#include <fastdds/dds/subscriber/DataReader.hpp>
#include <fastdds/dds/subscriber/SubscriberListener.hpp>


namespace fastdds_modern_cpp_api {
namespace dds {
namespace sub {
namespace qos {


class DataReaderQos {

public:
    DataReaderQos& operator<<(const eprosima::fastdds::dds::OwnershipQosPolicy& rhs) {
        m_qos.ownership(rhs);
        return *this;
    }
    DataReaderQos& operator<<(const eprosima::fastdds::dds::DurabilityQosPolicy& rhs) {
        m_qos.durability(rhs);
        return *this;
    }
    DataReaderQos& operator<<(const eprosima::fastdds::dds::ReliabilityQosPolicy& rhs) {
        m_qos.reliability(rhs);
        return *this;
    }
    DataReaderQos& operator<<(const eprosima::fastdds::dds::HistoryQosPolicy& rhs) {
        m_qos.history(rhs);
        return *this;
    }
    operator eprosima::fastdds::dds::DataReaderQos() const {
        return m_qos;
    }
private:
    eprosima::fastdds::dds::DataReaderQos m_qos;
};


}
}
}
}