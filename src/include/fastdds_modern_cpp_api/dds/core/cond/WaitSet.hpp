#pragma once

#include <fastdds_modern_cpp_api/dds/core/Duration.hpp>
#include <fastdds_modern_cpp_api/dds/sub/cond/ReadCondition.hpp>

#include "Condition.hpp"

#include <fastdds/dds/core/condition/WaitSet.hpp>


namespace fastdds_modern_cpp_api {
namespace dds {
namespace core {
namespace cond {

class WaitSet {

public:
    WaitSet& operator+=(fastdds_modern_cpp_api::dds::sub::cond::ReadCondition& rhs) {
        m_waitset.attach_condition(*rhs.m_readCondition);
        return *this;
    }

    WaitSet& operator-=(fastdds_modern_cpp_api::dds::sub::cond::ReadCondition& rhs) {
        m_waitset.detach_condition(*rhs.m_readCondition);
        return *this;
    }

    void dispatch(const fastdds_modern_cpp_api::dds::core::Duration& timeout) {
        eprosima::fastdds::dds::ConditionSeq triggered;
        auto ret =  m_waitset.wait(triggered, timeout);

        

        if (ret == 0) {
            std::cout << "good ret code!" << std::endl;
            /*for (eprosima::fastdds::dds::Condition* cond : triggered) {
                if (handlers.count(cond)) {
                    handlers[cond]();
                }
            }  */
        }

        if (ret != 0 && ret != 10) {
            // timeout = 10
            throw std::logic_error("Waitset failed with code: " + std::to_string(ret));
        }
    }

private:
    eprosima::fastdds::dds::WaitSet m_waitset;

};

}
}
}
}
