
#include<iostream>
#include "imageloader.h"
#include "draw.h"

int tex[100];

using namespace std;

GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D,
				 0,
				 GL_RGB,
				 image->width, image->height,
				 0,
				 GL_RGB,
				 GL_UNSIGNED_BYTE,
				 image->pixels);
	return textureId;
}




void loadallimages()
{
	Image* image1 = loadBMP("texture/boards/blueboard.bmp");
	tex[1] = loadTexture(image1);
	delete image1;
		
	Image* image2 = loadBMP("texture/boards/greenboard.bmp");
	tex[2] = loadTexture(image2);
	delete image2;

	Image* image3 = loadBMP("texture/boards/lightblueboard.bmp");
	tex[3] = loadTexture(image3);
	delete image3;

	Image* image4 = loadBMP("texture/boards/lightgreenboard.bmp");
	tex[4] = loadTexture(image4);
	delete image4;

	Image* image5 = loadBMP("texture/boards/woodboard.bmp");
	tex[5] = loadTexture(image5);
	delete image5;

	Image* image6= loadBMP("texture/boards/square.bmp");
	tex[6] = loadTexture(image6);
	delete image6;
	
	Image* image7= loadBMP("texture/images/chess.bmp");
	tex[7] = loadTexture(image7);
	delete image7;
	
	Image* image8= loadBMP("texture/button/new.bmp");
	tex[8] = loadTexture(image8);
	delete image8;
	
	Image* image9= loadBMP("texture/button/exit.bmp");
	tex[9] = loadTexture(image9);
	delete image9;
	
	Image* image10= loadBMP("texture/boards/red.bmp");
	tex[10] = loadTexture(image10);
	delete image10;
	
	Image* image11= loadBMP("texture/button/animate.bmp");
	tex[11] = loadTexture(image11);
	delete image11;
	

}



void background(){

	glPushMatrix();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex[1+ theme]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glColor3f(1.0f, 1.0f, 1.0f);
	
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-8, -8,0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(8, -8,0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(8,8,0);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-8,8,0);
	glEnd();
	glPopMatrix();
	//glFlush();
	//glutSwapBuffers();

	
}
void boardimages(int xside, int yside)
{
	glPushMatrix();
	glTranslatef(7+xside,-7+yside,0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex[6]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1, -1,0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1, -1,0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1,1,0);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1,1,0);
	glEnd();
	glPopMatrix();
}

void boardredimages(int xside, int yside)
{
	glPushMatrix();
	glTranslatef(7+xside,-7+yside,0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex[10]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1, -1,0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1, -1,0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1,1,0);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1,1,0);
	glEnd();
	glPopMatrix();
}

void endgameimage(){
	
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex[1+ theme]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glColor3f(1.0f, 1.0f, 1.0f);
	
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-8, -8,0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(8, -8,0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(8,8,0);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-8,8,0);
	glEnd();
	glPopMatrix();
	//glFlush();
	//glutSwapBuffers();
	
}



void welcome()
{
	glPushMatrix();
	gluLookAt(0,0,13.5, 0,-6.8,-1, 0,1,0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex[7]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glColor3f(1.0f, 1.0f, 1.0f);
	
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-10.1, -8,0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(10.1, -8,0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(10.1,8,0);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-10.1,8,0);
	glEnd();
	glPopMatrix();
}
void newgame(float add)
{
	//glScalef(1,0.5,1);
	glPushMatrix();
	glScalef(1,0.5,1);
	gluLookAt(0,0,13.5, 0,-6.8,-1, 0,1,0);
	glTranslatef(6.5, -4, 1.5);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex[8]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glColor3f(1.0f, 1.0f, 1.0f);
	
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1-add, -1-add,0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1+add, -1-add,0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1+add,1+add,0);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1-add,1+add,0);
	glEnd();
	glPopMatrix();
}

void exitgame(float add)
{
	
	glPushMatrix();
	glScalef(1,0.5,1);
	gluLookAt(0,0,13.5, 0,-6.8,-1, 0,1,0);
	glTranslatef(6.5, -4, 1.5);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex[9]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glColor3f(1.0f, 1.0f, 1.0f);
	
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1-add, -1-add,0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1+add, -1-add,0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1+add,1+add,0);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1-add,1+add,0);
	glEnd();
	glPopMatrix();
}

void animate(float add)
{
	
	glPushMatrix();
	glScalef(1,0.5,1);
	gluLookAt(0,0,13.5, 0,-6.8,-1, 0,1,0);
	glTranslatef(6.5, -4, 1.5);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex[11]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glColor3f(1.0f, 1.0f, 1.0f);
	
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1-add, -1-add,0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1+add, -1-add,0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1+add,1+add,0);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1-add,1+add,0);
	glEnd();
	glPopMatrix();
}


void welcome1()
{
	glPushMatrix();
	gluLookAt(0,0,13.5, 0,-6.8,-1, 0,1,0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex[10]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glColor3f(1.0f, 1.0f, 1.0f);
	
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-10.1, -8,0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(10.1, -8,0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(10.1,8,0);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-10.1,8,0);
	glEnd();
	glPopMatrix();
}
