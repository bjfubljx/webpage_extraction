#include "BloomFilter.h"


int array[] = {5, 7, 11, 13, 31, 37, 61};
uint BloomFilter::RSHash(const char *str, int seed)    
{    
    //unsigned int b = 378551;    
    uint a = 63689;
    uint hash = 0;    
     
    while (*str)    
    {    
        hash = hash * a + (*str++);    
        a *= seed;    
    }    
     
    return (hash & 0x7FFFFFFF);    
}    
 
void BloomFilter::SetKey(const char* str)
{
	int *p = new int[m_k+1];
	memset(p, 0, sizeof(p)/sizeof(int));
	for(int i=0;i<m_k;++i)
	{
		p[i] = static_cast<int>(RSHash(str, array[i]))%1000000;
	}
 
	for(int j=0;j<m_k; ++j)
	{
		bit[p[j]] = 1;
	}
	delete[] p;
}
 
int BloomFilter::VaryExist(const char* str)
{
	int res = 1;
	int *p = new int[m_k+1];
	memset(p, 0, sizeof(p)/sizeof(int));
	for(int i=0;i<m_k;++i)
	{
		p[i] = static_cast<int>(RSHash(str, array[i]))%1000000;
	}
 
	for(int j=0;j<m_k;++j)
	{
		res &= bit[p[j]];
		if(!res)
		{
			delete[] p;
			return 0;
		}			
	}
	delete[] p;
	return 1;
}

/*string random(string a, int type)
{
	int i;
	string b;
	switch(type)
	{
		case 1:
			for(i=0;i<5;i++)
			{
				b='A'+rand()%26;
				a=a+b;
			}
			break;
		case 2:
			for(i=0;i<100;i++)
			{
				b='a'+rand()%26;
				a=a+b;
			}
			break;
		case 3:
			for(i=0;i<8;i++)
			{
				b='0'+rand()%10;
				a=a+b;
			}
			break;
	}
	return a;
}
int main(int argc, char *argv[])
{
	BloomFilter bf(2000, 100);
    string str = "https://blog.csdn.net/alps1992/article/details/44610587";
	string str2 = "sdfasfa";
	string str3 = "http://pages.cs.wisc.edu/~cao/papers/summary-cache/node8.html";
	string p[100];
	string a[100];
	int i;
	 for(i=0;i<100;i++) 
         {
			     	
             string b;
	         b=random(b,1);
		    ///int flag;
            //flag=cha(b,a);
            //if(flag==0)
	        a[i]=b;
	        p[i]=a[i];					         
	        bf.SetKey(p[i].c_str());
	 }
	//bf.SetKey(str.c_str());
	//bf.SetKey(str3.c_str());
	int res = bf.VaryExist(str.c_str());
 
	if(res)
		cout << "exist" << endl;
	else
		cout << "not exist" << endl;
 
	//bf.SetKey(str2.c_str());
	res = bf.VaryExist(str2.c_str());
	if(res)
		cout << "exist" << endl;
	else
		cout << "not exist" << endl;

	res = bf.VaryExist(p[50].c_str());
	if(res)
		cout << "exist" << endl;
	else
		cout << "not exist" << endl;
	
    return 0;
}*/