#ifndef RECORD_H
#define RECORD_H
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "basic/cJSON.h"


using namespace std;

inline
void saveFile(char* content,std::string file_dst) {

    FILE *fp = NULL;
    fp = fopen(file_dst.c_str(),"w");
    if(fp!=NULL){
        fprintf(fp,content);
        fclose(fp);
    }

    return ;
}

inline
int getStringFromFile(std::string dirpath,char** content){
//    cout<<__func__<<" start"<<dirpath<<endl;
    filebuf *pbuf;
    ifstream filestr;

    long size;
    // 要读入整个文件，必须采用二进制打开
    filestr.open (dirpath.c_str(), ios::binary);
    // 获取filestr对应buffer对象的指针
    pbuf=filestr.rdbuf();

    // 调用buffer对象方法获取文件大小
    size=pbuf->pubseekoff (0,ios::end,ios::in);

    pbuf->pubseekpos (0,ios::in);

    if(size<=0){

        return -1;
    }
//    cout<<size<<endl;
    // 分配内存空间

    *content=new char[size];

    // 获取文件内容
    pbuf->sgetn (*content,size);

    filestr.close();
    // 输出到标准输出

    return 0;
}

typedef struct Record{
    string dir;
    string imagename_big;
    string imagename_small;
    Record(const string v_dir,const string v_big,const string &v_small){
        dir=v_dir;
        imagename_big=v_big;
        imagename_small=v_small;
    }
    Record(){
        dir="";
        imagename_big="";
        imagename_small="";
    }
    void setDir(const string v_dir){
        dir=v_dir;
    }
    void setBig(const string v_big){
        imagename_big=v_big;
    }
    void setSmall(const string v_small){
        imagename_small=v_small;
    }
    static bool loadFromJsonObj(cJSON* v_obj,Record& v_rec){

        if(nullptr != v_obj){
            cJSON*item=cJSON_GetObjectItem(v_obj,"dir");
            if(nullptr != item){
                v_rec.dir=item->valuestring;
            }
            item=cJSON_GetObjectItem(v_obj,"imagename_big");
            if(nullptr != item){
                v_rec.imagename_big=item->valuestring;
            }
            item=cJSON_GetObjectItem(v_obj,"imagename_small");
            if(nullptr != item){
                v_rec.imagename_small=item->valuestring;
            }
            return true;

        }
        return false;
    }

    static cJSON* getJsonObj(const Record* v_rec){
        cJSON*root=cJSON_CreateObject();
        if(nullptr != root){
            cJSON_AddStringToObject(root,"dir",v_rec->dir.c_str());
            cJSON_AddStringToObject(root,"imagename_big",v_rec->imagename_big.c_str());
            cJSON_AddStringToObject(root,"imagename_small",v_rec->imagename_small.c_str());
        }
        return root;
    }
}Record;

typedef struct RecordBuf{
    vector<Record> list_Record;

    RecordBuf(vector<Record> v_list){
        list_Record.resize(v_list.size());
        for(uint i=0;i<v_list.size();i++){
            list_Record[i]=v_list[i];
        }
    }
    RecordBuf(){

    }



    bool addRecord(const Record& v_rec){
        list_Record.push_back(v_rec);
    }


    static cJSON* getJsonObj(const RecordBuf* v_buf){
        cJSON* root=cJSON_CreateObject();
        if(nullptr != root){
            cJSON*array = cJSON_CreateArray();
            cJSON*item=nullptr;
            if(nullptr != array){
                for(uint i=0;i<v_buf->list_Record.size();i++){
                    item=Record::getJsonObj(&v_buf->list_Record[i]);
                    if(nullptr != item){
                        cJSON_AddItemToArray(array,item);
                        item=nullptr;
                    }
                }//end of add to array
                cJSON_AddItemToObject(root,"list",array);
            }//end of array not null

        }//end of root notnull
        return root;
    }

    static bool loadFromJsonObj(const cJSON* v_obj,RecordBuf& v_buf){
        cJSON* array=cJSON_GetObjectItem(v_obj,"list");
        if(nullptr == array ){
            return false;
        }
        int num=cJSON_GetArraySize(array);
        cJSON*arrayitem=nullptr;
        for(int i=0;i<num;i++){
            arrayitem=cJSON_GetArrayItem(array,i);
            if(nullptr != arrayitem){
                Record tmprec;
                if(Record::loadFromJsonObj(arrayitem,tmprec)){
                    v_buf.addRecord(tmprec);
                }
            }
            arrayitem=nullptr;

        }
        return true;
    }

    static string jsonString(const RecordBuf* v_buf){
        string ret;
        cJSON*root=getJsonObj(v_buf);
        if(nullptr != root){
            char *json=cJSON_Print(root);
            if(nullptr != json){
                ret=string(json);
                free(json);
                json=nullptr;
            }
            cJSON_free(root);
            root=nullptr;
        }
        return ret;
    }

    static bool saveToFile(const string & v_path,const RecordBuf* v_buf){
        string content=jsonString(v_buf);
        saveFile(const_cast<char*>(content.c_str()),v_path);
        return true;
    }

    static bool loadFromString(const string & v_content, RecordBuf& v_buf){
        cJSON*root=cJSON_Parse(v_content.c_str());
        if(nullptr != root){
            bool flag= loadFromJsonObj(root,v_buf);
            cout<<__func__<<":"<<flag<<endl;
            cJSON_free(root);
            root=nullptr;
            return flag;
        }
        return false;
    }

    static bool loadFromFile(const string & v_path, RecordBuf& v_buf){
        char *content=nullptr;
        getStringFromFile(v_path,&content);
        if(nullptr == content){
            return false;
        }
        bool flag= loadFromString(string(content),v_buf);
        free(content);
        content=nullptr;
        return flag;
    }

}RecordBuf;


#endif // RECORD_H
