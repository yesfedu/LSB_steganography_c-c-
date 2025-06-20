#ifndef AUDIO_LSBTO_PICTUTRE_H                                                                                                                                                              
#define AUDIO_LSBTO_PICTUTRE_H                                                                                                                                                              
#include "common.h"                                                                                                                                                                         
                                                                                                                                                                                            
                                                                                                                                                                                            
                                                                                                                                                                                            
// 读取音频文件并返回二进制数据                                                                                                                                                             
std::string readAudioFile(const std::string& audioPath, SF_INFO& sfinfo);                                                                                                                   
// LSB 隐写术：将音频二进制数据嵌入到图片中                                                                                                                                                 
cv::Mat lsbSteganography(const cv::Mat& image, const std::string& audioBinary);                                                                                                             
// 从隐写图片中提取音频二进制数据                                                                                                                                                           
std::string extractAudioBinary(const cv::Mat& stegoImage, int audioLength);                                                                                                                 
// 将二进制数据保存为音频文件                                                                                                                                                               
bool saveAudioFile(const std::string& audioBinary, const std::string& outputPath, SF_INFO sfinfo);                                                                                          
                                                                                                                                                                                            
                                                                                                                                                                                            
                                                                                                                                                                                            
                                                                                                                                                                                            
#endif 