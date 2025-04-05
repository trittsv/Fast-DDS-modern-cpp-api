#pragma once

#include <fastdds/dds/xtypes/exception/Exception.hpp>
#include <fastdds/rtps/common/Time_t.hpp>


namespace trittsv {
namespace dds {
namespace core {


using Exception = eprosima::fastdds::dds::xtypes::Exception;
using InvalidArgumentError = eprosima::fastdds::dds::xtypes::InvalidArgumentError;



class TimeoutError : public eprosima::fastdds::dds::xtypes::Exception, std::runtime_error {

public:
    explicit TimeoutError(const std::string& msg): Exception() , std::runtime_error(msg) {

    }

    TimeoutError(const TimeoutError& src): Exception(), std::runtime_error(src.what()) {

    }

    virtual ~TimeoutError() throw() {

    }

    virtual const char* what() const throw() {
        return this->std::runtime_error::what();
    }
};


}
}
}