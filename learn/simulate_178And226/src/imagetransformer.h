#ifndef IMAGETRANSFORMER_H
#define IMAGETRANSFORMER_H

#include <iostream>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>

#define VALUE_DEFAULT 1
#define FUNC_START std::cout<<__func__<<" start _____"<<std::endl;
#define FUNC_END std::cout<<__func__<<" end _____"<<std::endl;


using namespace std;
enum CMOS_MODE_TYPE{
    CMOS_MODE_TYPE_227_mode4=0
};

/**
 * @brief saveBufferToFile  将某一指针指向的buffer保存为二进制数据 "wb"
 * @param v_pdata
 * @param size
 * @param path_file
 * @return
 */
int saveBufferToFile(const uchar* v_pdata,uint size,std::string path_file);

/**
 * @brief generateInsertList 产生满足某一范围的随机数
 * @param v_list
 * @param v_min
 * @param v_max
 */
void generateInsertList(std::vector<int> &v_list, int v_min, int v_max);

inline int modWithCeil(int v_dividend,int v_divisor){
    int value=v_dividend/v_divisor;
    if(v_dividend%v_divisor!=0){
        value++;
    }
    return value;
}

inline void writeHalfByte(void *pdata,uchar v_data){

    memcpy(pdata,&v_data,1);
}

//void writeUnit(unsigned int v_value,uint v_size_unit ,uint v_pos){
//    //从起始位置起读2个字符 16位
////? 是否能不以字节为单位进行读写
//    short value=static_cast<short>(v_value<<(16-v_size_unit));
//    memcpy(pbuffer+v_pos*v_size_unit,&value,2);
//}

typedef struct ChannelData{

    //标记有效数据的起始与终止位数
    int m_eff_start;
    int m_eff_end;
    int m_pos_record_pix;
    int m_length_byte;

    int m_length;
    void* pbuffer;

public:
    ChannelData( int v_length,int v_eff_start,int v_eff_end){
        FUNC_START
                std::cout<<"ggg"<<std::endl;

        pbuffer=nullptr;
        m_length=v_length;
        m_length_byte=modWithCeil(v_length,8);
        pbuffer=malloc(static_cast<uint>(m_length_byte));
        if(pbuffer != nullptr){
            memset(pbuffer,VALUE_DEFAULT,static_cast<uint>(m_length_byte));
        }
        else{
            std::cout<<">>Error: Fail to malloc"<<std::endl;
        }
        m_eff_start=v_eff_start;
        m_eff_end=v_eff_end;
        m_pos_record_pix=0;
        FUNC_END

    }

    ChannelData( int v_length){
        pbuffer=nullptr;
        m_length=v_length;
        m_length_byte=modWithCeil(v_length,8);

        cout<<"modWithCeil(v_length,8):"<<modWithCeil(v_length,8)<<endl;
        pbuffer=malloc(static_cast<uint>(m_length_byte));
        m_pos_record_pix=0;
    }


    int copyFromChannelData(const ChannelData& v_obj,uint v_bit_move){
        cout<<"v_bit_move: "<<v_bit_move<<endl;
        cout<<"v_obj.m_length: "<<v_obj.m_length<<endl;
        cout<<"m_length: "<<m_length<<endl;
        cout<<"modWithCeil(v_obj.m_length,8):"<<modWithCeil(v_obj.m_length,8)<<endl;

        memcpy(pbuffer+v_bit_move,v_obj.pbuffer,modWithCeil(v_obj.m_length,8));
    }

    /**
     * @brief writeUnit  在该通道中写入某个数据单元
     * 1. 通道中的数据从高位优先
     * @param v_value
     * @param v_size_unit
     * @param v_pos
     */
    void writeUnit(unsigned int v_value,uint v_size_unit ,uint v_pos){
        //从起始位置起读2个字符 16位
        //? 是否能不以字节为单位进行读写
        unsigned short value=static_cast<unsigned short>(v_value<<(16-v_size_unit));
        cout<<"m_length:"<<m_length<<endl;
        cout<<"v_pos:"<<v_pos<<endl;

        memcpy(pbuffer+v_pos,&value,2);
    }

    void writeSAV_start(unsigned int v_sav0,
                        unsigned int v_sav1,
                        unsigned int v_sav2,
                        unsigned int v_sav3,
                        uint v_size_unit
                        ){
        writeUnit(v_sav0,v_size_unit,0);
        writeUnit(v_sav1,v_size_unit,1*v_size_unit);
        writeUnit(v_sav2,v_size_unit,2*v_size_unit);
        writeUnit(v_sav3,v_size_unit,3*v_size_unit);
    }

    void writeSAV_end(unsigned int v_sav0,
                      unsigned int v_sav1,
                      unsigned int v_sav2,
                      unsigned int v_sav3,
                      uint v_size_unit,
                      uint v_pos
                      ){
        FUNC_START

        //        cout<<"m_length: "<<m_length<<endl;
        //        cout<<"(3+v_pos)*v_size_unit: "<<(3+v_pos)*v_size_unit<<endl;

        writeUnit(v_sav0,v_size_unit,(0+v_pos)*v_size_unit);
        writeUnit(v_sav1,v_size_unit,(1+v_pos)*v_size_unit);
        writeUnit(v_sav2,v_size_unit,(2+v_pos)*v_size_unit);
        writeUnit(v_sav3,v_size_unit,(3+v_pos)*v_size_unit);
        FUNC_END

    }


    void writePix(unsigned int v_value,uint v_size_unit ,uint v_pos){
        m_pos_record_pix++;
        writeUnit(v_value,v_size_unit,v_pos*v_size_unit);
    }

    /**
     * @brief readBuffer 保存在字符类型的高4位
     * @param v_pos
     * @return
     */
    uchar readBufferAsHalfByte(uint v_pos){
        uchar bufer_tmp;
        memcpy(&bufer_tmp,pbuffer+v_pos,1);
        return bufer_tmp;
    }



}ChannelData;







