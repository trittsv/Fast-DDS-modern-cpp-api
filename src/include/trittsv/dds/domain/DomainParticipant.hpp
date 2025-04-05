#pragma once

#include <trittsv/dds/core/InstanceHandle.hpp>

#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/domain/DomainParticipantFactory.hpp>


namespace trittsv {
namespace dds {
namespace domain {

namespace qos {



class DomainParticipantQos {

public:
    eprosima::fastdds::dds::DomainParticipantQos native_qos;

};

} // namespace qos

class DomainParticipant {

public:
    DomainParticipant(uint32_t id, trittsv::dds::domain::qos::DomainParticipantQos qos) {
        auto factory = eprosima::fastdds::dds::DomainParticipantFactory::get_instance();
        m_pariticpant = factory->create_participant(id, qos.native_qos);
        if (m_pariticpant == nullptr) {
            throw std::runtime_error("Participant initialization failed");
        }
    }

    ~DomainParticipant() {
        if (nullptr != m_pariticpant) {
            m_pariticpant->delete_contained_entities();
            eprosima::fastdds::dds::DomainParticipantFactory::get_instance()->delete_participant(m_pariticpant);
        }
    }

    const dds::core::InstanceHandle& instance_handle() const {
        return dds::core::InstanceHandle(m_pariticpant->get_instance_handle());
    }

    eprosima::fastdds::dds::DomainParticipant* m_pariticpant;
};


} // namepsace domain
}
}