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
class MyListener : public eprosima::fastdds::dds::DataReaderListener {

public:
    MyListener() = default;
    ~MyListener() = default;

    void on_data_available(eprosima::fastdds::dds::DataReader* reader) override {
        // std::cout << "on_data_available" << std::endl;
        // use waitset instead
    }

    void on_requested_incompatible_qos(
        eprosima::fastdds::dds::DataReader* reader,
        const eprosima::fastdds::dds::RequestedIncompatibleQosStatus& status) override {
        std::cout << "QoS mismatch detected: " << status.total_count << " instances with incompatible QoS" << std::endl;
    }

    void on_liveliness_changed(
        eprosima::fastdds::dds::DataReader* reader,
        const eprosima::fastdds::dds::LivelinessChangedStatus& status) override
    {
        std::cout << "Liveliness changed. Alive: " << status.alive_count << ", Not alive: " << status.not_alive_count << std::endl;
    }

    void on_sample_lost(
        eprosima::fastdds::dds::DataReader* reader,
        const eprosima::fastdds::dds::SampleLostStatus& status) override {
        std::cout << "Sample lost. Total lost: " << status.total_count << std::endl;
    }
};


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


template <typename T>
class LoanedSamples {
public:
    using iterator = typename std::vector<LoanedSample<T>>::iterator;
    using const_iterator = typename std::vector<LoanedSample<T>>::const_iterator;

    LoanedSamples(){}
    LoanedSamples(eprosima::fastdds::dds::DataReader* reader,
                  eprosima::fastdds::dds::LoanableSequence<T> samples,
                  eprosima::fastdds::dds::SampleInfoSeq sample_infos)
        : m_reader(reader), m_samples(samples), m_sample_infos(sample_infos) {

        for (size_t i = 0; i < m_samples.length(); i++) {
            m_data.push_back(
                fastdds_modern_cpp_api::dds::sub::LoanedSample<T>(
                    fastdds_modern_cpp_api::dds::sub::SampleInfo(m_sample_infos[i]),
                    m_samples[i]
                )
            );
        }
    }

    ~LoanedSamples() {
        if (m_reader) {
            auto ret = m_reader->return_loan(m_samples, m_sample_infos);
            if (ret != eprosima::fastdds::dds::RETCODE_OK) {
                // TODO: warning
            }
        }
    }

    // Vector-like API
    void push_back(const LoanedSample<T>& value) { m_data.push_back(value); }
    void push_back(LoanedSample<T>&& value) { m_data.push_back(std::move(value)); }

    LoanedSample<T>& operator[](size_t index) { return m_data[index]; }
    const LoanedSample<T>& operator[](size_t index) const { return m_data[index]; }

    size_t size() const { return m_data.size(); }
    bool empty() const { return m_data.empty(); }

    iterator begin() { return m_data.begin(); }
    iterator end() { return m_data.end(); }

    const_iterator begin() const { return m_data.begin(); }
    const_iterator end() const { return m_data.end(); }

    void clear() { m_data.clear(); }
    std::vector<LoanedSample<T>>& data() { return m_data; }
    const std::vector<LoanedSample<T>>& data() const { return m_data; }

private:
    std::vector<LoanedSample<T>> m_data;

    eprosima::fastdds::dds::DataReader* m_reader;
    eprosima::fastdds::dds::LoanableSequence<T> m_samples;
    eprosima::fastdds::dds::SampleInfoSeq m_sample_infos;
};



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
        Selector(eprosima::fastdds::dds::DataReader* nativeReader): m_nativeReader(nativeReader) {}
    
        Selector& state(const dds::sub::status::DataState& dataState) {
            m_dataState = dataState;
            return *this;
        }

        dds::sub::LoanedSamples<T> take() {

            eprosima::fastdds::dds::LoanableSequence<T> samples;
            eprosima::fastdds::dds::SampleInfoSeq sample_infos;

            if (m_nativeReader) {
                auto ret = m_nativeReader->take(
                    samples,
                    sample_infos,
                    eprosima::fastdds::dds::LENGTH_UNLIMITED,
                    m_dataState.sample_state(),
                    m_dataState.view_state(),
                    m_dataState.instance_state());
                if (ret == eprosima::fastdds::dds::RETCODE_OK) {
                    return dds::sub::LoanedSamples<T>(m_nativeReader, samples, sample_infos);
                }
            }

            return dds::sub::LoanedSamples<T>();
        }

        void setReader(eprosima::fastdds::dds::DataReader* nativeReader) {
            m_nativeReader = nativeReader;
        }
    private:
        eprosima::fastdds::dds::DataReader* m_nativeReader;
        dds::sub::status::DataState m_dataState;
    };

    DataReader(
        const dds::sub::Subscriber& sub,
        const dds::topic::Topic<T>& topic,
        const dds::sub::qos::DataReaderQos& qos,
        dds::sub::DataReaderListener<T>* listener,
        const dds::core::status::StatusMask& mask) {

        m_listener = std::make_shared<MyListener<T>>();

        nativeReader = sub.m_subscriber->create_datareader(topic.get_topic(), qos, m_listener.get());
        if (nativeReader == nullptr) {
            throw std::runtime_error("DataReader initialization failed");
        }
    }

    void close() {

    }

    Selector select() {
        return Selector(nativeReader);
    }

    eprosima::fastdds::dds::DataReader* getReader() {
        return nativeReader;
    }

private:
    eprosima::fastdds::dds::DataReader* nativeReader;

    std::shared_ptr<MyListener<T>> m_listener;
};


} // namespace sub
}
}
