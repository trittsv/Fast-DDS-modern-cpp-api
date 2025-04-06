#include "gen/HelloWorld.hpp"
#include "gen/HelloWorldPubSubTypes.hpp"

#include <fastdds_modern_cpp_api/dds/dds.hpp>

#include <iostream>
#include <chrono>
#include <thread>
#include <iomanip>
#include <sstream>

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

inline std::string current_timestamp() {
    using namespace std::chrono;

    auto now = system_clock::now();
    auto itt = system_clock::to_time_t(now);
    auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;

    std::ostringstream oss;
    oss << std::put_time(std::localtime(&itt), "%F %T") << '.' << std::setw(3) << std::setfill('0') << ms.count();
    return oss.str();
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
        reader_qos << dds::core::policy::DatRepresentation(dds::core::policy::DataRepresentationId::XCDR2);
        /*reader_qos << dds::core::policy::Ownership(dds::core::policy::OwnershipKind::SHARED);
        reader_qos << dds::core::policy::Reliability(dds::core::policy::ReliabilityKind::RELIABLE, dds::core::Duration::infinite());
        reader_qos << dds::core::policy::Durability(dds::core::policy::DurabilityKind::TRANSIENT_LOCAL);
        reader_qos << dds::core::policy::History::KeepAll();*/
        dds::sub::DataReaderListener<HelloWorld>* reader_listener;
        dds::core::status::StatusMask reader_mask;
        auto dataState = dds::sub::status::DataState::any();

        dds::sub::DataReader<HelloWorld> reader(subscriber, topic, reader_qos, reader_listener, reader_mask);

        // The callback where we want to get notified on new data
        std::function<void()> callback = [&reader, &dataState]() {
            std::cout << "[" << current_timestamp() << "] Received samples ..." << std::endl;

            dds::sub::LoanedSamples<HelloWorld> samples = reader.select(dataState).take();
            for (auto sample : samples) {
                dds::sub::SampleInfo sampleInfo = sample.info();
                dds::sub::status::DataState dataState = sampleInfo.state();
                dds::sub::status::InstanceState instanceState = dataState.instance_state();

                if (sampleInfo.valid() && instanceState == dds::sub::status::InstanceState::alive()) {
                    HelloWorld const& t = sample.data();

                    std::cout << "[Received] (HelloWorld) index:" << t.index() << ", message: " << t.message() << std::endl;
                } else {
                    std::cout << "[Received] (HelloWorld) INVALID" << std::endl;
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
        std::cout << "Exception: " << e.what() << std::endl;
        return 1;
    }

    std::cout << "Exit..." << std::endl;
    return 0;
}
