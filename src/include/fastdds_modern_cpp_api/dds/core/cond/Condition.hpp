#pragma once

#include <fastdds/dds/core/condition/Condition.hpp>
#include <fastdds/dds/core/condition/GuardCondition.hpp>

namespace fastdds_modern_cpp_api {
namespace dds {
namespace core {
namespace cond {


//using Condition = eprosima::fastdds::dds::Condition;
class GuardCondition {
public:
    GuardCondition() {

    }

    void trigger_value(bool value) {
        m_guardCondition.set_trigger_value(value);
    }


    eprosima::fastdds::dds::GuardCondition m_guardCondition;

};

}
}
}
}
