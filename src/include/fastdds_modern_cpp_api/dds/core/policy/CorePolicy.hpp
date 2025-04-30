#pragma once

#include <fastdds_modern_cpp_api/dds/core/Duration.hpp>


#include <fastdds/dds/core/condition/Condition.hpp>

#include <fastdds/dds/core/Entity.hpp>
#include <fastdds/dds/core/ReturnCode.hpp>
#include <fastdds/dds/core/policy/QosPolicies.hpp>
#include <fastdds/dds/core/status/BaseStatus.hpp>
#include <fastdds/dds/core/status/SubscriptionMatchedStatus.hpp>

#include <fastdds/dds/core/policy/QosPolicies.hpp>

#include <fastdds/dds/core/status/StatusMask.hpp>

#include <fastdds/dds/publisher/qos/DataWriterQos.hpp>
#include <fastdds/dds/publisher/qos/PublisherQos.hpp>
#include <fastdds/dds/publisher/DataWriter.hpp>

#include <fastdds/dds/common/InstanceHandle.hpp>

#include <fastdds/dds/xtypes/exception/Exception.hpp>

#include <fastdds/rtps/common/Time_t.hpp>


namespace fastdds_modern_cpp_api {
namespace dds {
namespace core {
namespace policy {

enum class TypeConsistencyKind {
    DISALLOW_TYPE_COERCION = 0,
    ALLOW_TYPE_COERCION = 1
};

class TypeConsistencyEnforcement {

public:
    TypeConsistencyEnforcement(
        const TypeConsistencyKind& consistencyKind, bool ignore_sequence_bounds, bool ignore_string_bounds,
        bool ignore_member_names, bool prevent_type_widening, bool force_type_validation) {

        if (consistencyKind == TypeConsistencyKind::DISALLOW_TYPE_COERCION) {
            m_policy.m_kind = eprosima::fastdds::dds::TypeConsistencyKind::DISALLOW_TYPE_COERCION;
        } else if (consistencyKind == TypeConsistencyKind::ALLOW_TYPE_COERCION) {
            m_policy.m_kind = eprosima::fastdds::dds::TypeConsistencyKind::ALLOW_TYPE_COERCION;;
        }
        
        m_policy.m_ignore_sequence_bounds = ignore_sequence_bounds;
        m_policy.m_ignore_string_bounds = ignore_string_bounds;
        m_policy.m_ignore_member_names = ignore_member_names;
        m_policy.m_prevent_type_widening = prevent_type_widening;
        m_policy.m_force_type_validation = force_type_validation;
    }

    operator eprosima::fastdds::dds::TypeConsistencyEnforcementQosPolicy() const {
        return m_policy;
    }

private:
    eprosima::fastdds::dds::TypeConsistencyEnforcementQosPolicy m_policy;
};

class Partition {

public:
    Partition(const std::string& name) : m_name(name) {

    }

