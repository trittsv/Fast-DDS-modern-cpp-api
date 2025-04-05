#pragma once

#include <fastdds_modern_cpp_api/dds/topic/Topic.hpp>
#include <fastdds_modern_cpp_api/dds/sub/DataReaderListener.hpp>
#include <fastdds_modern_cpp_api/dds/sub/Subscriber.hpp>
#include <fastdds_modern_cpp_api/dds/sub/qos/DataReaderQos.hpp>
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


template<typename T>
using LoanedSamples = std::vector<T>;

template <typename T>
class DataReader {

public:
    class Selector {
    public:
        Selector() {}
        Selector& state(const dds::sub::status::DataState& s) {
            return *this;
        }

        dds::sub::LoanedSamples<T> take() {
            return dds::sub::LoanedSamples<T>();
        }
    };

    DataReader(
        const dds::sub::Subscriber& sub,
        const dds::topic::Topic<T>& topic,
        const dds::sub::qos::DataReaderQos& qos,
        dds::sub::DataReaderListener<T>* listener,
        const dds::core::status::StatusMask& mask) {

        nativeReader = sub.m_subscriber->create_datareader(topic.nativeTopic, qos);
        if (nativeReader == nullptr) {
            throw std::runtime_error("DataReader initialization failed");
        }

    }

    void close() {

    }

    Selector select() {
        return m_selector;
    }

    eprosima::fastdds::dds::DataReader* nativeReader;

private:
    Selector m_selector;

};


} // namespace sub
}
}
