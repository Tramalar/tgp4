#include "Object3D.h"
#include <vecmath.h>
#include "Triangle.h"


bool Triangle::intersect( const Ray& ray,  Hit& hit , float tmin){
	Matrix3f A,B,G,T;
	A.setCol(0,a-b);A.setCol(1,a-c);A.setCol(2,ray.getDirection());
	B.setCol(0,a-ray.getOrigin());B.setCol(1,a-c);B.setCol(2,ray.getDirection());
	G.setCol(0,a-b);G.setCol(1,a-ray.getOrigin());G.setCol(2,ray.getDirection());
	T.setCol(0,a-b);T.setCol(1,a-c);T.setCol(2,a-ray.getOrigin());

	float detA=A.determinant();
	float beta=B.determinant()/detA;
	float gamma=G.determinant()/detA;
	float alpha=1-beta-gamma;
	float t=T.determinant()/detA;
	float oldt=hit.getT();

	bool h=t>tmin&&t<oldt&&alpha>=0&&beta>=0&&gamma>=0;
	if(h)hit.set(t,material,alpha*normals[0]+beta*normals[1]+gamma*normals[2]);
	return h;
}