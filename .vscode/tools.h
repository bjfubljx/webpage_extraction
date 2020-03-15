#include <string>
#include <vector>
#include<functional>
using namespace std;
vector<string> GetAllUrls(string raw_text) {

    enum class UrlParseStatus {
        NONE,
        URL,
    };
    //cout<<"raw_text:"<<raw_text<<endl;
    auto res = vector<string>();
    UrlParseStatus status = UrlParseStatus::NONE;
    string token;
    for (auto i : raw_text) {
        if (i == ' '){
            token.clear();
        } else {
            token.push_back(i);
        }

        if (status==UrlParseStatus::NONE && token == "href=\"") {
            status = UrlParseStatus::URL;
            token.clear();
        } else if (status == UrlParseStatus::URL && i == '"'){
            token.pop_back();
            res.push_back(token);
            token.clear();
            status = UrlParseStatus::NONE;
        }
    }
    return res;
}

bool IsBeginWith(string s, string m){
    if (m.length() > s.length()){
        return false;
    }
    for (int i =0 ; i<m.length(); i++){
        if(m[i] != s[i]){
            return false;
        }
    }
    return true;
}

string Gethost(string url)
{
    size_t pos=url.find("://");
    if(pos!=url.npos)
        url=url.substr(pos+3);
    pos=url.find("/");
    if(pos==url.npos)
        cout<<url;
    else
    url=url.substr(0,pos);
    return url;
}

string Getpath(string url)
{
        size_t pos = url.find("://");
        if (pos != url.npos) url = url.substr(pos + 3);
        pos = url.find('/');
        if(pos == url.npos)
                url="/";
        else
                url= url.substr(pos);
        return url;
}

vector<string> GetSinaBlog(string raw_text)
{
         vector<string> all;
         all=GetAllUrls(raw_text);
         vector<string> after;
                int i,j;
                string m="http";
                string host;
                string path;
                string ho="blog";
                string pa="/s";
                //cout<<"uusize:"<<uu.size()<<endl;
                for(i=0;i<all.size();i++)
                {
                        if(IsBeginWith(all[i],m))
                        {
                                host=Gethost(all[i]);
                                path=Getpath(all[i]);
                                if(IsBeginWith(host,ho)&&IsBeginWith(path,pa))
                                        after.push_back(all[i]);
                                        //cout<<i<<":"<<uu[i]<<endl;
                        }
                }
               // for(j=0;j<after.size();j++)
                 //       cout<<j<<":"<<after[j]<<endl;
          return after;

}

vector<string> GetGmwPolic(string raw_text)
{
        vector<string> all;
         all=GetAllUrls(raw_text);
         vector<string> after;
                int i,j;
                string m="http";
                string host;
                string path;
                string ho="politics";
                string pa="/2019";
                //cout<<"uusize:"<<uu.size()<<endl;
                for(i=0;i<all.size();i++)
                {
                        if(IsBeginWith(all[i],m))
                        {
                                host=Gethost(all[i]);
                                path=Getpath(all[i]);
                                if(IsBeginWith(host,ho)&&IsBeginWith(path,pa))
                                        after.push_back(all[i]);
                                        //cout<<i<<":"<<uu[i]<<endl;
                        }
                }
               // for(j=0;j<after.size();j++)
                 //       cout<<j<<":"<<after[j]<<endl;
          return after;

}