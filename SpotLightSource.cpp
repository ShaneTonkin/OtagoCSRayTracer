#include "SpotLightSource.h"

#include "utility.h"

SpotLightSource::SpotLightSource(const Colour& colour, const Point& location, const Direction& direction, double angle) :
	LightSource(colour), location_(location), direction_(direction), angle_(angle) {

}




SpotLightSource::SpotLightSource(const SpotLightSource& lightSource) :
LightSource(lightSource),  location_(lightSource.location_), direction_(lightSource.direction_), angle_(lightSource.angle_) {

}


SpotLightSource::~SpotLightSource() {

}

const SpotLightSource& SpotLightSource::operator=(const SpotLightSource& lightSource) {
	if (this != &lightSource) {
		LightSource::operator=(lightSource);
		location_ = lightSource.location_;
		direction_ = lightSource.direction_;
		angle_ = lightSource.angle_;
	}
	return *this;
}

Colour SpotLightSource::getIlluminationAt(const Point& point) const {
		/****************************************************************
 	 * Code to compute directional illumination at point goes here. *
	 ****************************************************************/
	//Same as pointlight but 0 for anything outside the cone
	double distance = (location_ - point).norm();
	//if (point > distance * direction_ * cos(angle_) /*the ange of the returning ray from the hit point*/){
		if (distance < epsilon) distance = epsilon;
		return (1.0 / (distance*distance)) * colour_;
	//}
}

double SpotLightSource::getDistanceToLight(const Point& point) const {
	/*******************************************************************
	* Code to compute distance to directional light source goes here. *
	*******************************************************************/
	return (location_ - point).norm();
}

Direction SpotLightSource::getLightDirection(const Point& point) const {
	Direction direction(0, 0, 0);
	/**************************************************************
	* Code to compute direction of light at the point goes here. *
	**************************************************************/
	return point - location_;
}

