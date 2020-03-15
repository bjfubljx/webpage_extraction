#include<string>
#include"Response.h"

Response::Response()
{}
Response::Response(string head,string bo)
{
	header=head;
	body=bo;
}
string Response::getheader()
{
	return header;
}
string Response::getbody()
{
	return body;
}
