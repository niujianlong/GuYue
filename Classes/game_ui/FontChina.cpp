
#include "FontChina.h"
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
FontChina::FontChina(void)
{
}


FontChina::~FontChina(void)
{
}

const char* FontChina::G2U(const char* gb2312)    
{    
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	int len = MultiByteToWideChar(0, 0, gb2312, -1, NULL, 0);    
	wchar_t* wstr = new wchar_t[len+1];    
	memset(wstr, 0, len+1);    
	MultiByteToWideChar(0, 0, gb2312, -1, wstr, len);    
	len = WideCharToMultiByte(65001, 0, wstr, -1, NULL, 0, NULL, NULL);    
	char* str = new char[len+1];    
	memset(str, 0, len+1);    
	WideCharToMultiByte(65001, 0, wstr, -1, str, len, NULL, NULL);    
	if(wstr) delete[] wstr;    
	return str;    //这里没有对str进行内存的释放，会不会内存泄漏呢？
	#endif

	#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
	return gb2312; 
	#endif
}  

string FontChina::utf8_substr(const string& str, unsigned int start, unsigned int len)
{
	if (len == 0) return "";

	unsigned int min = string::npos, max = string::npos;
	unsigned int str_len = str.length();
	unsigned int c;
	unsigned int i, tmp;
	for (tmp = 0, i = 0; i < str_len; i++, tmp++)
	{
		if (tmp == start) min = i;
		if (tmp <= start + len || len == string::npos) max = i;

		c = (unsigned char)str[i];
		if (c >= 0 && c <= 127) i += 0;
		else if ((c & 0xE0) == 0xC0) i += 1;
		else if ((c & 0xF0) == 0xE0) i += 2;
		else if ((c & 0xF8) == 0xF0) i += 3;
		else return "";
	}
	if (tmp <= start + len || len == string::npos) max = i;
	if (min == string::npos || max == string::npos) return "";
	return str.substr(min, max);
}