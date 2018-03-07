#include "Object3D.h"
#include <vecmath.h>
#include <cmath>
#include "Sphere.h"

float const TOL=1e-6;

bool Sphere::intersect( const Ray& r , Hit& h , float tmin ){
	float b=2*Vector3f::dot(r.getDirection(),r.getOrigin()-center);
	float c=Vector3f::dot(r.getOrigin()-center,r.getOrigin()-center)-radius*radius;
	float d=sqrt(b*b-4*r.getDirection().absSquared()*c);

	float tp=(-b+d)/(2*r.getDirection().abs());
	float tm=(-b-d)/(2*r.getDirection().abs());
	float t=tp>tm?tm:tp;
	float oldt=h.getT();
	bool hit=t>tmin&&t<oldt&&d>TOL;
	if(hit)h.set(t,material,(r.pointAtParameter(t)-center).normalized());
	return hit;
}