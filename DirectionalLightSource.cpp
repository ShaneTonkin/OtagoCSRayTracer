#include "DirectionalLightSource.h"
#include "utility.h"

DirectionalLightSource::DirectionalLightSource(const Colour& colour, const Direction& direction) :
	LightSource(colour), direction_(direction) {

}

DirectionalLightSource::DirectionalLightSource(const DirectionalLightSource& lightSource) :
	LightSource(lightSource), direction_(lightSource.direction_) {

}

DirectionalLightSource::~DirectionalLightSource() {

}

const DirectionalLightSource& DirectionalLightSource::operator=(const DirectionalLightSource& lightSource) {
	if (this != &lightSource) {
		LightSource::operator=(lightSource);
		direction_ = lightSource.direction_;
	}
	return *this;
}


Colour DirectionalLightSource::getIlluminationAt(const Point& point) const {
	Colour colour;
	/****************************************************************
	* Code to compute directional illumination at point goes here. *
	****************************************************************/
	return colour;
}

double DirectionalLightSource::getDistanceToLight(const Point& point) const {
	double distance = 0;
	/*******************************************************************
	 * Code to compute distance to directional light source goes here. *
	 *******************************************************************/
	return distance;
}

Direction DirectionalLightSource::getLightDirection(const Point& point) const {
	Direction direction(0, 0, 0);
	/**************************************************************
	 * Code to compute direction of light at the point goes here. *
	 **************************************************************/

	return direction;
}
