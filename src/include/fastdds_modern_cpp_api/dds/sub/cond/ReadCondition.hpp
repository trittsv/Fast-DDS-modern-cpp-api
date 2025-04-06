#pragma once

#include <fastdds_modern_cpp_api/dds/sub/status/DataState.hpp>
#include <fastdds_modern_cpp_api/dds/sub/DataReader.hpp>

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
namespace cond {

class ReadCondition {

public:
    ReadCondition(fastdds_modern_cpp_api::dds::sub::IDataReader& reader, fastdds_modern_cpp_api::dds::sub::status::DataState dataState, std::function<void()> callback): m_callback(callback) {

        m_readCondition = reader.getReader()->create_readcondition(
            eprosima::fastdds::dds::SampleStateKind::NOT_READ_SAMPLE_STATE,
            eprosima::fastdds::dds::ANY_VIEW_STATE,
            eprosima::fastdds::dds::ANY_INSTANCE_STATE
    );

    }

    std::function<void()> m_callback;
    eprosima::fastdds::dds::ReadCondition* m_readCondition;
};


}
}
}
}