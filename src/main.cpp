/**
 * @author Hasan Ali
 * @opencv_version 4.1.1
 */

#include <iostream>
#include <opencv2/opencv.hpp>
#include "ColorQuery.h"

int main() {
    const std::string image_path = "../images/lena.jpg";
    const std::string white_win = "OPENCV: Color Query: White";
    const std::string black_win = "OPENCV: Color Query: Black";
    const std::string yellow_win = "OPENCV: Color Query: Yello";

    ColorQuery white_query(image_path, white_win, White, cv::Size(1,1));
    white_query.run();

    ColorQuery black_query(image_path, black_win, Black, cv::Size(1,1));
    black_query.run();

    ColorQuery yellow_query(image_path, yellow_win, Yellow, cv::Size(1, 1));
    yellow_query.run();

    return 0;
}
