#include <fastdds_modern_cpp_api/dds/dds.hpp>
#include "gen/HelloWorld.hpp"
#include "gen/HelloWorldPubSubTypes.hpp"

#include <iostream>
#include <chrono>
#include <thread>
#include <windows.h>

std::atomic<bool> g_running = true;

BOOL CtrlHandler(DWORD fdwCtrlType) {
	switch (fdwCtrlType) {
		case CTRL_C_EVENT:
			std::cout << "Ctrl + C pressed. Handling signal..." << std::endl;
			g_running = false;
			return TRUE;
		case CTRL_BREAK_EVENT:
			std::cout << "Ctrl + Break pressed. Handling signal..." << std::endl;
			g_running = false;
			return TRUE;
		default:
			return FALSE;
	}
}

int main(int argc, char** argv) {

	namespace dds = fastdds_modern_cpp_api::dds;

	SetConsoleCtrlHandler(CtrlHandler, TRUE);

	try {
		std::cout << "Hello World" << std::endl;

		// Create Participant
		dds::domain::qos::DomainParticipantQos participant_qos;
		dds::domain::DomainParticipant participant(0, participant_qos);

		// Create topic
		dds::topic::qos::TopicQos qos;
		dds::topic::TopicListener<HelloWorld>* listener;
		dds::core::status::StatusMask mask;

		std::cout << "Register type" << std::endl;
		// TODO: find a way to wrap this.
		eprosima::fastdds::dds::TypeSupport type_(new HelloWorldPubSubType()); 
		type_.register_type(participant.m_pariticpant);

		std::cout << "Create topic..." << std::endl;
		dds::topic::Topic<HelloWorld> topic(participant, "HelloWorldTopic", qos, listener, mask);

		std::cout << "Create Publisher..." << std::endl;
		dds::pub::qos::PublisherQos pub_qos;
		pub_qos << dds::core::policy::Partition("MyPartition");

		dds::pub::Publisher publisher(participant, pub_qos);

		std::cout << "Create Writer..." << std::endl;
        dds::pub::qos::DataWriterQos writer_qos;
		writer_qos << dds::core::policy::DatRepresentation(dds::core::policy::DataRepresentationId::XCDR2);
		writer_qos << dds::core::policy::Ownership(dds::core::policy::OwnershipKind::SHARED);
		writer_qos << dds::core::policy::Reliability(dds::core::policy::ReliabilityKind::RELIABLE, dds::core::Duration::infinite());
		writer_qos << dds::core::policy::Durability(dds::core::policy::DurabilityKind::TRANSIENT_LOCAL);
		writer_qos << dds::core::policy::History::KeepAll();

        dds::pub::DataWriterListener<HelloWorld>* writer_listener;
        dds::core::status::StatusMask writer_mask;

		dds::pub::DataWriter<HelloWorld> writer(publisher, topic, writer_qos, writer_listener, writer_mask);

		std::cout << "Write msg..." << std::endl;
		HelloWorld msg;
		writer.write(msg);

		while(g_running) {
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}

    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
        return 1;
    }

	std::cout << "Exit..." << std::endl;
	return 0;
}
