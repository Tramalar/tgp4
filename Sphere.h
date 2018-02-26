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

	virtual bool intersect( const Ray& r , Hit& h , float tmin){
		float b=2*Vector3f::dot(r.getDirection(),r.getOrigin()-center);
		float c=Vector3f::dot(r.getOrigin()-center,r.getOrigin()-center)-radius*radius;
		float d=sqrt(b*b-4*r.getDirection().absSquared()*c);

		float tp=(-b+d)/(2*r.getDirection().abs());
		float tm=(-b-d)/(2*r.getDirection().abs());
		float t=tp>tm?tm:tp;
		float oldt=h.getT();
		if(t>tmin&&t<oldt)h.set(t,material,(r.pointAtParameter(t)-center).normalized());
		return t>tmin&&t<oldt;
	}

protected:
	Vector3f center;
	float radius;

};


#endif
