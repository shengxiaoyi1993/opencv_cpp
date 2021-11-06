#include "sortimage.h"
#include <iostream>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <stdio.h>
#include "basic/getsubfile.h"


using namespace std;
using namespace cv;

 RecordBuf g_recbuf;
static bool flag_dir_start=false;
static bool flag_file_start=false;
//整理文件夹中的图片文件

int sortImageInInDir(const string & dir_input, const string & dir_output, const string &dir_ex){
        cout<<"dir_input:"<<dir_input<<endl;
    vector<string> list_file;
    vector<string> list_ex;
    vector<string> list_dir;

    //get subfile and subfile
    getFiles(dir_input,list_file,list_dir);
    //迭代法处理所有文件夹，使图片文件归类 
    for(uint i=0;i<list_dir.size();i++){
        //                cout<<i<<": "<<list_dir[i]<<endl;
        sortImageInInDir(list_dir[i],dir_output,dir_ex);
    }
    //    cout<<endl;
    //    return 0;

    if(flag_dir_start == false){
        if(dir_input == "/run/media/sxy/Extend/Data/uvss_data_before_2020/original_data/201804/09/2018-04-09-16.44.37PN._53"
                ){
            flag_dir_start=true;
        }
        else{
            return 0;
        }
    }
    for(uint i=0;i<list_file.size();i++){
        string suffixStr = list_file[i].substr(list_file[i].find_last_of('.') );
        if(suffixStr==".jpg"){
            //issmall
            if(isSmallImage(list_file[i])){
                string filename=getImageName(list_file[i]);
                //                if(filename == "2018-04-09-16.44.37PN._53"
                //                        || flag_file_start == true){
                //                    flag_file_start= true;
                //                }
                //                else{
                //                    continue;
                //                }
                Record tmprec;
                string subdir=dir_output+"/"+filename;
                mkdir(subdir);
                mvImage(list_file[i],subdir);
                tmprec.setDir(subdir);
                tmprec.setSmall(filename+".jpg");

                string suffix_sm = list_file[i].substr(list_file[i].find_last_of('_') );
                //has_sm
                if(suffix_sm == "_sm.jpg"){
                    //if big exist in list_ex or list_file
                    string path_big=getBigImagePath(list_file[i]);
                    //if in list_ex
                    bool inListEx=false;
                    for(uint j=0;j<list_ex.size();j++){
                        if(path_big == list_ex[j]){
                            list_ex.erase(list_ex.begin()+j);
                            mvImage(path_big,subdir);
                            tmprec.setBig(getImageName(path_big)+".jpg");

                            inListEx=true;
                            break;
                        }
                    }
                    //if big in list_file
                    if(!inListEx){
                        for(uint j=i+1;j<list_file.size();j++){
                            if(path_big == list_file[j]){
                                list_file.erase(list_file.begin()+j);
                                mvImage(path_big,subdir);
                                tmprec.setBig(getImageName(path_big)+".jpg");
                                break;
                            }

                        }//end of  big in list_file
                    }
                }//end of detect big
                g_recbuf.addRecord(tmprec);
                cout<<"addRecord"<<endl;
            }
            else{
                list_ex.push_back(list_file[i]);
            }//end of is small


        }//end of isimage


    }//end  of map file

    //copy ex image
    for(uint i=0;i<list_ex.size();i++){
        mvImage(list_ex[i],dir_ex);
    }



    cout<<"getRecBufSave"<<endl;
    getRecBufSave("/run/media/sxy/Extend/Data/output/record.txt");


    return 0;
}



bool isSmallImage(const string& path){
    Mat mat_tmp=imread(path,IMREAD_GRAYSCALE);
    if((mat_tmp.cols==1024&&mat_tmp.rows>1024)
            ||(mat_tmp.rows==1024&&mat_tmp.cols>1024)){
        return true;
    }
    else{
        return false;
    }

}

string getBigImagePath(const string& path){
    string bigimage=path;
    string target="_sm";
    unsigned long pos = path.find_last_of(target);
    unsigned long n = target.size();
    bigimage = bigimage.erase(pos-(n-1),n);
    return bigimage;

}

bool mvImage(const string& path_image,const string &dir_target){
    string command = "cp ";
    command  += path_image;
    command  += " ";
    command  += dir_target;
    system(command.c_str());
    return true;
}

bool mkdir(const string &dir_target){
    string command = "mkdir "+dir_target;
    system(command.c_str());
    return true;
}


string getImageName(const string &path){
    string imagename=path;
    unsigned long pos = imagename.find_last_of(".");
    imagename=imagename.erase(pos,strlen(".jpg"));
    pos = imagename.find_last_of("/");
    imagename=imagename.substr(pos+1,imagename.size()-pos-1);
    return imagename;
}


RecordBuf getRecBufSave(const string& v_path){
    RecordBuf::saveToFile(v_path,&g_recbuf);
    return g_recbuf;
}
