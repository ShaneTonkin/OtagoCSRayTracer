/* $Rev: 250 $ */
#pragma once

#ifndef CUBE_H_INCLUDED
#define CUBE_H_INCLUDED

#include "Object.h"

/** 
 * \file
 * \brief Cube class header file.
 */


/**
 * \brief Class for Cube objects.
 * 
 * This class provides an Object which is a Cube at the origin with "radius" 1.
 * That is, a Cube that extends from \f$-1\f$ to \f$+1\f$ along each axis.
 * 
 */
class Cube : public Object {

public:

	/** \brief Cube default constructor.
	 * 
	 * A newly constructed Cube extending from \f$-1\f$ to \f$+1\f$ along each axis.
	 * It may be moved, rotated, and scaled through its transform member.
	 *
	 * \image html cube.png
	 * \image latex cube.eps
	 */
	Cube();

	/** \brief Cube copy constructor.      
	 * \param cube The Cube to copy.
	 */
	Cube(const Cube& cube);
	
	/** \brief Cube destructor. */
	~Cube();
	
	/** \brief Cube assignment operator.
	 *
	 * \param cube The Cube to assign to \c this.
	 * \return A reference to \c this to allow for chaining of assignment.
	 */
	const Cube& operator=(const Cube& cube);
	
	/** \brief Cube-Ray intersection computation.
	 *
	 * \todo The Cube-Ray intersection needs to be implemented as part of the assignment. 
	 *
	 * Intersection with a Cube can be seen as six instances of intersection with a Plane.
	 * However, these planes are oriented to align to different pairs of axes, and do not
	 * pass through the origin.
	 *
	 * \param ray The Ray to intersect with this Cube.
	 * \return A list (std::vector) of intersections, which may be empty.
	 */
	std::vector<RayIntersection> intersect(const Ray& ray) const;

};

#endif // CUBE_H_INCLUDED
