#ifndef SPHERE_H
#define SPHERE_H

#include "Object3D.h"
#include <vecmath.h>
#include <cmath>

#include <iostream>
using namespace std;
///TODO:
///Implement functions and add more fields as necessary
class Sphere: public Object3D
{
protected:
	Vector3f center;
	float radius;
public:
	Sphere(){ 
		this->center=Vector3f(0,0,0);
		this->radius=1.f;
		//unit ball at the center
	}

	Sphere( Vector3f center , float radius , Material* material ):Object3D(material){
		this->center=center;
		this->radius=radius;
	}
	

	~Sphere(){}

	virtual bool intersect( const Ray& r , Hit& h , float tmin);


};


#endif
