#include "msg_lsbto_picture.h"                                                                                                                                                                                                                                                                                                                                                                                                                                                        
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      
const string END_DELIMITER = "$#%";                                                                                                                                                                                                                                                                                                                                                                                                                                                   
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      

bool embedMessage(Mat& image, const string& message)
{
    int index = 0;
    int messageLength = message.length();
    // // 计算图像 3 个通道总共能容纳的比特数
    // int imageSize = image.rows * image.cols * 3; 

    if (messageLength > 4095)
    {
        cerr << "Too long, can't steganography!" << endl;
        return false;
    }
    else
    {

        for (int row = 0; row < image.rows; row++)
        {
            for (int col = 0; col < image.cols; col++)
            {
                Vec3b& pixel = image.at<Vec3b>(row, col); // 获取三个通道的像素位置
                for (int channel = 0; channel < 3; channel++)
                {
                    if (index < messageLength * 8)
                    {
                        // 找到消息字节位置和比特位置
                        int bit = (message[index / 8] >> (index % 8)) & 0x01; 
                        // 清除当前通道的最低位
                        pixel[channel] &= 0xFE; 
                        // 修改当前通道的最低位
                        pixel[channel] |= bit; 
                        index++; // 索引指向下一个位置
                    }
                }
            }
        }
    }
    return true;
}

// 从隐写图像的三通道中通过 LSB 方法提取信息
std::string extractMessage(const std::string& inputFilename) 
{
    // 1. Read the image                                                                                                                                                                                                                                                                                                                                                                                                                                                              
     cv::Mat image = cv::imread(inputFilename, cv::IMREAD_COLOR);                                                                                                                                                                                                                                                                                                                                                                                                                     
    if (image.empty()) 
    {                                                                                                                                                                                                                                                                                                                                                                                                                                                              
        std::cerr << "Error: Could not open or find image: " << inputFilename << std::endl;                                                                                                                                                                                                                                                                                                                                                                                           
        return "";                                                                                                                                                                                                                                                                                                                                                                                                                                                                    
    } 
    std::string extractedMessage;
    int index = 0;
    char currentChar = 0;

    for (int row = 0; row < image.rows; row++) 
    {
        for (int col = 0; col < image.cols; col++) 
        {
            cv::Vec3b pixel = image.at<cv::Vec3b>(row, col);
            for (int channel = 0; channel < 3; channel++) 
            {
                if (index % 8 == 0 && index > 0) 
                {
                    extractedMessage.push_back(currentChar);
                    // 检查是否遇到结束序列
                    if (extractedMessage.find(END_DELIMITER) != std::string::npos) 
                    {
                        // 去除结束序列
                        extractedMessage = extractedMessage.substr(0, extractedMessage.find(END_DELIMITER));
                        return extractedMessage;
                    }
                    currentChar = 0;
                }
                currentChar |= (pixel[channel] & 0x01) << (index % 8);
                index++;
            }
        }
    }

    if (index % 8 != 0) 
    {
        extractedMessage.push_back(currentChar);
    }
    // 最后再检查一次是否遇到结束序列
    if (extractedMessage.find(END_DELIMITER) != std::string::npos) 
    {
        extractedMessage = extractedMessage.substr(0, extractedMessage.find(END_DELIMITER));
    }
    return extractedMessage;
}

// *** File Output ***                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      
bool saveMessageToFile(const std::string& filename, const std::string& message) 
{                                                                                                                                                                                                                                                                                                                                                                                                     
    std::ofstream outputFile(filename);                                                                                                                                                                                                                                                                                                                                                                                                                                               
    if (outputFile.is_open()) 
    {                                                                                                                                                                                                                                                                                                                                                                                                                                                       
        outputFile << message;                                                                                                                                                                                                                                                                                                                                                                                                                                                        
        outputFile.close();                                                                                                                                                                                                                                                                                                                                                                                                                                                           
        std::cout << "\n======>Message saved to file: " << filename << std::endl;                                                                                                                                                                                                                                                                                                                                                                                                              
        return true;                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
    } 
    else 
    {                                                                                                                                                                                                                                                                                                                                                                                                                                                                          
        std::cerr << "Error: Could not open file for writing: " << filename << std::endl;                                                                                                                                                                                                                                                                                                                                                                                             
        return false;                                                                                                                                                                                                                                                                                                                                                                                                                                                                 
    }                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 
}  


