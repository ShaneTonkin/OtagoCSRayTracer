
#pragma once

#ifndef DIRECTIONAL_LIGHT_SOURCE_H_INCLUDED
#define DIRECTIONAL_LIGHT_SOURCE_H_INCLUDED

#include "LightSource.h"

/**
 * \file
 * \brief DirectionalLightSource class header file.
 */

/**
 * \brief Light emitted from afar in a particular Direction.
 *
 * A DirectionaLightSource represents parallel light rays from a given Direction.
 * This is often used to represent a 'Sun' light source - a strong light source
 * at a very large (practically infinite) distance.
 */
class DirectionalLightSource : public LightSource {

public:

	/** \brief DirectionalLightSource constructor.
	 *
	 * This creates a LightSource with a specified Colour coming from a particular Direction
	 *
	 * \param colour The Colour of the DirectionalLightSource
	 * \param direction The Direction of the DirectionalLightSource
	 **/
	DirectionalLightSource(const Colour& colour, const Direction& direction);

	/** \brief DirectionalLightSource copy constructor.
	*
	* \param lightSource The DirectionalLightSource to copy to \c this.
	**/
	DirectionalLightSource(const DirectionalLightSource& lightSource);

	/** \brief DirectionalLightSource destructor */
	~DirectionalLightSource();

	/** \brief DirectionalLightSource assignment operator.
	*
	* \param lightSource The DirectionalLightSource to copy to \c this.
	* \return A reference to \c this to allow for chaining of assignment.
	**/
	const DirectionalLightSource& operator=(const DirectionalLightSource& lightSource);

  /** \brief Determine how much light reaches a Point from this DirectionalLightSource.
	*
	* \todo The DirectionalLightSource intensity method needs to be implemented as part of the assignment.
	*
	* The illumination from a DirectionalLightSource doesn't decay with distance.
	*
	* \param point The Point at which light is measured.
	* \return The illumination that reaches the Point from this DirectionalLightSource.
	*/
	Colour getIlluminationAt(const Point& point) const;

	/** \brief Compute the distance from a Point to this LightSource
	 *
	 * \todo This method needs to be implemented as part of the assignment.
	 *
	 * \param point The Point from which the distance is measrued.
	 * \return The distance from the Point to the LightSource
	 */
	double getDistanceToLight(const Point& point) const;

	/** \brief Determine the direction from which light from this LightSource falls
	 *
	 * \todo This method needs to be implemented as part of the assignment.
	 *
	 * \param point The Point at which to measure the direction.
	 * \return The direction from which light falls on the Point.
	 */
	Direction getLightDirection(const Point& point) const;


private:

	Direction direction_; //!< The Direction that this light source sheds light in.

};
#endif