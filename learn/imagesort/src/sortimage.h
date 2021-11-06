#ifndef SORTIMAGE_H
#define SORTIMAGE_H

#include <iostream>
#include <string>
#include <vector>
#include "basic/cJSON.h"
#include "basic/basic.h"
#include "record.h"

using namespace std;

extern RecordBuf g_recbuf;

/**
 * @brief sortImageInInDir sort image
 * @param dir_input
 * @param dir_output
 * @return
 */
int sortImageInInDir(const string & dir_input,const string & dir_output,const string & dir_ex);



bool isSmallImage(const string& path);

string getBigImagePath(const string& path);

bool mvImage(const string& path_image,const string &dir_target);

bool mkdir(const string &dir_target);

string getImageName(const string &path);



RecordBuf getRecBufSave(const string& v_path);

#endif // SORTIMAGE_H
