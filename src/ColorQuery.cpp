//
// Created by Hasan on 10/12/19.
//

#include "ColorQuery.h"

ColorQuery::ColorQuery(std::string image_path, std::string window_name, Color color, cv::Size size): image_path(image_path), window_name(window_name), color_values(color_lookup(color)), size(size) {}

void ColorQuery::init() {
    // this could potentially throw an exception
    this->image = cv::imread(image_path);

    if (!image.data) {
        throw std::invalid_argument("Could not open image.");
    }
}

void ColorQuery::run() {
    cv::namedWindow(window_name, cv::WINDOW_AUTOSIZE);

    cv::setMouseCallback(window_name, (cv::MouseCallback) mouse_callback, &image);

    std::cout << "Image: (width x height) = (" << image.cols << " x " << image.rows << ")" << std::endl;
    std::cout << "Color channels = " << image.channels() << std::endl;

    // loop to constantly redisplay image
    while (processing) {
        cv::imshow(window_name, image);

        // start event processing loop. Essential step for GUI
        key = cv::waitKey(20);  // async?

        if (key == 'x') {
            std::cout << "Keyboard exit requested.\nExiting...\nBye!" << std::endl;
            processing = false;
        }
    }
}

std::tuple<int, int, int> ColorQuery::color_lookup(Color color) {

    using namespace std;

    tuple<int, int, int> value;

    switch (color) {
        case White:
            value = make_tuple(255, 255, 255);
            break;
        case Black:
            value = make_tuple(0, 0, 0);
            break;
        // etc etc
    }

    return value;
}

void ColorQuery::mouse_callback(int event, int x, int y, int flags, void *img) {
    using namespace cv;         // You don't have to do this, but I thought I'd try.
    using namespace std;        // You can just namespace globally, or not namespace at all.

    int row = y;
    int col = x;

    switch (event) {
        case EVENT_RBUTTONDOWN:
            cout << "Color information at image location (" << x << "," << y << "): ";
            for (int chan = 0; chan < 3; chan++) {
                auto value = (unsigned int) ((Mat *) img)->at<Vec3b>(row, col)[chan];
                cout << value << " ";
            }
            cout << endl;
            break;
        case EVENT_LBUTTONDOWN:
            cout << "Color information at image location (" << x << "," << y << ") set to White.";
            for (int chan = 0; chan < 3; chan++) {
                ((Mat *) img)->at<Vec3b>(row, col)[chan] = 255;
            }
            cout << endl;
            break;

    }
}
