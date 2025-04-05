#pragma once

#include <fastdds_modern_cpp_api/dds/core/InstanceHandle.hpp>

#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/domain/DomainParticipantFactory.hpp>


namespace fastdds_modern_cpp_api {
namespace dds {
namespace domain {
namespace qos {

class DomainParticipantQos {

public:
    operator eprosima::fastdds::dds::DomainParticipantQos() const {
        return m_qos;
    }

private:
    eprosima::fastdds::dds::DomainParticipantQos m_qos;
};

} // namespace qos

class DomainParticipant {

public:
    DomainParticipant(uint32_t id) {
        init(id);
    }

    DomainParticipant(uint32_t id, fastdds_modern_cpp_api::dds::domain::qos::DomainParticipantQos qos) {
        init(id, qos);
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

private:
    void init(uint32_t id, fastdds_modern_cpp_api::dds::domain::qos::DomainParticipantQos& qos) {
        auto factory = eprosima::fastdds::dds::DomainParticipantFactory::get_instance();
        m_pariticpant = factory->create_participant(id, qos);
        if (m_pariticpant == nullptr) {
            throw std::runtime_error("Participant initialization failed");
        }
    }

    void init(uint32_t id) {
        init(id, m_qos);
    }

    fastdds_modern_cpp_api::dds::domain::qos::DomainParticipantQos m_qos;
};


} // namepsace domain
}
}
