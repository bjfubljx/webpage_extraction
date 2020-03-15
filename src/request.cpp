#include<iostream>
#include<stdio.h>
#include<string>
#include<netdb.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netdb.h>
#include<fstream>
#include"request.h"
using namespace std;

Request::Request(string raw)
{
	raw_url=raw;
	//host="";
	//path="";
	//header="";
	string hostUrl,pagePath;
        hostUrl=raw;
        pagePath="/";
        int pos=hostUrl.find("http://");
        if(-1!=pos)
                hostUrl=hostUrl.replace(pos,7,"");
        pos=hostUrl.find("https://");
        if(-1!=pos)
                hostUrl=hostUrl.replace(pos,8,"");
        pos=hostUrl.find("/");
        if(-1!=pos)
        {
                pagePath=hostUrl.substr(pos);
                hostUrl=hostUrl.substr(0,pos);
        }
        host=hostUrl;
        path=pagePath;

}/*
void Request::parseHostAndPagePath(string url)
{
	string hostUrl,pagePath;
	hostUrl=url;
	pagePath="/";
	int pos=hostUrl.find("http://");
	if(-1!=pos)
		hostUrl=hostUrl.replace(pos,7,"");
	pos=hostUrl.find("https://");
	if(-1!=pos)
		hostUrl=hostUrl.replace(pos,8,"");
	pos=hostUrl.find("/");
	if(-1!=pos)
	{
		pagePath=hostUrl.substr(pos);
		hostUrl=hostUrl.substr(0,pos);
	}
	host=hosUrl;
	path=pagePath;
}*/

void Request::setHeader(string path,string host)
{
	string requestHeader;
	requestHeader="GET "+path+" HTTP/1.1\r\n";
	requestHeader+="Host:"+host+"\r\n";
	requestHeader+="Accept: */*\r\n";
	requestHeader+="User-Agent: Mozilla/4.0(compatible)\r\n";
	requestHeader+="connection:Keep-Alive\r\n";
	requestHeader+="\r\n";
    cout<<"header:"<<requestHeader<<endl;//Ҫ��Ҫ��ӡ������
    this->header=requestHeader;
}

Response Request::getPageContent(string hostUrl,string header)
{
	struct hostent *host;
	//string hostUrl,pagePath;
	//parseHostAndPagePath(url,hostUrl,pagePath);
	//cout<<"hosturl: "<<hostUrl<<endl;
	const char* name=hostUrl.c_str();
	if(NULL==(host=gethostbyname(name)))
	{
		herror(NULL);
		cout<<"gethostbyname error\n"<<endl;
		exit(1);
	}

	struct sockaddr_in pin;
	int port=80;
	bzero(&pin,sizeof(pin));
	pin.sin_family=AF_INET;
	pin.sin_port=htons(port);
	pin.sin_addr.s_addr=((struct in_addr*)(host->h_addr))->s_addr;
	int isock;
	if((isock=socket(AF_INET,SOCK_STREAM,0))==-1)
	{
		cout<<"open socket error\n"<<endl;
		exit(1);
	}

	if(connect(isock,(const sockaddr*)&pin,sizeof(pin))==-1)
	{
		cout<<"connect eror\n"<<endl;
		exit(1);
	}
	if(send(isock,header.c_str(),header.size(),0)==-1)
	{
		cout<<"send error\n"<<endl;
		exit(1);
	}

	int done=0;
	int chars=0;
	string head;
	int l=0;
	char buffer[512];
	while(done==0)
	{
		l=recv(isock,buffer,1,0);
		if(l<0)
		    done=1;
		switch(*buffer)
		{
			case '\r':
				break;
			case '\n':
				if(chars==0)
					done=1;
				chars=0;
				break;
			default:
				chars++;
				break;
		}
		head+=buffer;
	}
	
	string content;
	do
	{
		l=recv(isock,buffer,sizeof(buffer)-1,0);
		// cout<<"l:"<<l<<endl;
	       
		    // cout<<"buffer:"<<buffer;

		if(l<0)
			break;
		content+=buffer;
	}while(l>0);
	//close(isock);
	Response res(head,content);
	return res;
}

string Request::getPath()
{
	return path;
}

string Request::getHost()
{
	return host;
}

string Request::getHeader()
{
	return header;
}

