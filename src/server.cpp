#include <Simple-Web-Server/server_http.hpp>

using HttpServer = SimpleWeb::Server<SimpleWeb::HTTP>;

int main(int argc, char* argv[])
{
	HttpServer server;
	server.config.port = 8080;

    if (argc == 2)
    {
        server.config.port = std::stoi(argv[1]);
    }

	std::map<std::string, std::string> data_map;

  	server.resource["^/check$"]["POST"] = [&data_map](std::shared_ptr<HttpServer::Response> response, std::shared_ptr<HttpServer::Request> request)
  	{
        auto content = request->content.string();
        if (data_map.count(content) == 0)
            data_map[content] = "-";
    	response->write(data_map[content]);
	};

	server.resource["^/submit$"]["POST"] = [&data_map](std::shared_ptr<HttpServer::Response> response, std::shared_ptr<HttpServer::Request> request)
	{
    	auto content = request->content.string();
    	std::cout << content << std::endl;
        auto pos = content.find('=');
        if (pos != std::string::npos)
        {
            auto key = content.substr(0, pos);
            auto value = content.substr(pos + 1, std::string::npos);
            data_map[key] = value;
        }
    	*response << "HTTP/1.1 200 OK\r\nContent-Length: " << content.length() << "\r\n\r\n" << content;
    };

    server.on_error = [](std::shared_ptr<HttpServer::Request>, const SimpleWeb::error_code& ec)
    {
    	if (ec == SimpleWeb::errc::operation_canceled)
    	{
    		std::cerr << "Operation cancelled" << std::endl;
    	}
    	else
    	{
    		std::cerr << "Server error!" << std::endl;
    	}
  	};

	std::promise<unsigned short> server_port;
	std::thread server_thread([&server, &server_port]()
	{
	    server.start([&server_port](unsigned short port)
	    {
	    	server_port.set_value(port);
	    });
	});
 
	std::cout << "Server listening on port " << server_port.get_future().get() << std::endl << std::endl;
	server_thread.join();
}