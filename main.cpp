#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>

#include "SceneParser.h"
#include "Image.h"
#include "Camera.h"
#include <string.h>

using namespace std;

float clampedDepth ( float depthInput, float depthMin , float depthMax);

#include "bitmap_image.hpp"
int main( int argc, char* argv[] )
{
  // Fill in your implementation here.

  // This loop loops over each of the input arguments.
  // argNum is initialized to 1 because the first
  // "argument" provided to the program is actually the
  // name of the executable (in our case, "a4").

  char* input,*output;
  int sizeX,sizeY;
  for( int argNum = 1; argNum < argc; ++argNum )
    {
		switch(argNum){
		case 2:
			input=argv[argNum];break;
		case 4:
			sizeX=stoi(argv[argNum]);break;
		case 5:
			sizeY=stoi(argv[argNum]);break;
		case 7:
			output=(argv[argNum]);break;
		}
    }
	
    
  // First, parse the scene using SceneParser.
  // Then loop over each pixel in the image, shooting a ray
  // through that pixel and finding its intersection with
  // the scene.  Write the color at the intersection to that
  // pixel in your output image.
  SceneParser sp=SceneParser(input);
  Image image( sizeX,sizeY );
  for(int i =0;i<sizeX;i++)
	  for (int j =0;j<sizeY;j++){
		  Ray r=sp.getCamera()->generateRay(Vector2f(-1+(2*i+0.f)/sizeX,-1+(2*j+0.f)/sizeY));
		  Hit h=Hit();
		  bool hit=sp.getGroup()->intersect(r, h,0);
		  if(hit){
			  Vector3f dir;
			  Vector3f col;		
			  float dist=h.getT();
			  Light *l=sp.getLight(0);
			  l->getIllumination(r.pointAtParameter(h.getT()),dir,col,dist);
			  Vector3f color= h.getMaterial()->Shade(r,h,dir,col);
			  image.SetPixel(i,j,color);
		  }
	  }
 
  image.SaveImage(output);
  


  ///TODO: below demonstrates how to use the provided Image class
  /////Should be removed when you start
  //Vector3f pixelColor (1.0f,0,0);
  ////width and height
  //Image image( 10 , 15 );
  //image.SetPixel( 5,5, pixelColor );
  //image.SaveImage("demo.bmp");
  return 0;
}

