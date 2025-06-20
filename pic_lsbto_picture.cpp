#include "pic_lsbto_picture.h"                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
// Function to embed the secret image into the carrier image using LSB
bool embedImage(const cv::Mat& carrier, const cv::Mat& secret, cv::Mat& stegoImage) 
{
    // Check if images are valid
    if (carrier.empty() || secret.empty()) 
    {
        std::cerr << "Error: Carrier or secret image is empty." << std::endl;
        return false;
    }

    // Check if images have the same dimensions
    if (carrier.size() != secret.size()) 
    {
        std::cerr << "Error: Carrier and secret images must have the same dimensions." << std::endl;
        return false;
    }

    // Check if carrier image has 3 channels
    if (carrier.channels() != 3) 
    {
        std::cerr << "Error: Carrier image must have 3 channels (color image)." << std::endl;
        return false;
    }

    // Convert secret image to grayscale if it is not already
    cv::Mat graySecret;
    if (secret.channels() == 3) 
    {
        cv::cvtColor(secret, graySecret, cv::COLOR_BGR2GRAY);
    } 
    else 
    {
        graySecret = secret.clone(); // If already grayscale, clone it
    }

    // Create stego image (copy of carrier)
    stegoImage = carrier.clone();

    // Embed the secret image into the carrier image
    for (int y = 0; y < carrier.rows; y++) 
    {
        for (int x = 0; x < carrier.cols; x++) 
        {
            for (int c = 0; c < 3; c++) 
            {
                // Get the carrier pixel value
                unsigned char carrierPixel = carrier.at<cv::Vec3b>(y, x)[c];

                // Get the secret pixel value
                unsigned char secretPixel = graySecret.at<uchar>(y, x);

                //黑白判断，secret图片 > 128 就是白色
                uchar secretBit = (secretPixel > 128) ? 1 : 0;

                // Embed the LSB of the secret pixel into the LSB of the carrier pixel
                stegoImage.at<cv::Vec3b>(y, x)[c] = (carrierPixel & 0xFE) | secretBit;
            }
        }
    }

    std::cout << "Image embedded successfully." << std::endl;
    return true;
}

// Function to extract the secret image from the stego image
cv::Mat extractImage(const cv::Mat& stegoImage) 
{
    // Check if stego image is valid
    if (stegoImage.empty()) {
        std::cerr << "Error: Stego image is empty." << std::endl;
        return cv::Mat();
    }

    // Create an image to store the extracted secret image
    cv::Mat extractedImage(stegoImage.size(), CV_8UC1);

    // Extract the LSB from each pixel of the stego image
    for (int y = 0; y < stegoImage.rows; y++) 
    {
        for (int x = 0; x < stegoImage.cols; x++) 
        {
            uchar secretValue = 0;
            for (int c = 0; c < 3; c++) 
            {
                secretValue |= ((stegoImage.at<cv::Vec3b>(y, x)[c] & 0x01) << c);
            }

            //二值化
            extractedImage.at<uchar>(y, x) = (secretValue > 0) ? 255 : 0;
        }
    }

    // Enhance contrast (linear scaling)
    double minVal, maxVal;
    cv::minMaxLoc(extractedImage, &minVal, &maxVal);

    cv::Mat contrastEnhanced;
    extractedImage.convertTo(contrastEnhanced, CV_8U, 255.0 / (maxVal - minVal), -minVal * 255.0 / (maxVal - minVal));

       //高斯模糊后处理
        cv::Mat gaussianBlurred;
        GaussianBlur(contrastEnhanced, gaussianBlurred, cv::Size(5, 5), 1.5);

    return gaussianBlurred;
}

// Function to save an image
bool saveImage(const cv::Mat& image, const std::string& filename) 
{
    if (image.empty()) 
    {
        std::cerr << "Error: Image to save is empty." << std::endl;
        return false;
    }

    if (cv::imwrite(filename, image)) 
    {
        std::cout << "Image saved successfully to " << filename << std::endl;
        return true;
    } 
    else 
    {
        std::cerr << "Error: Could not save image to " << filename << std::endl;
        return false;
    }
}

// Function to load an image
cv::Mat loadImage(const std::string& filename) 
{
    cv::Mat image = cv::imread(filename, cv::IMREAD_COLOR);

    if (image.empty()) 
    {
        std::cerr << "Error: Could not load image " << filename << std::endl;
    } 
    else 
    {
        std::cout << "Image loaded successfully from " << filename << std::endl;
    }

    return image;
}
