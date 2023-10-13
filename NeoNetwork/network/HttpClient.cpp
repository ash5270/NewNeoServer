﻿#include "HttpClient.h"
#include <iostream>
#include<memory>
neo::network::HttpClient::HttpClient()
{
	WSAInit();
	mSocket = 0;
	mIsConnect = false;
}

neo::network::HttpClient::HttpClient(const std::string& serverUrl, const int& port) :mServerUrl(serverUrl), mPort(port)
{
	WSAInit();
	mSocket = 0;
	mIsConnect = false;
}

neo::network::HttpClient::~HttpClient()
{
	WSACleanup();
}

bool neo::network::HttpClient::InitHttp()
{
	//tcp socket 초기화
	int result = 0;
	if (!WSAInit())
		return false;

	mSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	return true;
}

bool neo::network::HttpClient::CloseHttp()
{
	return false;
}

bool neo::network::HttpClient::WSAInit()
{
	int result = 0;
	WSADATA wsaData;
	result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result != 0)
	{
		//
		return false;
	}
	return true;
}

void neo::network::HttpClient::parseUrl(std::string& url, std::string& serverName, std::string& fileName, std::string& filePath, int& port)
{
	int n = 0;
	//서버 주소가 셋팅이 되어있지 않을때.
	if (mServerUrl == "")
	{
		//https:// 부분 제거
		if (url.substr(0, 7) == "http://")
			url.erase(0, 7);
		if (url.substr(0, 8) == "https://")
			url.erase(0, 8);

		//주소 뒤에 포트가 있는지 확인
		int n = url.find(':');
		std::string portString;
		if (n != std::string::npos)
		{
			int last = url.find('/');
			portString = url.substr(n + 1, last - 2);
			url.erase(n, last - n);
			port = std::stoi(portString);
		}
		else
			port = 80;

		//파일 위치 확인
		n = url.find('/');
		if (n != std::string::npos)
		{
			serverName = url.substr(0, n);
			filePath = url.substr(n);
			n = filePath.rfind('/');
			fileName = filePath.substr(n + 1);
		}
	}
	else
	{
		if (mServerUrl.substr(0, 7) == "http://")
			mServerUrl.erase(0, 7);
		if (mServerUrl.substr(0, 8) == "https://")
			mServerUrl.erase(0, 8);

		port = mPort;
		serverName = mServerUrl;

		n = url.find('/');
		if (n != std::string::npos)
		{
			filePath = url.substr(n);
			n = filePath.rfind('/');
			fileName = filePath.substr(n + 1);
		}
	}

}

void neo::network::HttpClient::closeSocket()
{
}


//response된 데이터를 파싱
neo::network::HttpData neo::network::HttpClient::parseResponseData(const std::string& response)
{
	HttpData header;
	//http 버전, http state code
	int offset = 0;

	header.HttpVersion = response.substr(offset, 8); offset += 8;
	header.HttpState = stoi(response.substr(++offset, 3)); offset += 3;
	int httpStateMsgCount = response.find("\r\n");
	header.HttpStateMsg = response.substr(13, httpStateMsgCount - ++offset);

	offset = response.find("\n") + 1;
	int headerLast = response.find("\r\n\r\n");

	//header 처리
	while (headerLast > offset)
	{
		//콜론 위치
		int colon = response.find_first_of(":", offset);
		//헤더 종류
		std::string head = response.substr(offset, colon++ - offset);
		int nextLine = response.find_first_of("\r\n", offset);
		//헤더 데이터
		std::string data = response.substr(colon + 1, nextLine - colon - 1);
		header.Headers.insert(std::make_pair(head, data));
		offset = nextLine + 2;
	}

	int startBody = response.find_first_of("\r\n", headerLast + 4);
	if (startBody < 0)
		header.Body = response.substr(headerLast + 4);
	else
	{
		int lastBody = response.find_first_of("\r\n", startBody + 4);
		header.Body = response.substr(startBody + 2, lastBody - startBody - 2);
	}
	return header;
}

