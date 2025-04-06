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


class SampleInfo {

public:
    SampleInfo(){}
    SampleInfo(eprosima::fastdds::dds::SampleInfo info): m_sampleInfo(info), m_state(info.instance_state, info.view_state, info.sample_state) {

    }

    dds::sub::status::DataState& state() {
        return m_state;
    }

    bool valid() {
        return m_sampleInfo.valid_data;
    }

private:
    eprosima::fastdds::dds::SampleInfo m_sampleInfo;
    dds::sub::status::DataState m_state;
};


}
}
}
