/* $Rev: 250 $ */
#include "Cube.h"

#include "utility.h"

Cube::Cube() : Object() {

}

Cube::Cube(const Cube& cube) : Object(cube) {

}

Cube::~Cube() {

}

const Cube& Cube::operator=(const Cube& cube) {
	if (this != &cube) {
		Object::operator=(cube);
	}
	return *this;
}

std::vector<RayIntersection> Cube::intersect(const Ray& ray) const {

	std::vector<RayIntersection> result;
	//Transform the ray
	Ray inverseRay = transform.applyInverse(ray);
	//Solve for hit point
	double x0 = inverseRay.point(0);
	double y0 = inverseRay.point(1);
	double z0 = inverseRay.point(2); 
	double dx = inverseRay.direction(0); 
	double dy = inverseRay.direction(1); 
	double dz = inverseRay.direction(2); 
	//Check if dz is not 0 or close to 0
	if(std::abs(dz) > epsilon){	
		//Back Face
		double t = (1-z0)/dz;
		if(t > 0){
			RayIntersection hit;
			hit.point = inverseRay.point + t*inverseRay.direction;
			//Check to see if the hit point's x value is in the range [-1,1]
			if(hit.point(0) < 1 && hit.point(0) > -1){
			//Check to see if the hit point's y value is in the range [-1,1]
				if(hit.point(1) < 1 && hit.point(1) > -1){
					//Assign the hit point the material of the plane
					hit.material = material;
					//Assign the hit point it's hit point
					hit.point = transform.apply(hit.point);
					//Assign the hit point's normal as [0,0,1]T
					hit.normal = transform.apply(Normal(0,0,1));
					//Assign the hit point's distance
					hit.distance = (hit.point - ray.point).norm();
					//Return the data associated with the hitpoint
					result.push_back(hit);
					}
				}
			}	
		//Front Face
		t = (-1-z0)/dz;
		if(t > 0){
			RayIntersection hit;
			hit.point = inverseRay.point + t*inverseRay.direction;
			//Check to see if the hit point's x value is in the range [-1,1]
			if(hit.point(0) < 1 && hit.point(0) > -1){
			//Check to see if the hit point's y value is in the range [-1,1]
				if(hit.point(1) < 1 && hit.point(1) > -1){
					//Assign the hit point the material of the plane
					hit.material = material;
					//Assign the hit point it's hit point
					hit.point = transform.apply(hit.point);
					//Assign the hit point's normal as [0,0,1]T
					hit.normal = transform.apply(Normal(0,0,-1));
					//Assign the hit point's distance
					hit.distance = (hit.point - ray.point).norm();
					//Return the data associated with the hitpoint
					result.push_back(hit);
				}
			}
		}
	}
	//Check dy is not 0 or close to 0
	if(std::abs(dy) > epsilon){	
		//Top Face
		double t = (-1-y0)/dy;
		if(t > 0){
			RayIntersection hit;
			hit.point = inverseRay.point + t*inverseRay.direction;
			//Check to see if the hit point's y value is in the range [-1,1]
			if(hit.point(0) < 1 && hit.point(0) > -1){
			//Check to see if the hit point's z value is in the range [-1,1]
				if(hit.point(2) < 1 && hit.point(2) > -1){
					//Assign the hit point the material of the plane
					hit.material = material;
					//Assign the hit point it's hit point
					hit.point = transform.apply(hit.point);
					//Assign the hit point's normal as [0,1,0]T
					hit.normal = transform.apply(Normal(0,-1,0));
					//Assign the hit point's distance
					hit.distance = (hit.point - ray.point).norm();
					//Return the data associated with the hitpoint
					result.push_back(hit);
				}
			}
		}
		//Bottom Face
		t = (1-y0)/dy;
		if(t > 0){
			RayIntersection hit;
			hit.point = inverseRay.point + t*inverseRay.direction;
			//Check to see if the hit point's x value is in the range [-1,1]
			if(hit.point(0) < 1 && hit.point(0) > -1){
			//Check to see if the hit point's z value is in the range [-1,1]
				if(hit.point(2) < 1 && hit.point(2) > -1){
					//Assign the hit point the material of the plane
					hit.material = material;
					//Assign the hit point it's hit point
					hit.point = transform.apply(hit.point);
					//Assign the hit point's normal as [0,1,0]T
					hit.normal = transform.apply(Normal(0,1,0));
					//Assign the hit point's distance
					hit.distance = (hit.point - ray.point).norm();
					//Return the data associated with the hitpoint
					result.push_back(hit);
				}
			}
		}
	}		
	//Check dx is not 0 or close to 0
	if(std::abs(dx) > epsilon){	
		//Left Face
		double t = (-1-x0)/dx;
		if(t > 0){
			RayIntersection hit;
			hit.point = inverseRay.point + t*inverseRay.direction;
			//Check to see if the hit point's y value is in the range [-1,1]
			if(hit.point(1) < 1 && hit.point(1) > -1){
			//Check to see if the hit point's z value is in the range [-1,1]
				if(hit.point(2) < 1 && hit.point(2) > -1){
					//Assign the hit point the material of the plane
					hit.material = material;
					//Assign the hit point it's hit point
					hit.point = transform.apply(hit.point);
					//Assign the hit point's normal as [1,0,0]T
					hit.normal = transform.apply(Normal(-1,0,0));
					//Assign the hit point's distance
					hit.distance = (hit.point - ray.point).norm();
					//Return the data associated with the hitpoint
					result.push_back(hit);
				}
			}
		}
		//Right Face
		t = (1-x0)/dx;
		if(t > 0){
			RayIntersection hit;
			hit.point = inverseRay.point + t*inverseRay.direction;
			//Check to see if the hit point's y value is in the range [-1,1]
			if(hit.point(1) < 1 && hit.point(1) > -1){
			//Check to see if the hit point's z value is in the range [-1,1]
				if(hit.point(2) < 1 && hit.point(2) > -1){
					//Assign the hit point the material of the plane
					hit.material = material;
					//Assign the hit point it's hit point
					hit.point = transform.apply(hit.point);
					//Assign the hit point's normal as [1,0,0]T
					hit.normal = transform.apply(Normal(1,0,0));
					//Assign the hit point's distance
					hit.distance = (hit.point - ray.point).norm();
					//Return the data associated with the hitpoint
					result.push_back(hit);
				}
			}
		}
	}		
	return result;
}