//
// Created by Hasan on 10/12/19.
//

#ifndef IPA_CV_INTERACTIVE_COLORQUERY_H
#define IPA_CV_INTERACTIVE_COLORQUERY_H


#include <string>
#include <opencv2/opencv.hpp>
#include "Color.h"
#include "aliases.h"

class ColorQuery {
private:
    std::string image_path, window_name;
    cv::Mat image;
    int key;
    bool processing = true;
    ColorBGR color_bgr;
    cv::Size size;
    void init();

    static ColorBGR color_lookup(Color color);
    static void mouse_callback(int event, int x, int y, int flags, void* img);

public:
    ColorQuery(std::string image_path, std::string window_name, Color color, cv::Size size);
    void run();
    // void extract(); // to extract ROI based on mouse clicks

};


#endif //IPA_CV_INTERACTIVE_COLORQUERY_H
