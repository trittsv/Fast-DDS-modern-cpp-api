#pragma once

#include <fastdds_modern_cpp_api/dds/topic/Topic.hpp>
#include <fastdds_modern_cpp_api/dds/sub/DataReaderListener.hpp>
#include <fastdds_modern_cpp_api/dds/sub/Subscriber.hpp>
#include <fastdds_modern_cpp_api/dds/sub/SampleInfo.hpp>
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
class LoanedSample {

public:
    LoanedSample(){}
    LoanedSample(fastdds_modern_cpp_api::dds::sub::SampleInfo sampleInfo, T data) : m_sampleInfo(sampleInfo), m_data(data) {
        
    }

    fastdds_modern_cpp_api::dds::sub::SampleInfo& info() {
        return m_sampleInfo;
    }

    T& data() {
        return m_data;
    }

private:
    fastdds_modern_cpp_api::dds::sub::SampleInfo m_sampleInfo;
    T m_data;
};

template<typename T>
using LoanedSamples = std::vector<LoanedSample<T>>;


class IDataReader {
public:
    virtual eprosima::fastdds::dds::DataReader* getReader() = 0;

    virtual ~IDataReader() = default;
};


template <typename T>
class DataReader : public IDataReader {

public:
    class Selector {

    public:
        Selector(): m_nativeReader(nullptr) {}
    
        Selector& state(const dds::sub::status::DataState& s) {
            return *this;
        }

        dds::sub::LoanedSamples<T> take() {
            dds::sub::LoanedSamples<T> loanedSamples;

            eprosima::fastdds::dds::LoanableSequence<T> samples;
            eprosima::fastdds::dds::SampleInfoSeq sample_infos;

            int32_t max_samples = eprosima::fastdds::dds::LENGTH_UNLIMITED;
            eprosima::fastdds::dds::SampleStateMask sample_states = eprosima::fastdds::dds::ANY_SAMPLE_STATE;
            eprosima::fastdds::dds::ViewStateMask view_states = eprosima::fastdds::dds::ANY_VIEW_STATE;
            eprosima::fastdds::dds::InstanceStateMask instance_states = eprosima::fastdds::dds::ANY_INSTANCE_STATE;

            if (m_nativeReader) {
                auto ret = m_nativeReader->take(samples, sample_infos, max_samples, sample_states, view_states, instance_states);
                if (ret == eprosima::fastdds::dds::RETCODE_OK) {
                    for (size_t i = 0; i < samples.length(); i++) {
                        loanedSamples.push_back(
                            fastdds_modern_cpp_api::dds::sub::LoanedSample<T>(
                                fastdds_modern_cpp_api::dds::sub::SampleInfo(sample_infos[i]),
                                samples[i]
                            )
                        );
                    }
                }
            }

            return loanedSamples;
        }

        void setReader(eprosima::fastdds::dds::DataReader* nativeReader) {
            m_nativeReader = nativeReader;
        }
    private:
        eprosima::fastdds::dds::DataReader* m_nativeReader;
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
        m_selector.setReader(nativeReader);
    }

    void close() {

    }

    Selector& select(dds::sub::status::DataState dataSate) {
        return m_selector;
    }

    

    eprosima::fastdds::dds::DataReader* getReader() {
        return nativeReader;
    }

private:
    Selector m_selector;
    eprosima::fastdds::dds::DataReader* nativeReader;

};


} // namespace sub
}
}
