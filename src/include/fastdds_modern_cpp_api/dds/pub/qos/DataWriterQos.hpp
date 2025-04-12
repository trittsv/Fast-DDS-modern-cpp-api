#pragma once

#include <fastdds_modern_cpp_api/dds/core/policy/CorePolicy.hpp>

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

class DataWriterQos {

public:
    DataWriterQos() {
            
    }

    DataWriterQos(eprosima::fastdds::dds::DataWriterQos qos) : m_qos(qos) {
        
    }

    DataWriterQos& operator<<(const fastdds_modern_cpp_api::dds::core::policy::Ownership& rhs) {
        m_qos.ownership(rhs);
        return *this;
    }
    DataWriterQos& operator<<(const fastdds_modern_cpp_api::dds::core::policy::Durability& rhs) {
        m_qos.durability(rhs);
        return *this;
    }
    DataWriterQos& operator<<(const fastdds_modern_cpp_api::dds::core::policy::Reliability& rhs) {
        m_qos.reliability(rhs);
        return *this;
    }
    DataWriterQos& operator<<(const fastdds_modern_cpp_api::dds::core::policy::History& rhs) {
        m_qos.history(rhs);
        return *this;
    }

    DataWriterQos& operator<<(const fastdds_modern_cpp_api::dds::core::policy::DatRepresentation& rhs) {
        m_qos.representation() = rhs;
        return *this;
    }

    operator eprosima::fastdds::dds::DataWriterQos() const {
        return m_qos;
    }

private:
    eprosima::fastdds::dds::DataWriterQos m_qos;

};

} // namespace qos
} // namespace pub
}
}
