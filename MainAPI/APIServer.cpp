#include "./include/APIServer.h"

APIServer::APIServer(int count)
:_wait_group(count)
{
    setRoutes();
}

APIServer::~APIServer()
{

}

void APIServer::start()
{
    int port = atoi(Config::getInstance()->getConfig("port").c_str());

    if(_server.track().start(port) == 0)
    {
        std::cout << "Start\n";
        _server.list_routes();
        _wait_group.wait();
        _server.stop();
    }
    else
    {
        std::cerr << "[ERROR] : HTTP Server Start Failed...\n";
        exit(-1);
    }
}

void APIServer::stop()
{
    _wait_group.done();
}

void APIServer::setRoutes()
{
    std::cout << "GET : / \n";
    _server.GET("/", [this](const wfrest::HttpReq * req, wfrest::HttpResp * resp)
    {
        staticResource(req, resp);
    });

    std::cout << "GET : login \n";
    _server.GET("/login", [this](const wfrest::HttpReq * req, wfrest::HttpResp * resp)
    {
        loginService(req, resp);
    });

    _server.GET("/register", [this](const wfrest::HttpReq * req, wfrest::HttpResp * resp)
    {
        registerService(req, resp);
    });

    _server.GET("/jwt", [this](const wfrest::HttpReq * req, wfrest::HttpResp * resp)
    {
        jwtService(req, resp);
    });

    _server.GET("/download", [this](const wfrest::HttpReq * req, wfrest::HttpResp * resp)
    {
        downloadService(req, resp);
    });

    _server.GET("/upload", [this](const wfrest::HttpReq * req, wfrest::HttpResp * resp)
    {
        uploadService(req, resp);
    });

    _server.GET("/search", [this](const wfrest::HttpReq * req, wfrest::HttpResp * resp)
    {
        searchService(req, resp);
    });

    _server.GET("/recommend", [this](const wfrest::HttpReq * req, wfrest::HttpResp * resp)
    {
        recommendService(req, resp);
    });

    _server.GET("/semantic", [this](const wfrest::HttpReq * req, wfrest::HttpResp * resp)
    {
        semanticService(req, resp);
    });

    _server.GET("/rag", [this](const wfrest::HttpReq * req, wfrest::HttpResp * resp)
    {
        ragService(req, resp);
    });
}

grpc::Status APIServer::serviceDiscovery(std::string service_name, ServiceInfo::MicroServiceInfo & service_info)
{
    auto [status, ms_info] = _rc_client.discovery(service_name);
    service_info.CopyFrom(ms_info);

    return status;
}

void APIServer::staticResource(const wfrest::HttpReq * req, wfrest::HttpResp * resp)
{
}

void APIServer::loginService(const wfrest::HttpReq * req, wfrest::HttpResp * resp)
{
    std::cout << "IN GET : / \n";

    std::string param = uriDecode(req->query("query"));

    ServiceInfo::MicroServiceInfo ms_info;
    auto status = serviceDiscovery("login", ms_info);

    if(status.ok())
    {
        std::string info = ms_info.service_name() + " " +
                           ms_info.ip() + ":" +
                           ms_info.port() + " " +
                           ms_info.version();

        std::cout << info << "\n";

        resp->String(info);
    }
    else
    {
        resp->String(status.error_message());
    }
}

void APIServer::registerService(const wfrest::HttpReq * req, wfrest::HttpResp * resp)
{

}

void APIServer::jwtService(const wfrest::HttpReq * req, wfrest::HttpResp * resp)
{

}

void APIServer::downloadService(const wfrest::HttpReq * req, wfrest::HttpResp * resp)
{

}

void APIServer::uploadService(const wfrest::HttpReq * req, wfrest::HttpResp * resp)
{

}

void APIServer::searchService(const wfrest::HttpReq * req, wfrest::HttpResp * resp)
{

}

void APIServer::recommendService(const wfrest::HttpReq * req, wfrest::HttpResp * resp)
{

}

void APIServer::semanticService(const wfrest::HttpReq * req, wfrest::HttpResp * resp)
{

}

void APIServer::ragService(const wfrest::HttpReq * req, wfrest::HttpResp * resp)
{

}

std::string APIServer::uriDecode(const std::string & encode_str)
{
    std::ostringstream decode_oss;
    size_t len = encode_str.length();

    for(size_t i = 0; i < len; i++)
    {
        if(encode_str[i] == '%' && i + 2 < len)
        {
            std::string hex = encode_str.substr(i + 1, 2);
            char decoded_char = static_cast<char>(std::stoi(hex, nullptr, 16));
            decode_oss << decoded_char;
            i += 2;
        }
        else if(encode_str[i] == '+')
        {
            decode_oss << ' ';
        }
        else
        {
            decode_oss << encode_str[i];
        }
    }

    return decode_oss.str();
}

RCClient::RCClient()
{
    std::string rc_ip = Config::getInstance()->getConfig("register_center_ip");
    std::string rc_port = Config::getInstance()->getConfig("register_center_port");

    std::shared_ptr<grpc::Channel> rc_channel = grpc::CreateChannel(rc_ip + ":" + rc_port, grpc::InsecureChannelCredentials());
    _regist_center_stub = std::move(ServiceInfo::ServiceRegistry::NewStub(rc_channel));
}

std::pair<grpc::Status, ServiceInfo::MicroServiceInfo> RCClient::discovery(std::string name)
{
    ServiceInfo::GetServiceInfoReq req;
    ServiceInfo::GetServiceInfoResp resp;
    grpc::ClientContext ctx;

    req.set_service_name(name);

    auto status = _regist_center_stub->getServiceInfo(&ctx, req, &resp);

    return {status, resp.service_info()};
}