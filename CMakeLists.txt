cmake_minimum_required(VERSION 3.16)

project(DigitalSystem)

set(CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE DEBUG)
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -g")

find_package(Protobuf REQUIRED CONFIG PATHS /usr/local/lib/cmake/protobuf)
find_package(gRPC REQUIRED CONFIG PATHS /usr/local/lib/cmake/grpc)

# APIServer
set(APIServer_source_file
    MainAPI/main.cpp
    MainAPI/APIServer.cpp
    ServiceRegistry/ServiceInfo.pb.cc
    ServiceRegistry/ServiceInfo.grpc.pb.cc
    utilities/Config.cpp
)

set(APIServer_head_file
    MainAPI/include/APIServer.h
    ServiceRegistry/include/ServiceInfo.pb.h
    ServiceRegistry/include/ServiceInfo.grpc.pb.h
)

add_executable(APIServer ${APIServer_source_file} ${APIServer_head_file})
set_target_properties(APIServer PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/MainAPI")
target_link_libraries(APIServer workflow wfrest protobuf::libprotobuf gRPC::grpc++ pthread z)

# 注册中心
set(ServiceRegistry_source_file 
    ServiceRegistry/main.cpp
    ServiceRegistry/ServiceRegistry.cpp
    ServiceRegistry/ServiceInfo.pb.cc
    ServiceRegistry/ServiceInfo.grpc.pb.cc
    utilities/Config.cpp
)

set(ServiceRegistry_head_file 
    ServiceRegistry/include/ServiceRegistry.h
    ServiceRegistry/include/ServiceInfo.pb.h
    ServiceRegistry/include/ServiceInfo.grpc.pb.h
)

add_executable(ServiceRegistry ${ServiceRegistry_source_file} ${ServiceRegistry_head_file})
set_target_properties(ServiceRegistry PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/ServiceRegistry")
target_link_libraries(ServiceRegistry protobuf::libprotobuf gRPC::grpc++ pthread z)
