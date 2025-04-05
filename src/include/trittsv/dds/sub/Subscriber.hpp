#pragma once

#include <trittsv/dds/domain/DomainParticipant.hpp>
#include <trittsv/dds/sub/qos/SubscriberQos.hpp>
#include <trittsv/dds/sub/SubscriberListener.hpp>
#include <trittsv/dds/core/status/Status.hpp>

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


namespace trittsv {
namespace dds {
namespace sub {

class Subscriber {

public:
    Subscriber(){}
    Subscriber(const dds::domain::DomainParticipant& dp, const dds::sub::qos::SubscriberQos& qos) {

        m_subscriber = dp.m_pariticpant->create_subscriber(qos);
        if (m_subscriber == nullptr) {
            throw std::runtime_error("Subscriber initialization failed");
        }

    }


    eprosima::fastdds::dds::Subscriber* m_subscriber;
};


}
}
}
