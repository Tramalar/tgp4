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
protected:
	Vector3f normal;
	float D;
public:
	Plane(){}
	Plane( const Vector3f& normal , float d , Material* m):Object3D(m){
		this->normal=normal;
		D=d;
	}
	~Plane(){}
	virtual bool intersect( const Ray& r , Hit& h , float tmin);

};
#endif //PLANE_H
		

