//
// Created by Hasan on 10/12/19.
//

#include "ColorQuery.h"

#include <utility>

ColorQuery::ColorQuery(std::string image_path, std::string window_name, Color color, cv::Size size): image_path(std::move(image_path)), window_name(std::move(window_name)), color_bgr(color_lookup(color)), size(std::move(size)) {
    init();
}

void ColorQuery::init() {
    // this could potentially throw an exception
    this->image = cv::imread(image_path);

    if (!image.data) {
        throw std::invalid_argument("Could not open image.");
    }
}

void ColorQuery::run() {
    cv::namedWindow(window_name, cv::WINDOW_AUTOSIZE);

    cv::setMouseCallback(window_name, (cv::MouseCallback) mouse_callback, this);

    std::cout << "Image: (width x height) = (" << image.cols << " x " << image.rows << ")" << std::endl;
    std::cout << "Color channels = " << image.channels() << std::endl;

    // loop to constantly redisplay image
    while (processing) {
        cv::imshow(window_name, image);

        // start event processing loop. Essential step for GUI
        key = cv::waitKey(20);  // async?

        /**
         * TODO: This could either destroy the window
         * OR
         * be able to shift focus to another window and then switch back
         */
        if (key == 'x') {
            std::cout << "Keyboard exit requested.\nExiting...\nBye!" << std::endl;
            processing = false;
        }
    }
}

/**
 * Color values obtained from [here](https://www.rapidtables.com/web/color/RGB_Color.html)
 * @param color
 * @return
 */
ColorBGR ColorQuery::color_lookup(Color color) {
    ColorBGR bgr;

    switch (color) {
        case White:
            bgr = {255, 255, 255};
            break;
        case Black:
            bgr = {0,0,0};
            break;
        case Yellow:
            bgr = {0,255,255};
            break;
        case Red:
            bgr = {0,0,255};
            break;
        case Green:
            bgr = {0,255,0};
            break;
        case Blue:
            bgr = {255,0,0};
            break;
        case LightGrey:
            bgr = {211,211,211};
            break;
        case DarkGrey:
            bgr = {169,169,169};
            break;
        case Purple:
            bgr = {128,0,128};
            break;
    }

    return bgr;
}

/**
 * This the callback function that run() will use to constantly update the image canvas.
 * @param event
 * @param x
 * @param y
 * @param flags
 * @param color_query_instance Because void * can be anything, an instance of this object can be cast to the respective components
 */
void ColorQuery::mouse_callback(int event, int x, int y, int flags, void *color_query_instance) {
    using namespace cv;         // You don't have to do this, but I thought I'd try.
    using namespace std;        // You can just namespace globally, or not namespace at all.

    int row = y;
    int col = x;

    auto color_query = (ColorQuery *) color_query_instance;
    auto bgr = color_query->color_bgr;
    auto img = color_query->image;

    switch (event) {
        case EVENT_RBUTTONDOWN:
            cout << "Color information at image location (" << x << "," << y << "): ";
            for (int chan = 0; chan < bgr.size(); chan++) {
                auto value = (unsigned int) img.at<Vec3b>(row, col)[chan];
                cout << value << " ";
            }
            cout << endl;
            break;
        case EVENT_LBUTTONDOWN:
            cout << "Color information at image location (" << x << "," << y << ") set to White.";
            for (int chan = 0; chan < bgr.size(); chan++) {
                img.at<Vec3b>(row, col)[chan] = bgr.at(chan);
            }
            cout << endl;
            break;

    }
}
