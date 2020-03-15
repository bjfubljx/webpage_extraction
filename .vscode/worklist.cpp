#include "worklist.h"
bool worklist::isempty()
{
	if(urls.empty())
		return true;
	return false;
}

void worklist::pushone(string ur)
{
	urls.push_back(ur);
}

string worklist::getone()
{
	string one;
	one=urls.back();
	urls.pop_back();
	return one;
}


