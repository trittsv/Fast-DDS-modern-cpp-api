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

    static InstanceState alive() {
        return InstanceState();
    }

    bool operator==(const InstanceState& other) const {
        return true;
    }


    bool operator!=(const InstanceState& other) const {
        return !(*this == other);
    }

};
    

class DataState {
public:
    DataState(){}

    inline static const DataState any(){
        return DataState();
    }

    InstanceState& instance_state() {
        return m_instanceState;
    }
private:
    InstanceState m_instanceState;
};



}
}
}

}
