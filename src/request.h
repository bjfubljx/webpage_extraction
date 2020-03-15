#pragma once
#include<string>
#include"Response.h"
using namespace std;

//namespace usp{

    class Request
    {
	private:
		string raw_url;
		string host;
		string path;
		string header;
    public:
		 Request(string raw);
	     //void parseHostAndPagePath(string url);
		 void setHeader(string path,string host);
	     Response getPageContent(string hostUrl,string header);
	     string getPath();
	     string getHost();
	     string getHeader();
    };
//}
