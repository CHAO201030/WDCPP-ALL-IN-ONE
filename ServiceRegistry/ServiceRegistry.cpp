#include "./include/ServiceRegistry.h"

Status ServiceImpl::getServiceInfo(ServerContext* context, const GetServiceInfoReq* request, GetServiceInfoResp* response)
{   

#if 1
    ServiceInfo::MicroServiceInfo temp_info = generateMicroServiceInfo(
        "login_service",
        "192.168.239.128",
        "6666",
        "v0.1",
        ServiceInfo::Status::OK
    );

    _service_table.insert({"login", temp_info});
#endif


    std::string req_service_name = request->service_name();
    std::cout << "APIServer request : " << req_service_name << "\n";

    auto it = _service_table.find(req_service_name);
    if( it != _service_table.end())
    {
        ServiceInfo::MicroServiceInfo ms_info = generateMicroServiceInfo(
            it->second.service_name(),
            it->second.ip(),
            it->second.port(),
            it->second.version(),
            it->second.status()
        );

        response->mutable_service_info()->CopyFrom(ms_info);

        return Status::OK;
    }
    else
    {
        return Status(grpc::StatusCode::NOT_FOUND, req_service_name + " is not found");
    }
}

Status ServiceImpl::setServiceInfo(ServerContext* context, const SetServiceInfoReq* request, SetServiceInfoResp* response)
{
    return Status::OK;
}

ServiceInfo::MicroServiceInfo ServiceImpl::generateMicroServiceInfo(std::string service_name, std::string ip, std::string port, std::string version, ServiceInfo::Status status)
{
    ServiceInfo::MicroServiceInfo ms_info;
    ms_info.Clear();

    ms_info.set_service_name(service_name);
    ms_info.set_ip(ip);
    ms_info.set_port(port);
    ms_info.set_version(version);
    ms_info.set_status(status);

    return ms_info;
}

RegistCenter::RegistCenter()
{
    std::string server_addr = Config::getInstance()->getConfig("ip") + ":" + Config::getInstance()->getConfig("port");
    _server_builder.AddListeningPort(server_addr, grpc::InsecureServerCredentials());
    _server_builder.RegisterService(&_service_impl);
}

void RegistCenter::start()
{
    std::unique_ptr<Server> uptr_server(_server_builder.BuildAndStart());

    uptr_server->Wait();
}