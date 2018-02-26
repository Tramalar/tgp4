#ifndef PLANE_H
#define PLANE_H

#include "Object3D.h"
#include <vecmath.h>
#include <cmath>
using namespace std;
///TODO: Implement Plane representing an infinite plane
///choose your representation , add more fields and fill in the functions
class Plane: public Object3D
{
public:
	Plane(){}
	Plane( const Vector3f& normal , float d , Material* m):Object3D(m),normal(normal),D(d){;
	}
	~Plane(){}
	virtual bool intersect( const Ray& r , Hit& h , float tmin){
		float t=(D+Vector3f::dot(normal,r.getOrigin()))/Vector3f::dot(normal,r.getDirection());
		float oldt=h.getT();
		if(t>tmin&&t<oldt)h.set(t,material,normal);
		return t>tmin&&t<oldt;
	}

protected:
	Vector3f normal;
	float D;
};
#endif //PLANE_H
		

