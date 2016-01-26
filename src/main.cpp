#include <iostream>
#include <cmath>
#include "util.h"
#include "mod.h"
#include "ypak.h"

using namespace std;

#define TestClass Ypak
#define TestFiles "tmp/magic.ypak"

void work(const char *path)
{
    cout << "[Read]" << path << endl;
	TestClass tt(path);
    cout <<"[INFO]==============================="<<endl;
	tt.info();
    cout <<"[SAVE]==============================="<<endl;
	tt.save();
    cout <<"====================================="<<endl;
}

int main(int argc, char* argv[])
{
    if(argc > 1)
    {
	    for(int i = 1; i < argc; i ++)
	    	work(argv[i]);
    }
    else
    {
	    work(TestFiles);
    }

    return 0;
}


