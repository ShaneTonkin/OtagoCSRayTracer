#include "Cylinder.h"

#include "utility.h"

Cylinder::Cylinder() : Object(){
}

Cylinder::Cylinder(const Cylinder &cylinder) : Object(cylinder){
}

Cylinder::~Cylinder(){
}

const Cylinder &Cylinder::operator=(const Cylinder &cylinder){
	if (this != &cylinder){
		Object::operator=(cylinder);
	}
	return *this;
}

std::vector<RayIntersection> Cylinder::intersect(const Ray &ray) const{

	std::vector<RayIntersection> result;
	Ray inverseRay = transform.applyInverse(ray);
	Point p = inverseRay.point;
	Direction d = inverseRay.direction;
	//Solve for hit point
	double x0 = inverseRay.point(0);
	double y0 = inverseRay.point(1);
	double z0 = inverseRay.point(2);
	double dx = inverseRay.direction(0);
	double dy = inverseRay.direction(1);
	double dz = inverseRay.direction(2);
	double a = d(0)*d(0) + d(1)*d(1);
	double b = 2 * p(0)*d(0) + 2*p(1)*d(1);
	double c = p(0)*p(0) + p(1)* p(1)- 1;
	double b2_4ac = b * b - 4 * a * c;
	double z = z0;
	double sqb24ac = sqrt(b2_4ac);
	double t = 0;
	double t0 = (-b + sqb24ac)/(2*a);
	double t1 = (-b - sqb24ac)/(2*a);
	if(t0 > t1){
		double temp = t0;
		t0 = t1;
		t1 = temp;
	}
	double z0t0 = z0 + t0 * dz;
	double z0t1 = z0 + t1 * dz;
	//Check for caps of cylinder hit
	//Check if dz is not 0 or close to 0
	if (z0t0 < -1){
		t = t0 + (t1 - t0) * (z0t0+1)/(z0t0-z0t1);
		//Top Circular Cap
		if (t > 0){
			RayIntersection hit;
			hit.point = inverseRay.point + t * inverseRay.direction;
			double x = hit.point(0);
			double y = hit.point(1);
			//Check to see if the hit point's x*x + y*y value is in the range [-1,1]
			if (x*x + y*y <= 1){
				RayIntersection hit;
				hit.material = material;
				// Intersection is in front of the ray's start point
				hit.point = transform.apply(hit.point);
				hit.normal = transform.apply(Normal(0,0,-1));
				if (hit.normal.dot(ray.direction) > 0){
					hit.normal = -hit.normal;
				}
				hit.distance = (hit.point - ray.point).norm();
				result.push_back(hit);
			}
		}
	}else if(z0t0 >= -1 && z0t0 <= 1){
		//Curved Surface
		RayIntersection hit;
		switch (sign(b2_4ac)){
		case -1:
			// No intersections
			break;
		case 0:
			// One intersection
			t = -b / (2 * a);
			if (t > 0){
				RayIntersection hit;
				hit.material = material;
				hit.point = inverseRay.point + t*inverseRay.direction;
				if(std::abs(hit.point(2)) < 1){
					// Intersection is in front of the ray's start point
					p(2) = 0;
					d(2) = 0;
					hit.point = transform.apply(Point(p + t * d));
					hit.normal = transform.apply(Normal(p + t * d));
					if (hit.normal.dot(ray.direction) > 0){
						hit.normal = -hit.normal;
					}
					hit.distance = (hit.point - ray.point).norm();
					result.push_back(hit);		
					}
				}
			break;
		case 1:
			// Two intersections
			t = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);
			if (t > 0 && (1 - z0)/dz > 0){
				RayIntersection hit;
				hit.material = material;
				hit.point = inverseRay.point + t*inverseRay.direction;
				if(std::abs(hit.point(2)) < 1){
					p(2) = 0;
					d(2) = 0;
					// Intersection is in front of the ray's start point
					hit.point = transform.apply(Point(p + t * d));
					hit.normal = transform.apply(Normal(p + t * d));
					if (hit.normal.dot(ray.direction) > 0){
						hit.normal = -hit.normal;
					}
					hit.distance = (hit.point - ray.point).norm();
					result.push_back(hit);
				}
			}
			t = (-b - sqrt(b * b - 4 * a * c)) / (2 * a);
			if (t > 0 && (-1 - z0)/dz > 0){
				RayIntersection hit;
				hit.material = material;
				hit.point = inverseRay.point + t*inverseRay.direction;
				if(std::abs(hit.point(2)) < 1){
					p(2) = 0;
					d(2) = 0;
					// Intersection is in front of the ray's start point
					hit.point = transform.apply(Point(p + t * d));
					hit.normal = transform.apply(Normal(p + t * d));
					if (hit.normal.dot(ray.direction) > 0){
						hit.normal = -hit.normal;
					}
					hit.distance = (hit.point - ray.point).norm();
					result.push_back(hit);
				}
			}		
			break;
		}
	}else if(z0t0 > 1){
		t = t0 + (t1 - t0) * (z0t0-1)/(z0t0-z0t1);
		//Bottom Circular Cap
		if (t > 0){
			RayIntersection hit;
			hit.point = inverseRay.point + t * inverseRay.direction;
			double x = hit.point(0);
			double y = hit.point(1);
			//Check to see if the hit point's x*x + y*y value is in the range [-1,1]
			if (x*x + y*y <= 1){
				RayIntersection hit;
				hit.material = material;
				// Intersection is in front of the ray's start point
				hit.point = transform.apply(hit.point);
				hit.normal = transform.apply(Normal(0,0,1));
				if (hit.normal.dot(ray.direction) > 0){
					hit.normal = -hit.normal;
				}
				hit.distance = (hit.point - ray.point).norm();
				result.push_back(hit);
			}
		}
	}
	return result;
}
