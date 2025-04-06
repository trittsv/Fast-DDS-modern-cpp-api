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

#define DECLARE_PUBSUB_TYPE(T, TPubSubType) \
    template <> struct PubSubTypeFor<T> { using Type = TPubSubType; }


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

        LOG << "Create topic...";
        dds::topic::Topic<HelloWorld> topic(participant, "HelloWorldTopic", qos, listener, mask);

        LOG << "Create Subscriber...";
        dds::sub::qos::SubscriberQos sub_qos;
        sub_qos << dds::core::policy::Partition("MyPartition");
        dds::sub::Subscriber subscriber(participant, sub_qos);

        LOG << "Create Reader...";
        dds::sub::qos::DataReaderQos reader_qos;
        reader_qos << dds::core::policy::DatRepresentation(dds::core::policy::DataRepresentationId::XCDR2);
        reader_qos << dds::core::policy::Ownership(dds::core::policy::OwnershipKind::SHARED);
        reader_qos << dds::core::policy::Reliability(dds::core::policy::ReliabilityKind::RELIABLE, dds::core::Duration::infinite());
        reader_qos << dds::core::policy::Durability(dds::core::policy::DurabilityKind::TRANSIENT_LOCAL);
        reader_qos << dds::core::policy::History::KeepAll();
        dds::sub::DataReaderListener<HelloWorld>* reader_listener;
        dds::core::status::StatusMask reader_mask;
        auto dataState = dds::sub::status::DataState::any();

        dds::sub::DataReader<HelloWorld> reader(subscriber, topic, reader_qos, reader_listener, reader_mask);

        // The callback where we want to get notified on new data
        std::function<void()> callback = [&reader, &dataState]() {
            LOG << "Received samples ...";

            dds::sub::LoanedSamples<HelloWorld> samples = reader.select(dataState).take();
            for (auto sample : samples) {
                dds::sub::SampleInfo sampleInfo = sample.info();
                dds::sub::status::DataState dataStateSample = sampleInfo.state();
                dds::sub::status::InstanceState instanceStateSample = dataStateSample.instance_state();

                if (sampleInfo.valid() && instanceStateSample == dds::sub::status::InstanceState::alive()) {
                    const HelloWorld& t = sample.data();

                    LOG << "[Received] (HelloWorld) index: " << std::to_string(t.index()) << ", message: " << t.message();
                } else {
                    LOG << "[Received] (HelloWorld) INVALID";
                }
            }
        };

        // setup waitset
        dds::sub::cond::ReadCondition readCondition(reader, dataState, callback);
        dds::core::cond::WaitSet waitset;
        waitset += readCondition;

        while(g_running) {
            try {
                waitset.dispatch(dds::core::Duration(1, 0)); // better -> dds::core::Duration::infinite()
            } catch(const dds::core::TimeoutError& e) {
                // ok expected - no new message arrived
            }
        }

    } catch (const std::exception& e) {
        LOG << "Exception: " << e.what();
        return 1;
    }

    LOG << "Exit...";
    return 0;
}
