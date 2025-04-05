#pragma once

#include <fastdds/dds/core/condition/Condition.hpp>

#include <fastdds/dds/core/Entity.hpp>
#include <fastdds/dds/core/ReturnCode.hpp>
#include <fastdds/dds/core/policy/QosPolicies.hpp>
#include <fastdds/dds/core/status/BaseStatus.hpp>
#include <fastdds/dds/core/status/SubscriptionMatchedStatus.hpp>

#include <fastdds/dds/core/status/StatusMask.hpp>

#include <fastdds/dds/publisher/qos/DataWriterQos.hpp>
#include <fastdds/dds/publisher/qos/PublisherQos.hpp>
#include <fastdds/dds/publisher/DataWriter.hpp>

#include <fastdds/dds/common/InstanceHandle.hpp>

#include <fastdds/dds/xtypes/exception/Exception.hpp>

#include <fastdds/rtps/common/Time_t.hpp>

namespace fastdds_modern_cpp_api {
namespace dds {
namespace pub {
namespace qos {


class PublisherQos {

public:
    PublisherQos& operator<<(const fastdds_modern_cpp_api::dds::core::policy::Partition& rhs) {
        m_qos.partition().push_back(rhs.m_name.c_str());
        return *this;
    }

    eprosima::fastdds::dds::PublisherQos m_qos;
};


} // namespace qos
} // namespace pub
} // namespace dds
}