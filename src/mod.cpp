#include <zlib.h>
#include "util.h"
#include "mod.h"


Mod::Mod(const char* path)
{
	strcpy(_path, path);
	_file.open(_path, ios::in|ios::binary);
    cout << "read at " << hex << showbase << _file.tellg() << dec << showbase << endl;


    uint32 unzipSize;
	_file.read((char *)&unzipSize, 4);


    int m1 = (int)_file.tellg();
    _file.seekg(0, ios::end);
    int m2 = (int)_file.tellg();
    _file.seekg(m1, ios::beg);

    uint32 zipSize = (uint32)(m2 - m1);

    unzip(zipSize, unzipSize, ".raw"); 
}


Mod::~Mod()
{
	_file.close();
}


void Mod::info()
{

}

void Mod::save()
{

}



void Mod::unzip(int zipSize, int unzipSize, const char* name)
{
    Bytef* buf = new Bytef[zipSize];
    _file.read((char *)buf, zipSize);
    
    uLongf len = unzipSize;
    Bytef* out = new Bytef[len];
    int err = uncompress(out, &len, buf, zipSize);
    if (err == Z_OK && len == unzipSize)
    {

        char path[255];
        strcpy(path, "out/");
        strcat(path, _path);
        strcat(path, name);

        Util::mkdir(path);

        ofstream fout(path, ios::out|ios::binary);
        fout.write((char *)out, len);
        fout.close();
    }
    else
    {
        cout << "unzip error: " << err << " for " << name << endl;
    }
    delete[] out;
    delete[] buf;
}




