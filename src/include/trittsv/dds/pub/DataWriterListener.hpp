#pragma once

#include <trittsv/dds/core/status/Status.hpp>
#include <trittsv/dds/pub/DataWriter.hpp>

#include <fastdds/dds/core/Entity.hpp>
#include <fastdds/dds/core/ReturnCode.hpp>
#include <fastdds/dds/core/policy/QosPolicies.hpp>
#include <fastdds/dds/core/status/BaseStatus.hpp>
#include <fastdds/dds/core/status/SubscriptionMatchedStatus.hpp>
#include <fastdds/dds/core/status/PublicationMatchedStatus.hpp>

#include <fastdds/dds/core/status/StatusMask.hpp>

namespace trittsv {
namespace dds {
namespace pub {

template <typename T>
class DataWriter;

template <typename T>
class DataWriterListener {

public:
    virtual void on_liveliness_lost(
        dds::pub::DataWriter<T>& writer, eprosima::fastdds::dds::LivelinessLostStatus const& status) {

    }

    virtual void on_offered_deadline_missed(
        dds::pub::DataWriter<T>& writer, eprosima::fastdds::dds::OfferedDeadlineMissedStatus const& status) {

    }

    virtual void on_offered_incompatible_qos(
        dds::pub::DataWriter<T>& writer, dds::core::status::OfferedIncompatibleQosStatus const& status) {

    }

    virtual void on_publication_matched(
        dds::pub::DataWriter<T>& writer, dds::core::status::PublicationMatchedStatus const& status) {
    }
};


}
}
}