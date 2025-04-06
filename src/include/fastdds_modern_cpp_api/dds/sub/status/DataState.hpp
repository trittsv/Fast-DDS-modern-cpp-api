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
namespace status {

class InstanceState {

public:
    InstanceState(){}
    InstanceState(eprosima::fastdds::dds::InstanceStateMask instance_states) : m_instance_states(instance_states){}

    static InstanceState alive() {
        return InstanceState(eprosima::fastdds::dds::InstanceStateKind::ALIVE_INSTANCE_STATE);
    }

    bool operator==(const InstanceState& other) const {
        return m_instance_states == other.m_instance_states;
    }

    bool operator!=(const InstanceState& other) const {
        return !(*this == other);
    }

    operator eprosima::fastdds::dds::InstanceStateMask() const {
        return m_instance_states;
    }

private:
    eprosima::fastdds::dds::InstanceStateMask m_instance_states;

};

class ViewState {

public:
    ViewState(){}
    ViewState(eprosima::fastdds::dds::ViewStateMask view_states) : m_view_states(view_states) {}

    operator eprosima::fastdds::dds::ViewStateMask() const {
        return m_view_states;
    }

private:
    eprosima::fastdds::dds::ViewStateMask m_view_states;
};

class SampleState {

public:
    SampleState(){}
    SampleState(eprosima::fastdds::dds::SampleStateMask sample_states) : m_sampleStates(sample_states) {}

    operator eprosima::fastdds::dds::SampleStateMask() const {
        return m_sampleStates;
    }

private:
    eprosima::fastdds::dds::SampleStateMask m_sampleStates;
};

class DataState {

public:
    DataState(){}
    DataState(
        eprosima::fastdds::dds::InstanceStateMask instance_states,
        eprosima::fastdds::dds::ViewStateMask view_states,
        eprosima::fastdds::dds::SampleStateMask sample_states)
        : m_instanceState(instance_states)
        , m_viewState(view_states)
        , m_sampleState(sample_states) {

    }

    inline static const DataState any() {
        return DataState(eprosima::fastdds::dds::ANY_INSTANCE_STATE, eprosima::fastdds::dds::ANY_VIEW_STATE, eprosima::fastdds::dds::ANY_SAMPLE_STATE);
    }

    InstanceState& instance_state() {
        return m_instanceState;
    }

    SampleState& sample_state() {
        return m_sampleState;
    }

    ViewState& view_state() {
        return m_viewState;
    }

private:
    InstanceState m_instanceState;
    ViewState m_viewState;
    SampleState m_sampleState;

};


}
}
}
}
