#pragma once
#include<string>
using namespace std;
//namespace usp
//{
	class Response
	{
	private:
		string header;
		string body;
	public:
		//string ReadHeader();
		Response();
		Response(string head,string bo);
		string getheader();
		string getbody();
	};
//}
