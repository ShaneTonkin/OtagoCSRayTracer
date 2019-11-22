#pragma once

#ifndef AMBIENT_LIGHT_SOURCE_H_INCLUDED
#define AMBIENT_LIGHT_SOURCE_H_INCLUDED

#include "LightSource.h"

/**
 * \file
 * \brief AmbientLightSource class header file.
 */

/**
 * \brief Ambient light in a scene.
 *
 * An AmbientLightSource represents background illumination in a scene.
 * This is essentially a hack to avoid purely black shadows without having to 
 * model indirect lighting, which can be expensive.
 */
class AmbientLightSource : public LightSource {

public:

	/** \brief AmbientLightSource constructor.
 	 *
	 * \param colour The Colour of light emitted by the AmbientLightSource.
	 **/
	AmbientLightSource(const Colour& colour);

	/** \brief AmbientLightSource copy constructor.
	*
	* \param lightSource The AmbientLightSource to copy to \c this.
	**/
	AmbientLightSource(const AmbientLightSource& lightSource);

	/** \brief AmbientLightSource destructor */
	~AmbientLightSource();

	/** \brief AmbientLightSource assignment operator.
	*
	* \param lightSource The AmbientLightSource to copy to \c this.
	* \return A reference to \c this to allow for chaining of assignment.
	**/
	const AmbientLightSource& operator=(const AmbientLightSource& lightSource);

	/** \brief Determine how much light reaches a Point from this AmbientLightSource.
	*
	* For an AmbientLightSource this is just the Colour of the light.
	*
	* \param point The Point at which light is measured.
	* \return The illumination that reaches the Point.
	*/
	Colour getIlluminationAt(const Point& point) const;

	/** \brief Compute the distance from a Point to this LightSource
	 *
	 * To indicate an ambient light we return -1.
	 *
	 * \param point The Point from which the distance is measrued.
	 * \return The distance from the Point to the LightSource
	 */
	double getDistanceToLight(const Point& point) const;

	/** \brief Determine the direction from which light from this LightSource falls
	 *
	 * Ambient light sources don't have a direction, so return a zero vector.
	 *
	 * \param point The Point at which to measure the direction.
	 * \return The direction from which light falls on the Point.
	 */
	Direction getLightDirection(const Point& point) const;

};

#endif // AMBIENT_LIGHT_SOURCE_H_INCLUDED