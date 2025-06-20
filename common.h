#ifndef COMMON_H                                                                                                                                                                                                                           
#define COMMON_H                                                                                                                                                                                                                           
                                                                                                                                                                                                                                           
#include <iostream>                                                                                                                                                                                                                        
#include <fstream>                                                                                                                                                                                                                         
#include <string>                                                                                                                                                                                                                          
#include <vector>                                                                                                                                                                                                                          
#include <opencv2/opencv.hpp>                                                                                                                                                                                                              
#include <sndfile.h>                                                                                                                                                                                                                       
#include <bitset>                                                                                                                                                                                                                          
#include <climits>                                                                                                                                                                                                                         
#include <filesystem> // For path manipulation (C++17 and later)                                                                                                                                                                           
#include <climits>                                                                                                                                                                                                                         
                                                                                                                                                                                                                                           
                                                                                                                                                                                                                                           
extern const std::string END_DELIMITER;                                                                                                                                                                                                    
                                                                                                                                                                                                                                           
                                                                                                                                                                                                                                           
std::string intToBinary(int num);                                                                                                                                                                                                          
int binaryToInt(const std::string& binary);                                                                                                                                                                                                
std::string charToBinary(char c);                                                                                                                                                                                                          
char binaryToChar(const std::string& binary);                                                                                                                                                                                              
//std::string getMessageFromTerminal(); 
std::string getMessageFromTerminal(void) ;                                                                                                                                                                                                     
std::string readMessageFromFile(const std::string& filePath);                                                                                                                                                                              
void saveBinaryDataAsHexTxt(const cv::Mat& image, const std::string& filename);
bool convertAndSaveToFile(const std::string& input, const std::string& filePath); 



#endif