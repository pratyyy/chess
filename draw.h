/*******************************************************
* Loads all the image files and draw them. Used to draw the 
	pregame scenario and give a good graphics look 

* Author : Prateek Vaishnav 
	   Gaurav Kishore

*********************************************************/ 
#ifdef __APPLE__
#include<OpenGL/gl.h>
#include<GLUT/glut.h>
#else
#include<GL/gl.h>
#include<GL/glut.h>
#endif

const float BOX_SIZE = 1.5f;                                    // buttons size 
static int theme = 0;						// theme no
static float xeye=0.0, yeye=-10.0, zeye= 5.0, xlook=0.0, ylook=0.0, zlook=-1.0;   // camera & look at coordiantes 
static float bxeye=0.0, byeye=-3.0, bzeye= 5.0, bxlook=0.0, bylook=0.0, bzlook=-10.0;
static float addnew = 0.0, exitnew = 0.0, addanimate = 0.0;


GLuint loadTexture(Image* image);
void loadallimages();                                         // load all the images 
void background();
void boardimages(int xside, int yside);
void boardredimages(int xside, int yside);
void endgameimage();
void welcome();
void newgame(float f);
void exitgame(float f);
void animate(float f);
void welcome1();
