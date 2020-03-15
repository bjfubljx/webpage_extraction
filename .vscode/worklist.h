#include<string>
#include<vector>

using namespace std;

class worklist{
private:
	vector<string> urls;
public:
	bool isempty();
	void pushone(string ur);
	string getone();
};