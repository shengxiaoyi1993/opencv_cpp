#include "getsubfile.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <algorithm>
#ifdef __linux
#include <unistd.h>
#include <dirent.h>
#endif
#ifdef WIN32
#include <direct.h>
#include <io.h>
#endif

using namespace std;


bool  getFiles(const string &cate_dir,vector<string> & list_file,vector<string> & list_dir)
{
//   vector<string> files;//存放文件名

#ifdef WIN32
   _finddata_t file;
   long lf;
   //输入文件夹路径
   if ((lf=_findfirst(cate_dir.c_str(), &file)) == -1) {
       cout<<cate_dir<<" not found!!!"<<endl;
   } else {
       while(_findnext(lf, &file) == 0) {
           //输出文件名
           //cout<<file.name<<endl;
           if (strcmp(file.name, ".") == 0 || strcmp(file.name, "..") == 0)
               continue;
           files.push_back(file.name);
       }
   }
   _findclose(lf);
#endif

#ifdef __linux
   DIR *dir;
   struct dirent *ptr;
   char base[1000];

   if ((dir=opendir(cate_dir.c_str())) == NULL)
       {
       cout<<"cate_dir:"<<cate_dir<<endl;
       perror("Open dir error...");
               exit(1);
       }

   while ((ptr=readdir(dir)) != NULL)
   {
       if(strcmp(ptr->d_name,".")==0 || strcmp(ptr->d_name,"..")==0)    ///current dir OR parrent dir
               continue;
       else if(ptr->d_type == 8)    ///file
           //printf("d_name:%s/%s\n",basePath,ptr->d_name);
           list_file.push_back(cate_dir+"/"+string(ptr->d_name));
       else if(ptr->d_type == 10)    ///link file
           //printf("d_name:%s/%s\n",basePath,ptr->d_name);
           continue;
       else if(ptr->d_type == 4)    ///dir
       {
           list_dir.push_back(cate_dir+"/"+ptr->d_name);
           /*
               memset(base,'\0',sizeof(base));
               strcpy(base,basePath);
               strcat(base,"/");
               strcat(base,ptr->d_nSame);
               readFileList(base);
           */
       }
   }
   closedir(dir);
#endif

   //排序，按从小到大排序
   sort(list_file.begin(), list_file.end());
   sort(list_dir.begin(), list_dir.end());

   return true;
}
