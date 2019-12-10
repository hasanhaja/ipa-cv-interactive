/**
 * @author Hasan Ali
 * @opencv_version 4.1.1
 */

#include <iostream>
#include <opencv2/opencv.hpp>

void color_query_mouse_callback(int event, int x, int y, int flags, void* img);
void display(std::string window_name, cv::Mat image);

int main() {
    const std::string image_path = "../images/lena.jpg";
    const std::string window_name = "OPENCV: Color Query";
    cv::Mat img = cv::imread(image_path);

    if (!img.data) {
        std::cout << "Could not open image" << std::endl;
        return -1;
    }

    int key;
    bool keep_processing = true;

    cv::namedWindow(window_name, cv::WINDOW_AUTOSIZE);

    cv::setMouseCallback(window_name, (cv::MouseCallback) color_query_mouse_callback, &img);

    std::cout << "Image: (width x height) = (" << img.cols << " x " << img.rows << ")" << std::endl;
    std::cout << "Color channels = " << img.channels() << std::endl;

    // loop to constantly redisplay image
    while (keep_processing) {
        cv::imshow(window_name, img);

        // start event processing loop. Essential step for GUI
        key = cv::waitKey(20);  // async?

        if (key == 'x') {
            std::cout << "Keyboard exit requested.\nExiting...\nBye!" << std::endl;
            keep_processing = false;
        }
    }

    return 0;
}

void color_query_mouse_callback(int event, int x, int y, int flags, void* img) {
    using namespace cv;         // You don't have to do this, but I thought I'd try.
    using namespace std;        // You can just namespace globally, or not namespace at all.

    int row = y;
    int col = x;

    switch (event) {
        case EVENT_LBUTTONDOWN:
            cout << "Color information at image location (" << x << "," << y << "): ";
            for (int chan = 0; chan < 3; chan++) {
                auto value = (unsigned int) ((Mat *) img)->at<Vec3b>(row, col)[chan];
                cout << value << " ";
            }
            cout << endl;
            break;
        case EVENT_RBUTTONDOWN:
            cout << "Color information at image location (" << x << "," << y << ") set to White.";
            for (int chan = 0; chan < 3; chan++) {
                ((Mat *) img)->at<Vec3b>(row, col)[chan] = 255;
            }
            cout << endl;
            break;

    }

}

void display(std::string window_name, cv::Mat image) {
    cv::namedWindow(window_name, cv::WINDOW_AUTOSIZE);
    cv::imshow(window_name, image);
}
