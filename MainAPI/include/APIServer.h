#ifndef __APISERVER_H__
#define __APISERVER_H__

#include "../../utilities/include/utilities.h"
#include "../../utilities/include/Config.h"

#include<workflow/WFFacilities.h>
#include<wfrest/HttpServer.h>

#include<grpcpp/grpcpp.h>
#include "../../ServiceRegistry/include/ServiceInfo.pb.h"
#include "../../ServiceRegistry/include/ServiceInfo.grpc.pb.h"


class RCClient
{
public:
    RCClient();
    std::pair<grpc::Status, ServiceInfo::MicroServiceInfo> discovery(std::string name);

private:
    std::unique_ptr<ServiceInfo::ServiceRegistry::Stub> _regist_center_stub;
};

class APIServer
{
public:
    APIServer(int count = 1);
    ~APIServer();
    void start();
    void stop();

private:
    void setRoutes();
    // ds_utilities::STATUS serviceDiscovery(std::string service_name, ds_utilities::MicroServiceInfo & service_info);
    grpc::Status serviceDiscovery(std::string service_name, ServiceInfo::MicroServiceInfo & service_info);

private:
    void staticResource(const wfrest::HttpReq * req, wfrest::HttpResp * resp);
    void loginService(const wfrest::HttpReq * req, wfrest::HttpResp * resp);
    void registerService(const wfrest::HttpReq * req, wfrest::HttpResp * resp);
    void jwtService(const wfrest::HttpReq * req, wfrest::HttpResp * resp);
    void downloadService(const wfrest::HttpReq * req, wfrest::HttpResp * resp);
    void uploadService(const wfrest::HttpReq * req, wfrest::HttpResp * resp);
    void searchService(const wfrest::HttpReq * req, wfrest::HttpResp * resp);
    void recommendService(const wfrest::HttpReq * req, wfrest::HttpResp * resp);
    void semanticService(const wfrest::HttpReq * req, wfrest::HttpResp * resp);
    void ragService(const wfrest::HttpReq * req, wfrest::HttpResp * resp);
    std::string uriDecode(const std::string & encode_str);
private:
    WFFacilities::WaitGroup _wait_group;
    wfrest::HttpServer _server;
    RCClient _rc_client;
};

#endif