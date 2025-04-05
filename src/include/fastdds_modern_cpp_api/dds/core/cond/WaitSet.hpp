#pragma once

#include <fastdds_modern_cpp_api/dds/sub/cond/ReadCondition.hpp>
#include "Condition.hpp"

#include <fastdds/dds/core/condition/WaitSet.hpp>


namespace fastdds_modern_cpp_api {
namespace dds {
namespace core {
namespace cond {

class WaitSet {

public:
    WaitSet& operator+=(const dds::sub::cond::ReadCondition& rhs) {
        //m_waitset.attach_condition(rhs.m_readCondition);
        return *this;
    }

    WaitSet& operator-=(const dds::sub::cond::ReadCondition& rhs) {
        //m_waitset.detach_condition(rhs.m_readCondition);
        return *this;
    }

    void dispatch(const eprosima::fastdds::dds::Duration_t& timeout) {
        eprosima::fastdds::dds::ConditionSeq triggered_conditions;
        m_waitset.wait(triggered_conditions, timeout);
    }

private:
    eprosima::fastdds::dds::WaitSet m_waitset;
};

}
}
}
}
