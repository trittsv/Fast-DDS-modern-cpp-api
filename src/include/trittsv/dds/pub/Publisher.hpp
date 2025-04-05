#pragma once


#include <trittsv/dds/domain/DomainParticipant.hpp>
#include <trittsv/dds/pub/qos/PublisherQos.hpp>

#include <fastdds/dds/publisher/qos/DataWriterQos.hpp>
#include <fastdds/dds/publisher/qos/PublisherQos.hpp>
#include <fastdds/dds/publisher/DataWriter.hpp>
#include <fastdds/dds/publisher/Publisher.hpp>


namespace trittsv {
namespace dds {
namespace pub {

class Publisher {

public:
    Publisher(){}
    Publisher(const dds::domain::DomainParticipant& dp, const dds::pub::qos::PublisherQos& qos) {

        dp.m_pariticpant->get_default_publisher_qos(pub_qos);
        m_publisher = dp.m_pariticpant->create_publisher(qos.m_qos);
        if (m_publisher == nullptr) {
            throw std::runtime_error("Publisher initialization failed");
        }
    }

    eprosima::fastdds::dds::Publisher* m_publisher;

    eprosima::fastdds::dds::PublisherQos pub_qos;
    

};

}
}
}