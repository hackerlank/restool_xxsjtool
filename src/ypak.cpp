#include <zlib.h>
#include <sqlite3.h>
#include "util.h"
#include "ypak.h"


Ypak::Ypak(const char* path)
{
    strcpy(_path, path);

     
    cout << "SQLite3 Version: " << sqlite3_libversion() << endl;  
  
    sqlite3 *db;
    int retval = sqlite3_open(path, &db);  
    if (retval != SQLITE_OK)  
    {  
        cout << "[ERROR](open) " << sqlite3_errmsg(db) << endl;
        return;
    }  
     
    //char *sql = "select respath, hash from data;";  /* sql command */  
    //char **Result;  /* store query results in it */  
    //int row = 0;    /* row number */  
    //int col = 0;    /* column number */  
    //retval = sqlite3_get_table(db, sql, &Result, &row, &col, NULL);  
    //if (retval != SQLITE_OK)  
    //{  
    //    cout << "[ERROR](data) " << sqlite3_errmsg(db) << endl;
    //    return;
    //}  
    //  
    //cout << "row " << row << " col " << col << endl;
    //for (int i=1; i<row; i++)  
    //{  
    //    int p = i * col;
    //    cout << "path:" << *(Result + p) << " hash:" << *(Result + p + 1) << endl;
    //}  
  


    sqlite3_stmt *stat;
    const char* pzTail = NULL;
    retval = sqlite3_prepare(db, "select respath, data from data;", -1, &stat, &pzTail);
    if (retval != SQLITE_OK)  
    {  
        cout << "[ERROR](data) " << sqlite3_errmsg(db) << endl;
        return;
    }

    int i = 0;
    retval = sqlite3_step(stat);
    while(retval == SQLITE_ROW)
    {
        char* respath = (char*)sqlite3_column_text(stat, 0);
        char* resdata = (char*)sqlite3_column_blob(stat, 1);
        int ressize = sqlite3_column_bytes(stat, 1);
        unzip(resdata, ressize, respath);

        retval = sqlite3_step(stat);
    }

    sqlite3_close(db);  
}


Ypak::~Ypak()
{

}


void Ypak::info()
{

}

void Ypak::save()
{

}


void Ypak::unzip(char* buf, int bufSize, const char* resPath)
{
    
    uint32 unzipSize;
    memcpy(&unzipSize, buf, 4);

    uLongf len = unzipSize;
    Bytef* out = new Bytef[len];
    int err = uncompress(out, &len, (const Bytef*)(buf + 4), (uLongf)(bufSize - 4));
    if (err == Z_OK && len == unzipSize)
    {

        char path[255];
        strcpy(path, "out/");
        strcat(path, resPath);

        char* p = path;
        while(*p != '\0')
        {
            if(*p == '\\')
                *p = '/';
            p++;
        }
        
        Util::mkdir(path);

        ofstream fout(path, ios::out|ios::binary);
        fout.write((char *)out, len);
        fout.close();
        cout << "[SAVE]" << path << endl;
    }
    else
    {
        cout << "unzip error: " << err << " for " << resPath << endl;
    }
    delete[] out;

}




