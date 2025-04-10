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

    eprosima::fastdds::dds::DomainParticipant* get_participant() const {
        return m_pariticpant;
    }

    template <typename T>
    void register_type() {
        m_typeSupports.push_back(eprosima::fastdds::dds::TypeSupport(new T()));
        m_typeSupports.back().register_type(m_pariticpant);
    }

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

    eprosima::fastdds::dds::DomainParticipant* m_pariticpant;
    fastdds_modern_cpp_api::dds::domain::qos::DomainParticipantQos m_qos;

    std::vector<eprosima::fastdds::dds::TypeSupport> m_typeSupports;
};


} // namepsace domain
}
}
