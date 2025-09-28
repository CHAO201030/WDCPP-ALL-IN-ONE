#ifndef __SERVICE_REGISTRY_H__
#define __SERVICE_REGISTRY_H__

#include "../../utilities/include/utilities.h"
#include "../../utilities/include/Config.h"

#include <grpcpp/grpcpp.h>
#include "ServiceInfo.pb.h"
#include "ServiceInfo.grpc.pb.h"

using ::grpc::Server;
using ::grpc::ServerBuilder;
using ::grpc::Status;
using ::grpc::ServerContext;
using ::ServiceInfo::GetServiceInfoReq;
using ::ServiceInfo::GetServiceInfoResp;
using ::ServiceInfo::SetServiceInfoReq;
using ::ServiceInfo::SetServiceInfoResp;

class RegistCenter;

class ServiceImpl final : public ServiceInfo::ServiceRegistry::Service
{
    friend class RegistCenter;

public:
    virtual Status getServiceInfo(ServerContext* context, const GetServiceInfoReq* request, GetServiceInfoResp* response) override;
    virtual Status setServiceInfo(ServerContext* context, const SetServiceInfoReq* request, SetServiceInfoResp* response) override;

private:
    ServiceInfo::MicroServiceInfo generateMicroServiceInfo(std::string service_name, std::string ip, std::string port, std::string version, ServiceInfo::Status status);

private:
    std::unordered_map<std::string, ServiceInfo::MicroServiceInfo> _service_table;
};

class RegistCenter
{
public:
    RegistCenter();
    void start();

private:
    ServiceImpl _service_impl;
    ServerBuilder _server_builder;
};

#endif