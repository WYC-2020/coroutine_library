#pragma once

class http_servlet : public acl::HttpServlet
{
public:
	http_servlet(acl::socket_stream*, acl::session*, int port = 80);
	~http_servlet();

protected:
	// @override
	bool doGet(request_t&, response_t&);

	// @override
	bool doPost(request_t&, response_t&);

	// @override
	bool doError(request_t&, response_t&);

	// @override
	bool doOther(request_t&, response_t&, const char* method);

	bool doConnect(request_t&, response_t&);

private:
	int port_;
	typedef bool (http_servlet::*handler_t)(request_t&,response_t&);
	std::map<std::string, handler_t> handlers_;

	bool on_hello(request_t&, response_t&);
	bool transfer_get(request_t&, response_t&);
	bool transfer_post(request_t&, response_t&);

	bool transfer_tcp(acl::socket_stream& local, acl::socket_stream& peer);
};
