#include "stdafx.h"
#include "http_servlet.h"

http_servlet::http_servlet(acl::socket_stream* stream, acl::session* session)
: acl::HttpServlet(stream, session)
{

}

http_servlet::~http_servlet(void)
{

}

bool http_servlet::doError(acl::HttpServletRequest&, acl::HttpServletResponse&)
{
	return false;
}

bool http_servlet::doUnknown(acl::HttpServletRequest&,
	acl::HttpServletResponse& res)
{
	res.setStatus(400);
	res.setContentType("text/html; charset=");
	// ���� http ��Ӧͷ
	if (res.sendHeader() == false)
		return false;
	// ���� http ��Ӧ��
	acl::string buf("<root error='unkown request method' />\r\n");
	(void) res.getOutputStream().write(buf);
	return false;
}

bool http_servlet::doGet(acl::HttpServletRequest& req,
	acl::HttpServletResponse& res)
{
	return doPost(req, res);
}

bool http_servlet::doPost(acl::HttpServletRequest& req,
	acl::HttpServletResponse& res)
{
	bool keep_alive = req.isKeepAlive();

	res.setContentType("text/html; charset=utf-8")	// ������Ӧ�ַ���
		.setKeepAlive(keep_alive)		// �����Ƿ񱣳ֳ�����
		.setChunkedTransferEncoding(true);	// chunked ����ģʽ

	// ���� http ��Ӧ��
	acl::string buf("first line\r\nsecond line\r\nthird line\r\n\r\n");
	if (res.write(buf) == false)
	{
		logger_error("write error!");
		return false;
	}

	for (int i = 0; i < 10; i++)
	{
		buf = "hello";
		if (res.write(buf) == false)
		{
			logger_error("write error!");
			return false;
		}
		if (res.write((acl::string)" ") == false)
		{
			logger_error("write error!");
			return false;
		}
		if (res.write((acl::string)"world") == false)
		{
			logger_error("write error!");
			return false;
		}
		if (res.write((acl::string)"\r\n") == false)
		{
			logger_error("write error!");
			return false;
		}
	}

	for (int j = 0; j < 10; j++)
	{
		for (int i = 0; i < 10; i++)
		{
			if (res.write((acl::string)"X") == false)
			{
				logger_error("write error!");
				return false;
			}
		}

		if (res.write((acl::string)"\r\n") == false)
		{
			logger_error("write error!");
			return false;
		}
	}

	// ���һ�в�д \r\n
	if (res.write((acl::string)"Bye") == false)
	{
		logger_error("write error!");
		return false;
	}

	return res.write(NULL, 0) && keep_alive;
}