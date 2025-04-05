#include "gen/HelloWorld.hpp"
#include "gen/HelloWorldPubSubTypes.hpp"

#include <fastdds_modern_cpp_api/dds/dds.hpp>

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
		eprosima::fastdds::dds::TypeSupport type_(new HelloWorldPubSubType()); // TODO: find a way to wrap this.
		type_.register_type(participant.m_pariticpant);

		std::cout << "Create topic..." << std::endl;
		dds::topic::Topic<HelloWorld> topic(participant, "HelloWorldTopic", qos, listener, mask);

		std::cout << "Create Subscriber..." << std::endl;
		dds::sub::qos::SubscriberQos sub_qos;
		dds::sub::Subscriber subscriber(participant, sub_qos);

		std::cout << "Create Reader..." << std::endl;
        dds::sub::qos::DataReaderQos reader_qos;
        dds::sub::DataReaderListener<HelloWorld>* reader_listener;
        dds::core::status::StatusMask reader_mask;

		dds::sub::DataReader<HelloWorld> reader(subscriber, topic, reader_qos, reader_listener, reader_mask);

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