typedef  struct FrameData{
    int m_channels;
    int m_bit_channel;
    std::vector<ChannelData> m_list_channel;
    std::vector<ChannelData> m_list_channel_move;
    int m_range_min_HBLK;
    int m_range_max_HBLK;

    std::vector<int> m_list_eff_start;
    std::vector<int> m_list_eff_end;
    int m_length_channel;
    int m_length_channel_move;
    int m_cols_pix;
    /**
     * @brief m_offset 标识第一个像素点落在的行序号
     */
    int m_offset;


    unsigned m_SAV_start[4];
    unsigned m_SAV_end[4];



public:
    /**
     * @brief FrameData   标识图片中一行的存储格式
     * @param v_channels
     * @param v_bit_channel
     */
    FrameData(int v_channels,int v_bit_channel){
        FUNC_START
                m_channels=v_channels;
        m_bit_channel=v_bit_channel;

        //? 226
        m_range_min_HBLK=1;
        m_range_max_HBLK=64;
        m_length_channel=433;
        m_length_channel_move=m_range_max_HBLK+2+m_length_channel;
        m_cols_pix=4096;
        m_offset=3;


        //? 226
        m_list_eff_start.clear();
        m_list_eff_end.clear();

        int array_tmp_start[10]={18,18,18,18,17,17,17,17,17,17};
        int array_tmp_end[10]={429,429,429,429,429,429,429,429,429,429};
        for(uint c_i=0;c_i<10;c_i++){
            m_list_eff_start.push_back(array_tmp_start[c_i]*m_bit_channel);
            m_list_eff_end.push_back(array_tmp_end[c_i]*m_bit_channel);
        }

        m_SAV_start[0]=0x3FF;
        m_SAV_start[1]=0x000;
        m_SAV_start[2]=0x000;
        m_SAV_start[3]=0x2AC;

        m_SAV_end[0]=0x3FF;
        m_SAV_end[1]=0x000;
        m_SAV_end[2]=0x000;
        m_SAV_end[3]=0x2D8;


        //初始化列表
        for(uint c_i=0;c_i<static_cast<uint>(m_channels);c_i++){
            std::cout<<"ggg"<<std::endl;

            m_list_channel.push_back(ChannelData(m_length_channel*m_bit_channel,
                                                 m_list_eff_start[c_i],
                                                 m_list_eff_end[c_i]));
            cout<<"m_length_channel*m_bit_channel:"<<m_length_channel*m_bit_channel<<endl;

            cout<<"m_length_channel_move*m_bit_channel:"<<m_length_channel_move*m_bit_channel<<endl;

            m_list_channel_move.push_back(ChannelData(m_length_channel_move*m_bit_channel));

        }
        FUNC_END




    }

    /**
     * @brief loadData 导入数据，生成每个通道内的数据和通道内进行的数据
     * @param v_pdata
     */
    int loadData(const uchar* v_pdata,int v_length){
        FUNC_START
                //write sav_start
                for(uint i=0;i<m_list_channel.size();i++){
            m_list_channel[i].writeSAV_start(m_SAV_start[0],
                    m_SAV_start[1],
                    m_SAV_start[2],
                    m_SAV_start[3],
                    static_cast<uint>(m_bit_channel)
                    );
        }

        //write pix
        cout<<"write pix"<<endl;
        int value_available=v_length<m_cols_pix?v_length:m_cols_pix;
        cout<<"value_available:"<<value_available<<endl;

        for(int i=0;i<value_available;i++){
            cout<<"i: "<<i<<endl;
            uint seq_col=(m_offset+i)%10;
            m_list_channel[seq_col].writePix(
                        static_cast<unsigned>(v_pdata[static_cast<uint>(i)]),
                    static_cast<uint>(m_bit_channel),
                    static_cast<uint>( m_list_channel[seq_col].m_pos_record_pix
                                       +m_list_eff_start[seq_col])
                    );
        }


        //write sav_end
        for(uint i=0;i<m_list_channel.size();i++){
            cout<<"i: "<<i<<endl;
            m_list_channel[i].writeSAV_end(m_SAV_end[0],
                    m_SAV_end[1],
                    m_SAV_end[2],
                    m_SAV_end[3],
                    static_cast<uint>(m_bit_channel),
                    static_cast<uint>(m_list_eff_end[i]+1)
                    );


        }

        std::cout<<"value_available"<<std::endl;

        //! 计算每个通道前后插入的数据,列表中标识的是每个通道前后插入的位
        std::vector<int> list_start;
        std::vector<int> list_end;
        list_start.resize(static_cast<uint>(m_channels));
        list_end.resize(static_cast<uint>(m_channels));

        generateInsertList(list_start,
                           m_range_min_HBLK,
                           m_range_max_HBLK);



        for(uint c_i=0;c_i<list_end.size();c_i++){
            list_end[c_i]=m_range_max_HBLK-list_start[c_i];
        }

        for(uint i=0;i<m_list_channel_move.size();i++){
//            cout<<"list_start[i]:"<<list_start[i]<<endl;
            m_list_channel_move[i].copyFromChannelData(m_list_channel[i],
                                                       static_cast<uint>(list_start[i]*m_bit_channel));
        }

        return 0;

        FUNC_END




    }

    static void* getSaveBuffer(std::vector<ChannelData> list, int & size,int v_size_output){
        void* pbuffer=nullptr;

        //申请内存，多申请一个字节，方便写入
        uint size_total=0;
        for(uint i=0;i<list.size();i++){
            size_total+=static_cast<uint>( list[i].m_length);
        }
        pbuffer=static_cast<uchar*>(malloc(static_cast<uint>(modWithCeil(static_cast<int>(size_total),8)+1)));
        if(pbuffer == nullptr){
            std::cout<<">>Error: Fail to malloc"<<std::endl;
            return pbuffer;
        }
        uint pos=0;

        for(uint i=0;i<list.size();i++){
            uchar data_tmp=list[i].readBufferAsHalfByte(pos*4);
            writeHalfByte(pbuffer+pos*4,data_tmp);
            pos++;
        }

        size=static_cast<int>(size_total);

        return pbuffer;
    }


    /**
     * @brief transformToFrameData  从输入数据转换成保存的数据
     * @param v_channels
     * @param v_bit_channel
     * @param v_bit_outbut
     * @param v_pdata
     * @return  输出的指针不为空则需要释放
     */
    static void* transformToFrameData(int v_channels,
                                      int v_bit_channel,
                                      int v_bit_outbut,
                                      int v_length,
                                      const uchar *v_pdata,
                                      int & o_size
                                      ){


        FrameData framedata_tmp(v_channels,v_bit_channel);


        int flag_tmp = framedata_tmp.loadData(v_pdata,v_length);

        if(flag_tmp != 0){
            std::cout<<">>Error:Fail to load data"<<std::endl;
        }


        //?
        return getSaveBuffer(framedata_tmp.m_list_channel_move,o_size,v_bit_outbut);

    }



}FrameData;


class ImageTransformer
{

private:
    int m_channels;
    int m_bit_channel;
    int m_bit_delivery;

public:


public:
    explicit ImageTransformer(int v_channels,
                              int v_bit_channel,
                              int v_bit_delivery);
    /**
     * @brief transform  转换mat_src，并输出为path_output文件
     * @param mat_src
     * @param path_output
     */
    int transform(const cv::Mat & mat_src,
                  const std::string & path_output);

private:


};




#endif // IMAGETRANSFORMER_H
