#ifndef __MOD_H__
#define __MOD_H__

#include "define.h"

class Mod
{
public:
	Mod(const char* path);
	~Mod();

	void info();
	void save();

    void unzip(int zipSize, int unzipSize, const char* name);
public:
	char 	 _path[255];
	ifstream _file;
};



#endif

