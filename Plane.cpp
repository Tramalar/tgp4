#include "Object3D.h"
#include <vecmath.h>
#include "Plane.h"

float const TOL=1e-6;

bool Plane::intersect( const Ray& r , Hit& h , float tmin){
	float dotp=Vector3f::dot(normal,r.getDirection());
	if(abs(dotp)<TOL)return false;
	float t=(D+Vector3f::dot(normal,r.getOrigin()))/dotp;
	float oldt=h.getT();
	if(t>tmin&&t<oldt)h.set(t,material,normal);
	return t>tmin&&t<oldt;
} 