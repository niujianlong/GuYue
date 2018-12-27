#ifndef __FONT_CHINA__
#define __FONT_CHINA__
#include <string>
using namespace std;

class FontChina
{
public:
	FontChina(void);
	~FontChina(void);
	static const char* G2U(const char* gb2312);
	static string utf8_substr(const string& str, unsigned int start, unsigned int len);
};


#endif //__FONT_CHINA__
