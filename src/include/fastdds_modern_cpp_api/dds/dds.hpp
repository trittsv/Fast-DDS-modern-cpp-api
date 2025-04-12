#pragma once

#include <fastdds_modern_cpp_api/dds/core/cond/WaitSet.hpp>
#include <fastdds_modern_cpp_api/dds/core/policy/CorePolicy.hpp>
#include <fastdds_modern_cpp_api/dds/core/Duration.hpp>
#include <fastdds_modern_cpp_api/dds/core/Exception.hpp>
#include <fastdds_modern_cpp_api/dds/sub/qos/DataReaderQos.hpp>
#include <fastdds_modern_cpp_api/dds/pub/qos/DataWriterQos.hpp>
#include <fastdds_modern_cpp_api/dds/sub/qos/SubscriberQos.hpp>
#include <fastdds_modern_cpp_api/dds/pub/qos/PublisherQos.hpp>
#include <fastdds_modern_cpp_api/dds/pub/DataWriter.hpp>
#include <fastdds_modern_cpp_api/dds/pub/Publisher.hpp>
#include <fastdds_modern_cpp_api/dds/pub/DataWriterListener.hpp>
#include <fastdds_modern_cpp_api/dds/sub/cond/ReadCondition.hpp>
#include <fastdds_modern_cpp_api/dds/sub/qos/DataReaderQos.hpp>
#include <fastdds_modern_cpp_api/dds/sub/qos/SubscriberQos.hpp>
#include <fastdds_modern_cpp_api/dds/sub/status/DataState.hpp>
#include <fastdds_modern_cpp_api/dds/sub/DataReader.hpp>
#include <fastdds_modern_cpp_api/dds/sub/DataReaderListener.hpp>
#include <fastdds_modern_cpp_api/dds/sub/SampleInfo.hpp>
#include <fastdds_modern_cpp_api/dds/sub/Subscriber.hpp>
#include <fastdds_modern_cpp_api/dds/sub/SubscriberListener.hpp>
#include <fastdds_modern_cpp_api/dds/topic/Topic.hpp>
#include <fastdds_modern_cpp_api/dds/topic/qos/TopicQos.hpp>
#include <fastdds_modern_cpp_api/dds/domain/DomainParticipant.hpp>


// This wraps the FastDDS c++ api into the DDS Standard modern C++ API

