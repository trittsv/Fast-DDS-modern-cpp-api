#pragma once

#include <fastdds_modern_cpp_api/dds/core/Duration.hpp>
#include <fastdds_modern_cpp_api/dds/core/Exception.hpp>
#include <fastdds_modern_cpp_api/dds/sub/cond/ReadCondition.hpp>

#include "Condition.hpp"

#include <fastdds/dds/core/condition/WaitSet.hpp>

#include <unordered_map>

namespace fastdds_modern_cpp_api {
namespace dds {
namespace core {
namespace cond {

class WaitSet {

public:
    WaitSet& operator+=(const fastdds_modern_cpp_api::dds::sub::cond::ReadCondition& rhs) {
        m_waitset.attach_condition(*rhs.m_readCondition);
        m_handlers[rhs.m_readCondition] = &rhs;
        return *this;
    }

    WaitSet& operator-=(const fastdds_modern_cpp_api::dds::sub::cond::ReadCondition& rhs) {
        m_waitset.detach_condition(*rhs.m_readCondition);
        m_handlers.erase(rhs.m_readCondition);
        return *this;
    }

    WaitSet& operator+=(fastdds_modern_cpp_api::dds::core::cond::GuardCondition& rhs) {
        m_waitset.attach_condition(rhs.m_guardCondition);
        return *this;
    }

    WaitSet& operator-=(fastdds_modern_cpp_api::dds::core::cond::GuardCondition& rhs) {
        m_waitset.detach_condition(rhs.m_guardCondition);
        return *this;
    }

    void dispatch(const fastdds_modern_cpp_api::dds::core::Duration& timeout) {

        eprosima::fastdds::dds::ConditionSeq triggered;

        auto ret =  m_waitset.wait(triggered, timeout);

        if (ret == eprosima::fastdds::dds::RETCODE_OK) {
            for (eprosima::fastdds::dds::Condition* cond : triggered) {
                auto it = m_handlers.find(cond);
                if (it != m_handlers.end() && it->second->m_callback) {
                    it->second->m_callback();
                }
            }
        } else if (ret == eprosima::fastdds::dds::RETCODE_TIMEOUT) {
            throw fastdds_modern_cpp_api::dds::core::TimeoutError("Timout Error");
        } else {
            throw std::logic_error("Waitset failed with code: " + std::to_string(ret));
        }
    
        /*const ReturnCode_t RETCODE_OK = 0;
        const ReturnCode_t RETCODE_ERROR = 1;
        const ReturnCode_t RETCODE_UNSUPPORTED = 2;
        const ReturnCode_t RETCODE_BAD_PARAMETER = 3;
        const ReturnCode_t RETCODE_PRECONDITION_NOT_MET = 4;
        const ReturnCode_t RETCODE_OUT_OF_RESOURCES = 5;
        const ReturnCode_t RETCODE_NOT_ENABLED = 6;
        const ReturnCode_t RETCODE_IMMUTABLE_POLICY = 7;
        const ReturnCode_t RETCODE_INCONSISTENT_POLICY = 8;
        const ReturnCode_t RETCODE_ALREADY_DELETED = 9;
        const ReturnCode_t RETCODE_TIMEOUT = 10;
        const ReturnCode_t RETCODE_NO_DATA = 11;
        const ReturnCode_t RETCODE_ILLEGAL_OPERATION = 12;*/
    
    }

private:
    eprosima::fastdds::dds::WaitSet m_waitset;
    std::unordered_map<eprosima::fastdds::dds::Condition*, const fastdds_modern_cpp_api::dds::sub::cond::ReadCondition*> m_handlers;
};

}
}
}
}
