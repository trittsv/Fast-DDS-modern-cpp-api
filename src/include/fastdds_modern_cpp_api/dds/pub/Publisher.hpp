#pragma once


#include <fastdds_modern_cpp_api/dds/domain/DomainParticipant.hpp>
#include <fastdds_modern_cpp_api/dds/pub/qos/PublisherQos.hpp>
#include <fastdds_modern_cpp_api/dds/pub/qos/DataWriterQos.hpp>

#include <fastdds/dds/publisher/qos/DataWriterQos.hpp>
#include <fastdds/dds/publisher/qos/PublisherQos.hpp>
#include <fastdds/dds/publisher/DataWriter.hpp>
#include <fastdds/dds/publisher/Publisher.hpp>


namespace fastdds_modern_cpp_api {
namespace dds {
namespace pub {

class Publisher {

public:
    Publisher(){}

    Publisher(const dds::domain::DomainParticipant& dp, const dds::pub::qos::PublisherQos& qos) {

        m_publisher = dp.get_participant()->create_publisher(qos);
        if (m_publisher == nullptr) {
            throw std::runtime_error("Publisher initialization failed");
        }
    }

    fastdds_modern_cpp_api::dds::pub::qos::DataWriterQos default_datawriter_qos() {
        eprosima::fastdds::dds::DataWriterQos qos = eprosima::fastdds::dds::DATAWRITER_QOS_DEFAULT;
        auto ret = m_publisher->get_default_datawriter_qos(qos);
        if (ret != 0) {
            throw std::runtime_error("Failed to get_default_datawriter_qos " + std::to_string(ret));
        }
        return fastdds_modern_cpp_api::dds::pub::qos::DataWriterQos(qos);
    }

    eprosima::fastdds::dds::Publisher* m_publisher;
};

}
}
}
