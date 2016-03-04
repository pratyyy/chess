/*******************************************************
* Main file for The Graphical Display(Requires draw.h) 

* Basic Concept for graphical output: 
	1.3ds file for various pieces is used to draw the piece object using the file load_3ds.h. 
	
	2.With the help of glut glPushname function each object has been assigned a unique id and 
	placed at particular positions. This helped in easy picking of the object by the mouse.
	
	3.gluLookAt function is used to rotate the camera angle on pressing the various keys.	 

	4.Creating the window using glut functions 

* Author : Prateek Vaishnav 
	   Gaurav Kishore 
*********************************************************/ 

///Header/////

#ifdef __WIN32__
#include <windows.h>
#endif

#ifdef __APPLE__
#include<OpenGL/gl.h>
#include<GLUT/glut.h>
#else
#include<GL/gl.h>
#include<GL/glut.h>
#endif

#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <vector>
#include <time.h>
#include <string.h>
#include <sstream>
#include "imageloader.h"
#include "load_bmp.h"
#include "load_3ds.h"
#include "object.h"
#include "draw.h"

///Header/////

// Picking Stuff //
#define RENDER					1
#define SELECT					2
#define BUFSIZE 1024
#define on 					1
#define off					0

using namespace std;


int screen_width=1000;
int screen_height=800;
static float alpha=0.0;

double rotation_x=0, rotation_x_increment=0.1;
double rotation_y=0, rotation_y_increment=0.05;
double rotation_z=0, rotation_z_increment=0.03;
static int hite[32]= {0};
static float xhite[32]= {0};
static float yhite[32]= {0};
static int boardpile[64] = {0};
static int posii =0;
static int positionpieces[32][2];
static int xcoord=0, ycoord=1;
static int blackchance = 0;
static int status = 0;
static float allowed[8][8]={0.0};
static float allowedred[8][8]={0.0};
static int froms, tos;
static bool murdered[32] = {0};
static float murderedxhite[32] = {0};
static float murderedyhite[32] = {0};
int filling=1; //0=OFF 1=ON
int chkfrom, chkto;
static bool anim =1;

//Lights settings
GLfloat light_ambient[]= { 0.1f, 0.1f, 0.1f, 0.1f };
GLfloat light_diffuse[]= { 1.0f, 1.0f, 1.0f, 0.0f };
GLfloat light_specular[]= { 1.0f, 1.0f, 1.0f, 0.0f };
GLfloat light_position[]= { 50.0f, 0.0f, 20.0f, 1.0f };

//Materials settings
GLfloat mat_ambient[]= { 0.7f, 0.7f, 0.7f, 0.0f };
GLfloat mat_diffuse[]= { 0.7f, 0.7f, 0.7f, 0.0f };
GLfloat mat_specular[]= { 1.0f, 1.0f, 1.0f, 0.0f };
GLfloat mat_shininess[]= { 1.0f };
int mainwindow, rightwindow , leftwindow;
static int screenvar = 3;   ///welcome screen

GLuint selectBuf[BUFSIZE];
GLint hits;
int mode = RENDER;
int cursorX,cursorY;

void displayGUI(U64 current);
void finalupdateGUI(int fromsq, int tosq);
void displaypossiblemoves(int position);
void initialispositions();
void startPicking() ;
void processHits2 (GLint hits, GLuint buffer[], int sw);
void stopPicking() ;
void setting();
void init(void);
void resize (int p_width, int p_height);
void keyboard(unsigned char p_key, int p_x, int p_y);
void keyboard_s (int p_key, int p_x, int py);
void endgameGUI(int i);
void display(void);
void Drawscene();
void mouseStuff(int button, int state, int x, int y);
void update(int value);
void mouse_move_CB(int x,int y);
void mainnn();


