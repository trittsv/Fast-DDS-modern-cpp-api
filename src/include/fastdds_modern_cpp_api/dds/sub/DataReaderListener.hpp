#pragma once

#include <fastdds_modern_cpp_api/dds/sub/DataReader.hpp>
#include <fastdds_modern_cpp_api/dds/core/status/Status.hpp>

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


template <typename T>
class DataReader;

template <typename T>
class DataReaderListener {

public:

    virtual void on_data_available(dds::sub::DataReader<T>& reader) {

    }

    virtual void on_liveliness_changed(
        dds::sub::DataReader<T>& reader, const dds::core::status::LivelinessChangedStatus& status) {

    }

    virtual void on_requested_deadline_missed(
        dds::sub::DataReader<T>& reader, const eprosima::fastdds::dds::RequestedDeadlineMissedStatus& status) {

    }

    virtual void on_requested_incompatible_qos(
        dds::sub::DataReader<T>& reader,
        const dds::core::status::RequestedIncompatibleQosStatus& status) {
    
    }

    virtual void on_sample_lost(dds::sub::DataReader<T>& reader, const eprosima::fastdds::dds::SampleLostStatus& status) {

    }

    virtual void on_sample_rejected(dds::sub::DataReader<T>& reader, const eprosima::fastdds::dds::SampleRejectedStatus& status) {

    }

    virtual void on_subscription_matched(
        dds::sub::DataReader<T>& reader, const dds::core::status::SubscriptionMatchedStatus& status) {

    }
};


}
}
}