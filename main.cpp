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
  vector<string> args=vector<string>();
  for( int argNum = 1; argNum < argc; ++argNum )
    {
		try{
			if(strcmp(argv[argNum],"-input")==0&&argNum+1<argc){
				input=argv[++argNum];
			}
			else if(strcmp(argv[argNum],"-output")==0&&argNum+1<argc){
				output=argv[++argNum];
			}
			else if(strcmp(argv[argNum],"-size")==0&&argNum+2<argc){
				sizeX=stoi(argv[++argNum]);
				sizeY=stoi(argv[++argNum]);				
			}
			else throw(out_of_range("Index out of range"));
		}
		catch (...){
			cerr<<"bad commandline arguments";
			return 1;
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
		  image.SetPixel(i,j,sp.getBackgroundColor());
		  if(hit){
			  Vector3f dir;
			  Vector3f col;
			  Vector3f color;
			  float dist=h.getT();
			  for(int k=0;k<sp.getNumLights();k++){
				Light *l=sp.getLight(k);
				l->getIllumination(r.pointAtParameter(h.getT()),dir,col,dist);
				color=color+h.getMaterial()->Shade(r,h,dir,col);;
			  }
			image.SetPixel(i,j,color+sp.getAmbientLight()*h.getMaterial()->getDiffuseColor());
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

