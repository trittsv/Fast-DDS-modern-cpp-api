#include "gen/HelloWorld.hpp"
#include "gen/HelloWorldPubSubTypes.hpp"
#include "Utils.hpp"

#include <fastdds_modern_cpp_api/dds/dds.hpp>

#include <iostream>
#include <chrono>
#include <thread>
#include <iomanip>
#include <sstream>

#include <windows.h>

std::atomic<bool> g_running = true;

CTRL_HANDLER_MACRO();

int main(int argc, char** argv) {

    namespace dds = fastdds_modern_cpp_api::dds;

    SetConsoleCtrlHandler(CtrlHandler, TRUE);

    try {
        LOG << "Hello World";

        // Create Participant
        dds::domain::qos::DomainParticipantQos participant_qos;
        dds::domain::DomainParticipant participant(0, participant_qos);

        // Create topic
        dds::topic::qos::TopicQos qos;
        dds::topic::TopicListener<HelloWorld>* listener;
        dds::core::status::StatusMask mask;

        // TODO: find a way to wrap this.
        REGISTER_PUBSUB_TYPE(HelloWorld, participant.get_participant()); 

        LOG << "Create topic...";;
        dds::topic::Topic<HelloWorld> topic(participant, "HelloWorldTopic", qos, listener, mask);

        LOG << "Create Publisher...";;
        dds::pub::qos::PublisherQos pub_qos;
        pub_qos << dds::core::policy::Partition("MyPartition");

        dds::pub::Publisher publisher(participant, pub_qos);

        LOG << "Create Writer...";;
        dds::pub::qos::DataWriterQos writer_qos;
        writer_qos << dds::core::policy::DatRepresentation(dds::core::policy::DataRepresentationId::XCDR2);
        writer_qos << dds::core::policy::Ownership(dds::core::policy::OwnershipKind::SHARED);
        writer_qos << dds::core::policy::Reliability(dds::core::policy::ReliabilityKind::RELIABLE, dds::core::Duration::infinite());
        writer_qos << dds::core::policy::Durability(dds::core::policy::DurabilityKind::TRANSIENT_LOCAL);
        writer_qos << dds::core::policy::History::KeepAll();

        dds::pub::DataWriterListener<HelloWorld>* writer_listener;
        dds::core::status::StatusMask writer_mask;

        dds::pub::DataWriter<HelloWorld> writer(publisher, topic, writer_qos, writer_listener, writer_mask);

        LOG << "Write msg...";;
        HelloWorld msg;
        msg.index() = 1;
        msg.message() = "Hello im here!";

        while(g_running) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));

            try {
                writer.write(msg);
            } catch (const std::exception& e) {
                LOG << e.what();
            }

            msg.index() = msg.index() + 1;
        }

    } catch (const std::exception& e) {
        LOG << "Exception: " << e.what();
        return 1;
    }

    LOG << "Exit...";;
    return 0;
}
