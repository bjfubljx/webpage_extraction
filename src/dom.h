#include <cstdio>
#include <stdlib.h>
#include <string.h>
#include <cstring>
#include <bits/algorithmfwd.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <regex.h>
#include <iostream>
#include <iconv.h>
#include <cstring>
#include <sys/stat.h>
#include <fstream>
#include "information.h"
using namespace std;
#define BUFSIZE 1024
#define BLOCKSIZE 200
#define RATE 0.8
char buf[BUFSIZE * BUFSIZE];
char ur[100];

int encoding(char *buf, size_t len)
{
    iconv_t cd;
    if (cd == (iconv_t)-1)
    {
        perror("获取字符转换描述符失败！\n");
        return -1;
    }
    size_t sz = BUFSIZE * BUFSIZE;
    char *tmp_str = (char *)malloc(sz);
    // 不要将原始的指针传进去，那样会改变原始指针的
    size_t inlen = len;
    size_t outlen = sz;
    char *in = buf;
    char *out = tmp_str;
    if (tmp_str == NULL)
    {
        iconv_close(cd);
        fprintf(stderr, "分配内存失败！\n");
        return -1;
    }
    memset(tmp_str, 0, sz);
    if (iconv(cd, &in, &inlen, &out, &outlen) == (size_t)-1)
    {
        iconv_close(cd);
        return -1;
    }
    iconv_close(cd);
}
string find_title()
{
    char *s = buf;
    int p1, p2;
    string find_title(s);
    p1 = find_title.find("<title>");
    p2 = find_title.find("</title>");
    string titl = find_title.substr(p1 + 7, p2 - p1 - 7);
    int j = 0;
    char til[BUFSIZE * BUFSIZE];
    for (int i = 0; i < titl.length(); i++)
    {
        if ((titl.at(i) == '\n'))
        {
            continue;
        }
        else
        {
            til[j] = titl.at(i);
            j++;
        }
    }
    return til;
}
string find_author()
{
    char *s = buf;
    int p1, p2;
    string find_author(s);
    p1 = find_author.find("ownernick");
    p2 = find_author.find("</span>", p1);
    string autho = find_author.substr(p1, p2 - p1);
    int p3, p4;
    p3 = autho.find_first_of('>');
    p4 = autho.find_first_of('<');
    string auth = autho.substr(p3 + 1, p4);
    return auth;
}
string find_time()
{
    char *s = buf;
    int p1, p2;
    string find_time(s);
    p1 = find_time.find("time SG_txtc");
    p2 = find_time.find("</span>", p1);
    string tim = find_time.substr(p1, p2 - p1);
    int p3, p4;
    p3 = tim.find_first_of('>');
    p4 = tim.find_first_of('<');
    string ti = tim.substr(p3 + 1, p4);
    return ti;
}
string find_description()
{
    char *s = buf;
    int p1, p2;
    string find_description(s);
    p1 = find_description.find("description\"");
    p2 = find_description.find("/>", p1);
    string descriptio = find_description.substr(p1, p2 - p1);
    int p3, p4;
    p3 = descriptio.find("content=\"");
    p4 = descriptio.rfind('\"');
    string descripti = descriptio.substr(p3 + 9, p4 - p3 - 9);
    return descripti;
}
string find_charset()
{
    char *s = buf;
    int p1, p2;
    string find_charset(s);
    p1 = find_charset.find("charset=");
    p2 = find_charset.find("\"", p1);
    string charse = find_charset.substr(p1 + 8, p2 - p1 - 8);
    return charse;
}
string url_domain()
{
    int p1, p2;
    string url_domain(ur);
    p1 = url_domain.find("http://");
    p2 = url_domain.find('/', p1 + 8);
    string url_domai = url_domain.substr(p1 + 7, p2 - 7);
    return url_domai;
}
string denoising()
{
    char *s1 = buf;
    int p1, p2;
    string s(s1);
    int flag1 = 0;
    int flag2 = 0;
    while (1)
    {
        if ((flag1 = s.find("<!--")) != string::npos)
        {
            flag2 = s.find("-->", flag1);
            s = s.erase(flag1, flag2 - flag1 + 3);
        }
        else
        {
            break;
        }
    }
    while (1)
    {
        if ((flag1 = s.find("/*")) != string::npos)
        {
            flag2 = s.find("*/", flag1);
            s = s.erase(flag1, flag2 - flag1 + 2);
        }
        else
        {
            break;
        }
    }
    while (1)
    {
        if ((flag1 = s.find("<div")) != string::npos)
        {
            flag2 = s.find(">", flag1);
            s = s.erase(flag1, flag2 - flag1 + 1);
        }
        else
        {
            break;
        }
    }
    while (1)
    {
        if ((flag1 = s.find("</div")) != string::npos)
        {
            flag2 = s.find(">", flag1);
            s = s.erase(flag1, flag2 - flag1 + 1);
        }
        else
        {
            break;
        }
    }
    while (1)
    {
        if ((flag1 = s.find("<DIV")) != string::npos)
        {
            flag2 = s.find(">", flag1);
            s = s.erase(flag1, flag2 - flag1 + 1);
        }
        else
        {
            break;
        }
    }
    while (1)
    {
        if ((flag1 = s.find("</DIV")) != string::npos)
        {
            flag2 = s.find(">", flag1);
            s = s.erase(flag1, flag2 - flag1 + 1);
        }
        else
        {
            break;
        }
    }
    while (1)
    {
        if ((flag1 = s.find("<script")) != string::npos)
        {
            flag2 = s.find("</script>", flag1);
            s = s.erase(flag1, flag2 - flag1 + 9);
        }
        else
        {
            break;
        }
    }
    int i = 0;
    int j = 0;
    char m[200000];
    for (int i = 0; i < s.length(); i++)
    {
        if ((s.at(i) == ' ') || (s.at(i) == '\n'))
        {
            continue;
        }
        else
        {
            m[j] = s.at(i);
            j++;
        }
    }
    int block_offset = 0;
    int text_weight[1000] = {0};
    int tag_flag = 0;
    string tex(m);
    for (int i = 0; i < tex.length(); i++)
    {
        if (m[i] == '<')
        {
            tag_flag = 0;
        }
        text_weight[block_offset] += tag_flag;
        if (m[i] == '>')
        {
            tag_flag = 1;
        }
        if (i % BLOCKSIZE == 0)
        {
            block_offset++;
        }
    }
    int thr_record[1000] = {0};
    int max_index = 0;
    int max_value = 0;
    for (int i = 0; i <= block_offset; i++)
    {
        if (float(text_weight[i]) / BLOCKSIZE >= RATE)
        {
            int j = i + 1;
            thr_record[i] += 1;
            while (float(text_weight[j]) / BLOCKSIZE >= RATE)
            {
                thr_record[i] += 1;
                j++;
            }
            if (thr_record[i] > max_value)
            {
                max_index = i;
                max_value = thr_record[i];
            }
        }
    }
    tex = tex.substr((max_index - 1) * BLOCKSIZE, thr_record[max_index] * BLOCKSIZE);
    int p3;
    int flag3 = 0;
    int flag4 = 0;
    while (1)
    {
        if ((flag3 = tex.find('<')) != string::npos)
        {
            if ((flag4 = tex.find('>')) != string::npos)
            {
                if (flag3 > flag4)
                {
                    tex = tex.erase(0, flag4 + 1);
                }
                else
                {
                    tex = tex.erase(flag3, flag4 - flag3 + 1);
                }
            }
            else
            {
                tex = tex.erase(flag3);
            }
        }
        else
        {
            break;
        }
    }
    return tex;
}
string gm_find_author()
{
    char *s = buf;
    int p1, p2;
    string find_author(s);
    p1 = find_author.find("author\"");
    p2 = find_author.find(">", p1);
    string autho = find_author.substr(p1, p2 - p1);
    int p3, p4;
    p3 = autho.find("content=\"");
    p4 = autho.rfind('\"');
    string auth = autho.substr(p3 + 9, p4 - p3 - 9);
    return auth;
}
string gm_find_description()
{
    char *s = buf;
    int p1, p2;
    string find_description(s);
    p1 = find_description.find("description\"");
    p2 = find_description.find(">", p1);
    string descriptio = find_description.substr(p1, p2 - p1);
    int p3, p4;
    p3 = descriptio.find("content=\"");
    p4 = descriptio.rfind('\"');
    string descripti = descriptio.substr(p3 + 9, p4 - p3 - 9);
    return descripti;
}
string gm_find_time()
{
    char *s = buf;
    int p1, p2;
    string find_time(s);
    p1 = find_time.find("m-con-time");
    p2 = find_time.find("</span>", p1);
    string tim = find_time.substr(p1, p2 - p1);
    int p3, p4;
    p3 = tim.find_first_of('>');
    p4 = tim.find_first_of('<');
    string ti = tim.substr(p3 + 1, p4);
    return ti;
}
string gm_find_charset()
{
    char *s = buf;
    int p1, p2;
    string find_charset(s);
    p1 = find_charset.find("charset=\"");
    p2 = find_charset.find("\"", p1 + 9);
    string charse = find_charset.substr(p1 + 9, p2 - p1 - 9);
    return charse;
}
void rfile(const Information &c)
{
    ifstream in;
    in.open("");
    if (!in)
    {
        cout << "Can't open the file" << endl;
    }
    char s[100];
    char a[10000];
    while(!in.eof())
    {
        in.getline(s,sizeof(s));
        strcat(a,s);
    }
}
void wfile(Information &c)
{
    string s = c.get_release_time().substr(0, c.get_release_time().find(" "));
    string f = c.get_domain();
    char a[72] = "./";
    char d[2];
    d[0] = '/';
    d[1] = '\0';
    char e[5];
    e[0] = '.';
    e[1] = 't';
    e[2] = 'x';
    e[3] = 't';
    e[4] = '\0';
    vector<string> file_name1;
    vector<string> file_path1;
    char path12[72] = "./";
    strcat(a, s.c_str());
    // cout<<a<<endl;
    mkdir(a, S_IRWXU);
    strcat(a,d);
    strcat(a,c.get_domain().c_str());
    mkdir(a,S_IRWXU);
    strcat(path12, s.c_str());
    // cout << s << endl;
    strcat(path12, d);
    // cout<<"path1"<<path12<<endl;
    strcat(path12, c.get_domain().c_str());
    strcat(path12, d);
    // cout<<path12<<endl;
    chdir(path12);
    memset(path12,0,sizeof(path12));
    strcat(path12, c.get_title().c_str());
    strcat(path12, e);
    // cout << path12 << endl;
    ofstream out;
    out.open(path12, ios::out|ios::binary);
    if (!out)
    {
        cout << "Can't open the file" << endl;
    }
    // out.write((char *)&c,sizeof(c));
    out<<c.get_title()<<endl;
    out<<c.get_author()<<endl;
    out<<c.get_digest()<<endl;
    out<<c.get_charset()<<endl;
    out<<c.get_release_time()<<endl;
    out<<c.get_domain()<<endl;
    out<<c.get_text()<<endl;
    out.close();
}
void setobject()
{
    Information information;
    information.set_title(find_title());
    information.set_author(gm_find_author());
    information.set_charset(gm_find_charset());
    information.set_domain_name(url_domain());
    information.set_digest(gm_find_description());
    information.set_release_time(gm_find_time());
    information.settext(denoising());
    wfile(information);
}
