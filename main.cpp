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


#include "bitmap_image.hpp"

const string expected_input= "Expected:\n"
				             "-input <name of the input file>\n"
				             "(-output <name of the output file>)\n"
				             "(-size <width of the output picture as an integer> <height of the output picture as an integer>)\n"
				             "(-normals <name of the file to save the visualization of normals>)\n"
				             "(-depth <numeric minimum depth> <numeric maximum depth> <name of the file to save the visualization of depth>)\n";

int parseArgs(int argc, char* argv[], int &sizeX, int &sizeY, char *&input, char *&output, char *&normals, char *&depth, float &depthMin, float &depthMax){
  for( size_t argNum = 1; argNum < argc; ++argNum )
    {
		try{
			if(strcmp(argv[argNum],"-input")==0&&argNum+1<argc){
				input=argv[++argNum];
			}
			else if(strcmp(argv[argNum],"-output")==0&&argNum+1<argc){
				output=argv[++argNum];
			}
			else if(strcmp(argv[argNum],"-normals")==0&&argNum+1<argc){
				normals=argv[++argNum];
			}
			else if(strcmp(argv[argNum],"-size")==0&&argNum+2<argc){
				sizeX=stoi(argv[++argNum]);
				sizeY=stoi(argv[++argNum]);				
			}
			else if(strcmp(argv[argNum],"-depth")==0&&argNum+3<argc){
				depthMin=stof(argv[++argNum]);
				depthMax=stof(argv[++argNum]);
				depth=argv[++argNum];
			}
			else throw(out_of_range(""));
		}
		catch (const out_of_range){
			cerr<<"Unknown command line argument or too few parameters given\n"+expected_input;
			return 1;
		}
		catch (const invalid_argument){
			cerr<<"Non-numeric values for size or depth-range\n"+expected_input;
			return 1;
		}
    }
  if(input==NULL){
	cerr<<"no input file specified\n";
	return 2;
  }
  return 0;

}

int main( int argc, char* argv[] )
{
  // Fill in your implementation here.

  // This loop loops over each of the input arguments.
  // argNum is initialized to 1 because the first
  // "argument" provided to the program is actually the
  // name of the executable (in our case, "a4").

  //asetetaan input, normals ja depth NULLiksi vertailun helpottamiseksi
  //annetaan outputille oletusarvoksi "output.bmp" ja kuvan oletuskooksi 200x200, yksinkertaisimmillaan siis voi ajaa antamalla komentorivi-argumenttina ainoastaan input-tiedoston nimen
  char *input=NULL,*output="output.bmp", *normals=NULL, *depth=NULL;
  int sizeX=200,sizeY=200;
  float depthMin, depthMax;

  int parse= parseArgs(argc, argv, sizeX, sizeY, input, output, normals, depth, depthMin, depthMax);
  if(parse)return parse;
    
  // First, parse the scene using SceneParser.
  // Then loop over each pixel in the image, shooting a ray
  // through that pixel and finding its intersection with
  // the scene.  Write the color at the intersection to that
  // pixel in your output image.
  SceneParser sp=SceneParser(input);
  Image image(sizeX, sizeY), imageN(sizeX, sizeY), imageD(sizeX, sizeY);
 
  for(size_t i =0;i<sizeX;i++){
	  float x=-1+(float)(2*i)/sizeX;
	  for (size_t j =0;j<sizeY;j++){
		  image.SetPixel(i,j,sp.getBackgroundColor());

		  Ray r=sp.getCamera()->generateRay(Vector2f(x,-1+(float)(2*j)/sizeY));
		  Hit h=Hit();
		  bool hit=sp.getGroup()->intersect(r,h,0);
		  if(hit){
			  Vector3f dir, temp_color, color;
			  float dist=h.getT();

			  //piirretään syvyysarvot, jos komentorivillä ollaan pyydetty näin tehtävän
			  if(depth!=NULL&&dist>depthMin&&dist<depthMax){
				  float g=1-(dist-depthMin)/(depthMax-depthMin);
				  imageD.SetPixel(i,j,Vector3f(g,g,g)); 
			  }
			  //piirretään normaalit väreinä, jos komentorivillä ollaan pyydetty näin tehtävän
			  if(normals!=NULL) 
				  imageN.SetPixel(i,j,Vector3f(abs(h.getNormal()[0]),abs(h.getNormal()[1]),abs(h.getNormal()[2])));

			  for(size_t k=0;k<sp.getNumLights();k++){
				  Light *l=sp.getLight(k);
				  l->getIllumination(r.pointAtParameter(h.getT()),dir,temp_color,dist);
				  color=color+h.getMaterial()->Shade(r,h,dir,temp_color);;
			  }

			 image.SetPixel(i,j,color+sp.getAmbientLight()*h.getMaterial()->getDiffuseColor());
		  }
	  }
  }
 
  image.SaveImage(output);
  if(normals!=NULL) imageN.SaveImage(normals);
  if(depth!=NULL) imageD.SaveImage(depth);
  return 0;
}

