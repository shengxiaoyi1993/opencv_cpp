#ifndef GETSUBFILE_H
#define GETSUBFILE_H

#include<iostream>
#include<string>
#include <vector>
using namespace std;


/**
 * get subfile and subdir of certain dir
 * @param  cate_dir  [description]
 * @param  list_file [description]
 * @param  list_dir  [description]
 * @return           [description]
 */
bool  getFiles(const string &cate_dir,vector<string> & list_file,vector<string> & list_dir);


#endif // GETSUBFILE_H
