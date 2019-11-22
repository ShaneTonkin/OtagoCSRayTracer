#include "ImageDisplay.h"

ImageDisplay::ImageDisplay(const std::string& windowName, unsigned int width, unsigned int height) :
image_(width, height, 1, 3, 0), display_(width, height, windowName.c_str()) {

}

ImageDisplay::~ImageDisplay() {
	if (!display_.is_closed()) {
		display_.close();
	}
}

void ImageDisplay::set(int x, int y, const Colour& colour) {
	image_(x, y, 0, 0) = int(255 * colour.red);
	image_(x, y, 0, 1) = int(255 * colour.green);
	image_(x, y, 0, 2) = int(255 * colour.blue);
}

void ImageDisplay::refresh() {
	display_.display(image_);
	display_.wait(1);
}

void ImageDisplay::save(const std::string& filename) const {
	image_.save(filename.c_str());
}

void ImageDisplay::pause(double seconds) {
	display_.wait(int(seconds*1000));
}
