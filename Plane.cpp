#include "Plane.h"

#include "utility.h"

Plane::Plane() : Object() {

}

Plane::Plane(const Plane& plane) : Object(plane) {

}

Plane::~Plane() {

}

const Plane& Plane::operator=(const Plane& plane) {
	if (this != &plane) {
		Object::operator=(plane);
	}
	return *this;
}

std::vector<RayIntersection> Plane::intersect(const Ray& ray) const {

	std::vector<RayIntersection> result;
	//Transform the ray
	Ray inverseRay = transform.applyInverse(ray);
	//Solve for hit point
	const Point& p = inverseRay.point;
	const Direction& d = inverseRay.direction;
	double z0 = inverseRay.point(2); 
	double dz = inverseRay.direction(2); 
	double t = -z0/dz;
	//Check if dz is not 0 or close to 0
	if(std::abs(dz) > epsilon){
		if(t>0){		
			RayIntersection hit;
			hit.point = p + t*d;
			double x = hit.point(0);
			double y = hit.point(1);
			//Check to see if the hit point's x and y values are in the range [-1,1]
			if(std::abs (x) <= 1 && std::abs(y) <= 1){
				//Assign the hit point the goods
				hit.material = material;
				hit.point = transform.apply(hit.point);
				hit.normal = transform.apply(Normal(0,0,1));
				if (hit.normal.dot(ray.direction) > 0) {
					hit.normal = -hit.normal;
				}
				hit.distance = (hit.point - ray.point).norm();
				result.push_back(hit);	
			}
		}
	}	
	return result;
}