#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Object3D.h"
#include <vecmath.h>
#include <cmath>
#include <iostream>

using namespace std;
///TODO: implement this class.
///Add more fields as necessary,
///but do not remove hasTex, normals or texCoords
///they are filled in by other components
class Triangle: public Object3D
{
public:
	Triangle();
        ///@param a b c are three vertex positions of the triangle
	Triangle( const Vector3f& a, const Vector3f& b, const Vector3f& c, Material* m):Object3D(m),a(a),b(b),c(c){
          hasTex = false;
	}

	virtual bool intersect( const Ray& ray,  Hit& hit , float tmin){
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
	bool hasTex;
	Vector3f normals[3];
	Vector2f texCoords[3];
protected:
	Vector3f a,b,c;

};

#endif //TRIANGLE_H