    std::string m_name;
};

enum class DataRepresentationId {
    XCDR1 = 0,
    XML = 1,
    XCDR2 = 2 
};

class DataRepresentation {

public:
    DataRepresentation(const DataRepresentationId& kind) {
        if (kind == DataRepresentationId::XCDR1) {
            m_policy.m_value.push_back(eprosima::fastdds::dds::DataRepresentationId_t::XCDR_DATA_REPRESENTATION);
        } else if(kind == DataRepresentationId::XML) {
            m_policy.m_value.push_back(eprosima::fastdds::dds::DataRepresentationId_t::XML_DATA_REPRESENTATION);
        } else if (kind == DataRepresentationId::XCDR2) {
            m_policy.m_value.push_back(eprosima::fastdds::dds::DataRepresentationId_t::XCDR2_DATA_REPRESENTATION);
        }
    }
    operator eprosima::fastdds::dds::DataRepresentationQosPolicy() const {
        return m_policy;
    }

private:
    eprosima::fastdds::dds::DataRepresentationQosPolicy m_policy;

};


enum class ReliabilityKind {
    BEST_EFFORT = 0,
    RELIABLE = 1
};

class Reliability {

public:
    Reliability(const fastdds_modern_cpp_api::dds::core::policy::ReliabilityKind& kind, const fastdds_modern_cpp_api::dds::core::Duration& max_blocking_time = dds::core::Duration(0, 100000000)) {

        if (kind == ReliabilityKind::BEST_EFFORT) {
            m_policy.kind = eprosima::fastdds::dds::ReliabilityQosPolicyKind::BEST_EFFORT_RELIABILITY_QOS;
        } else if (kind == ReliabilityKind::RELIABLE) {
            m_policy.kind = eprosima::fastdds::dds::ReliabilityQosPolicyKind::RELIABLE_RELIABILITY_QOS;
            m_policy.max_blocking_time = eprosima::fastdds::dds::Duration_t(max_blocking_time.sec, max_blocking_time.nsec);
        }

        
    }
    operator eprosima::fastdds::dds::ReliabilityQosPolicy() const {
        return m_policy;
    }
private:
    eprosima::fastdds::dds::ReliabilityQosPolicy m_policy;
};



enum class DurabilityKind {
    VOLATILE = 0,
    TRANSIENT_LOCAL = 1,
    TRANSIENT = 2,
    PERSISTENT = 3
};

class Durability {

public:
    Durability(const dds::core::policy::DurabilityKind& kind) {

        if (kind == DurabilityKind::VOLATILE) {
            m_policy.kind = eprosima::fastdds::dds::DurabilityQosPolicyKind::VOLATILE_DURABILITY_QOS;
        } else if (kind == DurabilityKind::TRANSIENT_LOCAL) {
            m_policy.kind = eprosima::fastdds::dds::DurabilityQosPolicyKind::TRANSIENT_LOCAL_DURABILITY_QOS;
        } else if (kind == DurabilityKind::TRANSIENT) {
            m_policy.kind = eprosima::fastdds::dds::DurabilityQosPolicyKind::TRANSIENT_DURABILITY_QOS;
        } else if (kind == DurabilityKind::PERSISTENT) {
            throw std::logic_error("Not implemented!");
        }
    }
    operator eprosima::fastdds::dds::DurabilityQosPolicy() const {
        return m_policy;
    }
private:
    eprosima::fastdds::dds::DurabilityQosPolicy m_policy;
};


enum class OwnershipKind {
    SHARED = 0,
    EXCLUSIVE = 1
};

class Ownership {

public:
    Ownership(const dds::core::policy::OwnershipKind& kind) {
        if (kind == OwnershipKind::SHARED) {
            m_policy.kind = eprosima::fastdds::dds::OwnershipQosPolicyKind::SHARED_OWNERSHIP_QOS;
        } else if (kind == OwnershipKind::EXCLUSIVE) {
            m_policy.kind = eprosima::fastdds::dds::OwnershipQosPolicyKind::EXCLUSIVE_OWNERSHIP_QOS;
        }
    }
    operator eprosima::fastdds::dds::OwnershipQosPolicy() const {
        return m_policy;
    }
private:
    eprosima::fastdds::dds::OwnershipQosPolicy m_policy;
};

enum class HistoryKind {
    KEEP_LAST = 0,
    KEEP_ALL = 1
};

class History {

public:
    History() {

    }
    
    History(const dds::core::policy::HistoryKind& kind, int32_t depth = 1) {
        if (kind == HistoryKind::KEEP_LAST) {
            m_policy.kind = eprosima::fastdds::dds::HistoryQosPolicyKind::KEEP_LAST_HISTORY_QOS;
            m_policy.depth = depth;
        } else if (kind == HistoryKind::KEEP_ALL) {
            m_policy.kind = eprosima::fastdds::dds::HistoryQosPolicyKind::KEEP_ALL_HISTORY_QOS;
        }
    }

    History& depth(int32_t depth) {
        m_policy.depth = depth;
        return *this;
    }

    static History KeepAll() {
        return History(HistoryKind::KEEP_ALL);
    }

    static History KeepLast(int32_t depth) {
        return History(HistoryKind::KEEP_LAST, depth);
    }

    operator eprosima::fastdds::dds::HistoryQosPolicy() const {
        return m_policy;
    }

private:
    eprosima::fastdds::dds::HistoryQosPolicy m_policy;
};
    



} // policy
}
}
}
