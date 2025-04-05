#pragma once



#include <fastdds/dds/core/Entity.hpp>
#include <fastdds/dds/core/ReturnCode.hpp>
#include <fastdds/dds/core/policy/QosPolicies.hpp>
#include <fastdds/dds/core/status/BaseStatus.hpp>
#include <fastdds/dds/core/status/SubscriptionMatchedStatus.hpp>
#include <fastdds/dds/core/status/PublicationMatchedStatus.hpp>

#include <fastdds/dds/core/status/StatusMask.hpp>

namespace trittsv {
namespace dds {
namespace core {
namespace status {


class InconsistentTopicStatus {
public:
    InconsistentTopicStatus(){}
    uint32_t total_count() const {
        return 1;
    }
    uint32_t total_count_change() const {
        return 1;
    }
};

class SubscriptionMatchedStatus {
public:
    SubscriptionMatchedStatus(){}
    uint32_t current_count() const {
        return m_status.current_count;
    }
private:
    eprosima::fastdds::dds::SubscriptionMatchedStatus m_status;
};

class RequestedIncompatibleQosStatus {

public:
    RequestedIncompatibleQosStatus(){}
    uint32_t total_count() const {
        return m_status.total_count;
    }
    uint32_t total_count_change() const {
        return m_status.total_count_change;
    }
    uint32_t last_policy_id() const {
        return m_status.last_policy_id;
    }
private:
    eprosima::fastdds::dds::IncompatibleQosStatus m_status;
};



class LivelinessChangedStatus {

public:
    LivelinessChangedStatus(){}

    uint32_t alive_count() const {
        return m_status.alive_count;
    }
    uint32_t not_alive_count() const {
        return m_status.not_alive_count;
    }
private:
    eprosima::fastdds::dds::LivelinessChangedStatus m_status;
};


class PublicationMatchedStatus {

public:
    PublicationMatchedStatus(){}

    uint32_t current_count() const {
        return m_status.current_count;
    }
private:
    eprosima::fastdds::dds::PublicationMatchedStatus m_status;
};

class OfferedIncompatibleQosStatus {

public:
    OfferedIncompatibleQosStatus(){}

    uint32_t last_policy_id() const {
        return m_status.last_policy_id;
    }
    uint32_t total_count() const {
        return m_status.total_count;
    }
    uint32_t total_count_change() const {
        return m_status.total_count_change;
    }
private:
    eprosima::fastdds::dds::OfferedIncompatibleQosStatus m_status;
};



using SampleLostStatus = eprosima::fastdds::dds::SampleLostStatus;
using LivelinessLostStatus = eprosima::fastdds::dds::LivelinessLostStatus;
using SampleRejectedStatus = eprosima::fastdds::dds::SampleRejectedStatus;
using RequestedDeadlineMissedStatus = eprosima::fastdds::dds::RequestedDeadlineMissedStatus;
using OfferedDeadlineMissedStatus = eprosima::fastdds::dds::OfferedDeadlineMissedStatus;


using StatusMask = eprosima::fastdds::dds::StatusMask;


}
}
}
}