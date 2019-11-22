#include "Scene.h"

#include "Colour.h"
#include "ImageDisplay.h"
#include "utility.h"
#include "math.h"

Scene::Scene() : backgroundColour(0,0,0), maxRayDepth(3), renderWidth(800), renderHeight(600), filename("render.png"), camera_(), objects_(), lights_() {

}

Scene::~Scene() {

}

void Scene::render() const {
	ImageDisplay display("Render", renderWidth, renderHeight);
	
	std::cout << "Rendering a scene with " << objects_.size() << " objects" << std::endl;
	
	const double w = double(renderWidth);
	const double h = double(renderHeight);

	for (unsigned int v = 0; v < renderHeight; ++v) {
		for (unsigned int u = 0; u < renderWidth; ++u) {
			double cu = -1 + (u + 0.5)*(2.0 / w);
			double cv = -h/w + (v + 0.5)*(2.0 / w);
			Ray ray = camera_->castRay(cu, cv);
			display.set(u, v, computeColour(ray, maxRayDepth));
		}
		display.refresh();
	}

	display.save(filename);
	display.pause(5);
}

RayIntersection Scene::intersect(const Ray& ray) const {
	RayIntersection firstHit;
	firstHit.distance = infinity;	
	for (auto& obj : objects_) {
		for (auto& hit : obj->intersect(ray)) {
			if (hit.distance > epsilon && hit.distance < firstHit.distance) {
				firstHit = hit;
			}
		}
	}	return firstHit;
}

Colour Scene::computeColour(const Ray& ray, unsigned int rayDepth) const {
	RayIntersection hitPoint = intersect(ray);
	if (hitPoint.distance == infinity) {
		return backgroundColour;
	}

	Colour hitColour(0, 0, 0);
		
	// Code to do better lighting, shadows, and reflections goes here.
    for (auto light: lights_) {
        // Compute the influence of this light on the appearance of the hit object.
		if (light->getDistanceToLight(hitPoint.point) < 0) {
			// An ambient light, ignore shadows and add appropriate colour
			hitColour += light->getIlluminationAt(hitPoint.point) * hitPoint.material.ambientColour;
		} else {
			Vector n = hitPoint.normal;
			n = n/n.norm();
			Vector l = - light->getLightDirection(hitPoint.point);
			l = l/l.norm();
			Colour id = light->getIlluminationAt(hitPoint.point);
			Colour kd = hitPoint.material.diffuseColour;
			Colour is = light->getIlluminationAt(hitPoint.point);
			Colour ks = hitPoint.material.specularColour;
			// r = reflection of l about n
			Vector r = 2*(n.dot(l))*n- l;
			r = r/r.norm();
			// v = vector from hit point back along the view ray
			Vector v = -ray.direction;
			v = v/v.norm();
			//a = specular exponent
			double a = hitPoint.material.specularExponent;
			bool inShadow = false;
			//Cast shadow ray check for intersections
			Ray shadowRay = Ray();
			shadowRay.point = hitPoint.point;
			shadowRay.direction = -light->getLightDirection(hitPoint.point);
			RayIntersection hit = intersect(shadowRay);
			if(hit.distance < hitPoint.distance){
				inShadow = true;
			}
			//If the point is not in shadow calculate diffuse and specular light
			if(!inShadow){
				//Check that the angle between the light and the surface is not 0
				if(n.dot(l) > 0){
					//Diffuse Lighting
					hitColour += id * kd *(n.dot(l));
				}
				//Check the angle between the reflection and the viewpoint is not 0
				if(r.dot(v)<= 1){
					//Specular Lighting
					hitColour += (is * ks) * pow(r.dot(v), a);
				}
			}
		}
    }
	/**********************************
   	 * TODO - ADD MIRROR EFFECTS HERE *
	 **********************************/
	if(rayDepth > 0){
		Vector n = hitPoint.normal;
		n = n/n.norm();
		Vector v = -ray.direction;
		v = v/v.norm();
		Ray mirrorRay;
		mirrorRay.point = hitPoint.point;
		mirrorRay.direction = 2 * (n.dot(v))*n-v;
		hitColour += hitPoint.material.mirrorColour * computeColour(mirrorRay, rayDepth-1);
	}
	hitColour.clip();
	return hitColour;
}

bool Scene::hasCamera() const {
	return bool(camera_);
}
