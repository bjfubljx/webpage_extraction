#include <string.h>
#include <vector>
#include <cstring>
#include <dirent.h>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h> 
#include <time.h>
#include <unistd.h>
#include <iostream>
#include <sys/types.h>
#include <dirent.h>
#include <vector>
#include <algorithm>
#include<sys/stat.h>
using namespace std;
class Information
{
  private:
    string title;
    string author;
    string digest;
    string charset;
    string release_time;
    string domain_name;
    string text;
  public:
    Information(){}
    Information(string ctitle, string cauthor, string cdigest, string ccharset, string crelease_time, string cdomain_name, string ctext)
    {
        title = ctitle;
        author = cauthor;
        digest = cdigest;
        charset = ccharset;
        release_time = crelease_time;
        domain_name = cdomain_name;
        text = ctext;
    }
    Information(const Information &c)
    {
        title = c.title;
        author = c.author;
        digest = c.digest;
        charset = c.charset;
        release_time = c.release_time;
        domain_name = c.domain_name;
        text = c.text;
    }
    string get_title()
    {
        return title;
    }
    string get_author()
    {
        return author;
    }
    string get_charset()
    {
        return charset;
    }
    string get_digest()
    {
        return digest;
    }
    string get_release_time()
    {
        return release_time;
    }
    string get_domain()
    {
        return domain_name;
    }
    string get_text()
    {
        return text;
    }
    void set_title(string x)
    {
        title = x;
    }
    void set_author(string x)
    {
        author = x;
    }
    void set_charset(string x)
    {
        charset = x;
    }
    void set_digest(string x)
    {
        digest = x;
    }
    void set_release_time(string x)
    {
        release_time = x;
    }
    void set_domain_name(string x)
    {
        domain_name = x;
    }
    void settext(string x)
    {
        text = x;
    }
};