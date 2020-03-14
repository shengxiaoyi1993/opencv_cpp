#ifndef IMAGETRANSFORMER_H
#define IMAGETRANSFORMER_H

#include <iostream>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>





typedef struct ChannelData{
    int m_length;
    int m_effectice;

private:
    char* buffer;

    ChannelData();




}ChannelData;


typedef  struct FrameData{
    int m_channels;
    int m_bit_channel;
    std::vector<ChannelData> m_list_channel;
    FrameData(int v_channels,int v_bit_channel){
        m_channels=v_channels;
        m_bit_channel=v_bit_channel;
        m_list_channel.resize(static_cast<uint>(m_channels));
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