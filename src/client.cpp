#include <Simple-Web-Server/client_http.hpp>

using HttpClient = SimpleWeb::Client<SimpleWeb::HTTP>;

void quit_usage()
{
	printf("Usage:\n  -s [addr:port] [key] [value] : set a value\n  -c [addr:port] [key]         : check a value\n");
	exit(0);
}

int main(int argc, char* argv[])
{
	if (argc < 4 || argc > 5)
		quit_usage();

	std::string server_addr = argv[2];

	if (strcmp(argv[1], "-c") == 0) //check the data
	{
		if (argc != 4)
			quit_usage();

		std::string key = argv[3];

		HttpClient client(server_addr);
	    try
	    {
	    	auto r2 = client.request("POST", "/check", key);
	    	auto str = r2->content.rdbuf();
	    	std::cout << str << std::endl;
	    }
	    catch(const SimpleWeb::system_error &e)
	    {
	    	std::cerr << "Client request error: " << e.what() << std::endl;
	    }
	}
	else if (strcmp(argv[1], "-s") == 0) //set the data
	{
		if (argc != 5)
			quit_usage();

		std::string key = argv[3];
		std::string value = argv[4];
		std::string data_string = key + "=" + value;

		HttpClient client(server_addr);
	    try
	    {
	    	auto r2 = client.request("POST", "/submit", data_string);
	    }
	    catch(const SimpleWeb::system_error &e)
	    {
	    	std::cerr << "Client request error: " << e.what() << std::endl;
	    }
	}
	else
	{
		quit_usage();
	}
}