std::ostringstream neo::network::HttpClient::setConnection(const std::string& url, const std::string& httpMethod)
{
	//url파싱
	std::string file;
	std::string filePath;
	std::string serverName;
	std::string copyUrl = url;
	//request header
	std::ostringstream request;

	int port;
	parseUrl(copyUrl, serverName, file, filePath, port);

	addrinfo hints;
	addrinfo* serverInfo;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	//DNS 서버에 질의후 데이터 동적할당
	//시간이 많이 지체될 수 도있다.
	//메인스레드에서 붙잡고 있지 않도록 별도의 스레드를 만들어서 돌리는 방안
	//GetAddrinfoEx()를 사용하던가
	int result = getaddrinfo(serverName.c_str(),
		std::to_string(port).c_str(),
		&hints, 
		&serverInfo);
	if (result != 0)
	{
		std::cout << "getaddrinfo error\n";
		freeaddrinfo(serverInfo);
		return request;
	}

	memcpy(&mSockAddr, serverInfo->ai_addr, sizeof(sockaddr));
	//해제해줘야함
	freeaddrinfo(serverInfo);
	//mSockAddr = *(SOCKADDR_IN*)serverInfo->ai_addr;
	if (!mIsConnect && connect(mSocket, (SOCKADDR*)&mSockAddr, sizeof(mSockAddr)) != 0)
	{
		//에러 출력
		std::cout << WSAGetLastError() << "\n";
		std::cout << "Could not connect\n";
		return request;
	}

	request << httpMethod << " " << filePath << " HTTP/1.1\r\n";
	request << "Host: " << serverName << "\r\n";
	request << "Connection: keep-alive\r\n";
	request << "Accept-Encoding: gzip, deflate, br\r\n";

	mIsConnect = true;
	return request;
}

neo::network::HttpData neo::network::HttpClient::Get(const std::string& url)
{
	std::ostringstream stream = setConnection(url, "GET");
	stream << "\r\n";
	std::string request_str = stream.str();
	if (!mIsConnect)
		return HttpData();
	send(mSocket, request_str.c_str(), strlen(request_str.c_str()), 0);
	int dataLength;
	char buf[4096];
	int len = recv(mSocket, buf, 4096, 0);
	std::string result(buf, len);

	return parseResponseData(result);
}

neo::network::HttpData neo::network::HttpClient::Post(const std::string& url, const std::string& data)
{
	std::ostringstream stream = setConnection(url, "POST");
	if (!mIsConnect)
		return HttpData();
	stream << "Content-Type: application/json" << "\r\n";
	stream << "Content-Length: " << data.length() << "\r\n\r\n";
	stream << data << "\r\n";
	std::string request_str = stream.str();

	send(mSocket, request_str.c_str(), strlen(request_str.c_str()), 0);

	int dataLength;
	char buf[1024];
	int len = recv(mSocket, buf, 1024, 0);
	std::string result(buf, len);
	return parseResponseData(result);
}
neo::network::HttpData neo::network::HttpClient::Put(const std::string& url, const std::string& data)
{
	std::ostringstream stream = setConnection(url, "PUT");
	if (!mIsConnect)
		return HttpData();
	stream << "Content-Type: application/json; charset=utf-8" << "\r\n";
	stream << "Content-Length: " << data.length() << "\r\n\r\n";
	stream << data << "\r\n";

	std::string request_str = stream.str();
	send(mSocket, request_str.c_str(), strlen(request_str.c_str()), 0);

	int dataLength;
	char buf[1024] = { 0 };
	int len = recv(mSocket, buf, 1024, 0);
	if (len < 0)
	{
		std::cout << WSAGetLastError() << "\n";
		return HttpData();
	}
	std::string result(buf, len);
	std::string out;
	return parseResponseData(result);
}

neo::network::HttpData neo::network::HttpClient::Delete(const std::string& url)
{
	std::ostringstream stream = setConnection(url, "DELETE");
	stream << "\r\n\r\n";
	if (!mIsConnect)
		return HttpData();

	std::string request_str = stream.str();
	send(mSocket, request_str.c_str(), strlen(request_str.c_str()), 0);

	int dataLength;
	char buf[1024];
	int len = recv(mSocket, buf, 1024, 0);
	if (len < 0)
		return HttpData();
	std::string result(buf, len);
	std::string out;
	
	//std::cout << result << "\n";
	return parseResponseData(result);
}