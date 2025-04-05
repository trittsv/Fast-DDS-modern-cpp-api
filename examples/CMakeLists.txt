project(fastdds_modern_cpp_example VERSION 1 LANGUAGES CXX)

find_package(fastdds 3 REQUIRED)

#${FASTDDSGEN_EXE} -cs -I ${CMAKE_CURRENT_SOURCE_DIR} -language c++ -d "${CMAKE_BINARY_DIR}" HelloWorldData.idl

add_executable(publisher_app publisher_app.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gen/HelloWorldPubSubTypes.cxx
    ${CMAKE_CURRENT_SOURCE_DIR}/gen/HelloWorldTypeObjectSupport.cxx
    ${CMAKE_CURRENT_SOURCE_DIR}/gen/HelloWorldCdrAux.ipp
)
target_include_directories(publisher_app SYSTEM PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/gen)
target_link_libraries(publisher_app fastdds fastcdr)


add_executable(subscriber_app subscriber_app.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gen/HelloWorldPubSubTypes.cxx
    ${CMAKE_CURRENT_SOURCE_DIR}/gen/HelloWorldTypeObjectSupport.cxx
    ${CMAKE_CURRENT_SOURCE_DIR}/gen/HelloWorldCdrAux.ipp
)
target_include_directories(subscriber_app SYSTEM PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/gen)
target_link_libraries(subscriber_app fastdds fastcdr)

