#include <stdlib.h>
#include <math.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <GL/glut.h>
using namespace std;
//init window dimension
const int width =640;
const int height =480;
// angle of rotation for the camera direction
float angle = 0.0f;
float angleY = 0.0f;
// direction of the camera
float dX=0.0f,dZ=-1.0f,dY=0.0f;
// initial position
float x=0.0f, z=5.0f;
//initialization of delta movement and delta angle
float teta = 0.0f;
float tetaY = 0.0f;
float mov = 0.0f;
float movX = 0.0f;
// initialization texture variables
unsigned int texName;
unsigned int texPyr;
unsigned int texTree0;
unsigned int texTree1;
// initialization variables for read img file
GLint Colors;
GLenum texture_format;
void init()
{
glClearColor(0.6, 0.6, 1.0, 1.0);
glShadeModel(GL_SMOOTH);
glEnable(GL_DEPTH_TEST);
}
unsigned int loadTexture(const char* filename) // function that load the texture
from a image
{
SDL_Surface *img =IMG_Load(filename);
// get the number of channels in the SDL surface
Colors = img->format->BytesPerPixel;
if (Colors == 4) // contains an alpha channel
{
if (img->format->Rmask == 0x000000ff)
texture_format = GL_RGBA;
} else if (Colors == 3) // no alpha channel
{
if (img->format->Rmask == 0x000000ff)
texture_format = GL_RGB;
}
unsigned int id;
glGenTextures(1,&id); // generate texture
glBindTexture(GL_TEXTURE_2D,id); //how i want to use tex
glTexImage2D(GL_TEXTURE_2D,0,img->format->BytesPerPixel,img->w,img-
>h,0,texture_format,GL_UNSIGNED_BYTE,img->pixels);//load texture for opengl
structure
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
SDL_FreeSurface(img); //Frees the resources used by a previousdY created
SDL_Surface
return id;
}
void reshape(int w, int h) {
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glViewport(0, 0, w, h);
gluPerspective(45.0f, w/h, 0.1f, 100.0f);
}
void drawTree(unsigned int tex)
{ // draw first half of the tree
glPushMatrix();
glEnable(GL_TEXTURE_2D);
glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);// make surface
transparent
glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE); // make
surface transparent
glEnable(GL_ALPHA_TEST);
glAlphaFunc(GL_GREATER, 0.0f);
glBindTexture(GL_TEXTURE_2D, tex);
// draw and fix texture vertex
glBegin(GL_QUADS);
glTexCoord2i(1,0);
glVertex3f(0.0f, 0.0f, 0.0f);
glTexCoord2i(1,1);
glVertex3f(0.0f, 5.0f, 0.0f);
glTexCoord2i(0,1);
glVertex3f( 2.0f, 5.0f, 0.0f);
glTexCoord2i(0,0);
glVertex3f( 2.0f, 0.0f, 0.0f);
glEnd();
glDisable(GL_TEXTURE_2D);
glDisable(GL_BLEND);
glDisable(GL_ALPHA_TEST);
glPopMatrix();
// draw second half of the tree (rotate of 90°)
glPushMatrix();
glEnable(GL_TEXTURE_2D);
glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
glEnable(GL_ALPHA_TEST);
glAlphaFunc(GL_GREATER, 0.0f);
glBindTexture(GL_TEXTURE_2D, tex);
glBegin(GL_QUADS);
glTexCoord2i(0,0);
glVertex3f(1.0f, 0.0f, 1.0f);
glTexCoord2i(1,0);
glVertex3f(1.0f, 0.0f, -1.0f);
glTexCoord2i(1,1);
glVertex3f( 1.0f, 5.0f, -1.0f);
glTexCoord2i(0,1);
glVertex3f( 1.0f, 5.0f, 1.0f);
glEnd();
glDisable(GL_TEXTURE_2D);
glDisable(GL_BLEND);
glDisable(GL_ALPHA_TEST);
glPopMatrix();
}
void movement(float mov) // increment movement up down
{
x += mov * dX * 0.1f;
z += mov * dZ * 0.1f;
} void movementX(float movX) // increment movement left right
{
x += movX * (-dZ) * 0.1f;
z += movX * dX* 0.1f;
} void direction(float teta) // increment direction of the head
{
angle += teta;
dX = sin(angle);
dZ = -cos(angle);
} void directionY(float tetaY) // increment the direction of the head along Y
{
if(angleY>1 ) //limit the visual of head
{
angleY = 1;
dY = sin(angleY);
}
if(angleY<-1 ) //limit the visual of head
{
angleY = -1;
dY = sin(angleY);
}
else
angleY += tetaY;
dY = sin(angleY);
} void display(void) {
//// call the movement and direction function
if (mov != 0)
movement(mov);
if (movX != 0)
movementX(movX);
if (teta!= 0)
direction(teta);
if (tetaY!= 0)
directionY(tetaY);
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
// Set the camera
gluLookAt( x, 1.0f, z,
x+dX, 1.0f+dY, z+dZ, // the position along y axis remains
constant
0.0f, 1.0f, 0.0f);
// Draw ground
glPushMatrix();
glEnable(GL_TEXTURE_2D);
glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL); //set env.
glBindTexture(GL_TEXTURE_2D, texName);
glBegin(GL_QUADS);
glTexCoord2i(0,0);
glVertex3f(-100.0f, 0.0f, -100.0f);
glTexCoord2i(200,0);
glVertex3f(-100.0f, 0.0f, 100.0f);
glTexCoord2i(200,200);
glVertex3f( 100.0f, 0.0f, 100.0f);
glTexCoord2i(0,200);
glVertex3f( 100.0f, 0.0f, -100.0f);
glEnd();
glDisable(GL_TEXTURE_2D);
glPopMatrix();
// create piramid
glPushMatrix();
glEnable(GL_TEXTURE_2D);
glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL); //set env.
glBindTexture(GL_TEXTURE_2D, texPyr);
glTranslatef(0,0,-50);
glBegin( GL_TRIANGLES );
glTexCoord2i(0,0);
glVertex3f( 10.0f, 0.f, 10.0f );
glTexCoord2i(20,0);
glVertex3f(10.0f, 0.0f, -10.0f );
glTexCoord2i(20,20);
glVertex3f( 0.0f, 20.0f, 0.0f);
glTexCoord2i(0,0);
glVertex3f(10.0f, 0.0f, -10.0f );
glTexCoord2i(20,0);
glVertex3f( -10.0f, 0.0f, -10.0f);
glTexCoord2i(20,20);
glVertex3f( 0.0f, 20.0f, 0.0f);
glTexCoord2i(0,0);
glVertex3f( -10.0f, 0.0f, -10.0f);
glTexCoord2i(20,0);
glVertex3f( -10.0f, 0.0f, 10.0f);
glTexCoord2i(20,20);
glVertex3f( 0.0f, 20.0f, 0.0f);
glTexCoord2i(0,0);
glVertex3f( -10.0f, 0.0f, 10.0f);
glTexCoord2i(20,0);
glVertex3f( 10.0f, 0.f, 10.0f );
glTexCoord2i(20,20);
glVertex3f( 0.0f, 20.0f, 0.0f);
glEnd();
glDisable(GL_TEXTURE_2D);
glPopMatrix();
//draw many tree
for(int i = -4; i < 4; i++)
for(int j=-3; j < 3; j++) {
glPushMatrix();
glTranslatef(i*10.0f, -0.5f, j * 10.0f);
drawTree(texTree0);
glPopMatrix();
}
for(int i = -10; i < 10; i++)
for(int j = 1; j < 4; j++)
{
glPushMatrix();
glTranslatef(i*3.5f, 0.0f, j*-13.0f);
drawTree(texTree1);
glPopMatrix();
}
glFlush();
}
void pressKey(int key, int xx, int yy) { //increment or decrement teta
switch (key) {
case GLUT_KEY_LEFT :
teta = -0.03f; glutPostRedisplay(); break;
case GLUT_KEY_RIGHT :
teta = 0.03f; glutPostRedisplay();break;
case GLUT_KEY_UP :
tetaY = 0.03f; glutPostRedisplay();break;
case GLUT_KEY_DOWN :
tetaY = -0.03f;glutPostRedisplay(); break;
}
}
void releaseKey(int key, int x, int y) { // restore teta
switch (key) {
case GLUT_KEY_LEFT:
teta = 0.0f;glutPostRedisplay();break;
case GLUT_KEY_RIGHT :
teta = 0.0f;glutPostRedisplay();break;
case GLUT_KEY_UP :
tetaY = 0.0f;glutPostRedisplay();break;
case GLUT_KEY_DOWN :
tetaY = 0.0f;glutPostRedisplay();break;
}
} void release(unsigned char key, int x, int y) {
//restore mov and movX
switch (key) {
case 'a':
movX = 0;break;
case 'd' :
movX = 0;break;
case 'w' :
mov = 0;break;
case 's':
mov = 0;break;
}
} void keyboard(unsigned char key, int x, int y) // increment or decrement movement along z and x axes
{
switch (key) {
case 27:
exit(0); break;
case 'w': //forwards
mov = 1; glutPostRedisplay(); break;
case 's': // backwards
mov = -1; glutPostRedisplay();break;
case 'a': // left
movX = -1;glutPostRedisplay(); break;
case 'd': //right
movX = 1;glutPostRedisplay(); break;
}
}
int main(int argc, char **argv) {
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
glutInitWindowSize(width,height);
glutInitWindowPosition(0,0);
glutCreateWindow(argv[0]);
init();
texName = loadTexture("grass.jpg");
texPyr = loadTexture("pyramid.jpg");
texTree0 = loadTexture("tree0.png");
texTree1 = loadTexture("tree1.png");
glutDisplayFunc(display);
glutReshapeFunc(reshape);
// call keyboard function
glutSpecialFunc(pressKey);
glutKeyboardFunc(keyboard);
// call keyboard release function
glutSpecialUpFunc(releaseKey);
glutKeyboardUpFunc(release);
glutMainLoop();
return 0;
}
