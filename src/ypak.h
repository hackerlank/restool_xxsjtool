#ifndef __YPAK_H__
#define __YPAK_H__

#include "define.h"

class Ypak
{
public:
	Ypak(const char* path);
	~Ypak();

	void info();
	void save();

    void unzip(char* buf, int bufSize, const char* resPath);
public:
	char 	 _path[255];
};



#endif

