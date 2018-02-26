#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <vecmath.h>
#include "Object3D.h"
///TODO implement this class
///So that the intersect function first transforms the ray
///Add more fields as necessary
class Transform: public Object3D
{
public: 
  Transform(){}
 Transform( const Matrix4f& m, Object3D* obj ):o(obj),trans(m){
    ;
  }
  ~Transform(){
  }
  virtual bool intersect( const Ray& r , Hit& h , float tmin){
	  Vector3f newO=(trans.inverse()*Vector4f(r.getOrigin(),1)).xyz();
	  Vector3f newD=(trans.inverse()*Vector4f(r.getDirection(),0)).xyz();
	  bool hit = o->intersect( Ray(newO,newD), h , tmin);
	  Vector3f newN=(trans.inverse().transposed()*Vector4f(h.getNormal(),0)).xyz().normalized();
	  h.set(h.getT(),h.getMaterial(),newN);
	  return hit;
  }

 protected:
  Object3D* o; //un-transformed object	
  Matrix4f trans;
};

#endif //TRANSFORM_H
