//Assignment4

#include<GL/glut.h>
#include<math.h>
#include "SDL/SDL.h"
int window;
int width=800,hieght=800;
//DIFINE VARIABLES FOR SPIN AND REVOLUTION
static float spin[]={0.0,0.0,0.0}; //spin angle for the sun and each planet
static float x[2][3]={{0.0,4.0,0.0},{0.0,6.0,0.0}}; //position of sun and planets
static float angle[2]={0.0,0.0};// angle for increment of position
static float rev_increment[9]={1.0,0.6}; // increment of angle for the sun and
each planet
static float spin_increment[3]={2,3,2}; // increment of spin for the sun and each
planet
//DEFINE VARIABLE FOR TEXTURES
unsigned int tex;
unsigned int tex_1;
unsigned int tex_2;
//DEFINE QUADRATIC OBJECT
GLUquadric *q0;
GLUquadric *q1;
GLUquadric *q2;
unsigned int loadTexture(const char* filename) // function that load the texture
from a BMP image
{
SDL_Surface *img = SDL_LoadBMP(filename);
unsigned int id;
glGenTextures(1,&id); // generate texture
glBindTexture(GL_TEXTURE_2D,id); //how i want to use tex
glTexImage2D(GL_TEXTURE_2D,0,img->format->BytesPerPixel,img->w,img-
>h,0,GL_BGR,GL_UNSIGNED_BYTE,img->pixels);//load texture for opengl structure
//--Set texture parameters
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
SDL_FreeSurface(img); //Frees the resources used by a previously created
SDL_Surface
return id;
}
void reshape(int w,int h)
{
glViewport(0.0,0.0,w,h);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
if(w<=h)
gluPerspective(60,h/w,1.0,20.0);
else
gluPerspective(60,w/h,1,20);
gluLookAt(0,-11,-5,0,0,0,0,1,0); //I set my own camera position for a
beautiful display
glMatrixMode(GL_MODELVIEW);
}
void revolution(float *angle) //function that calculate new position in the space
{
float ang;
ang=3.14*angle[0]/180.0;
x[0][0]=4*sin(ang);
x[0][1]=4*cos(ang);
x[0][2]=0;
ang=3.14*angle[1]/180.0;
x[1][0]=6*sin(ang);
x[1][1]=6*cos(ang);
x[1][2]=0;
}
void spinSphere(int value)
{
int i;
int k;
for (k=0;k<3;k++) //increment the spin for each object (different
between the object)
{
spin[k]+=spin_increment[k];
if(spin[k]>360.0)
spin[k]-=360.0;
}
for(i=0;i<2;i++) //increment the angle for each object
(different between the object)
{
angle[i]+=rev_increment[i];
if(angle[i]>360.0)
angle[i]-=360.0;
revolution(angle);
}
glutPostRedisplay(); //Tell GLUT that the display has
changed
glutTimerFunc(25,spinSphere, 0);
} void init() //initialization function
{
glClearColor (0.0 , 0.0 , 0.0 , 0.0) ;
glEnable(GL_LIGHTING); //activate lighting calculations.
glEnable(GL_LIGHT0); //activate the first light source.
GLfloat diffuse[]={6.0, 6.0, 6.0, 7.0}; // set light diffuse
parameters(omni-directional white light)
GLfloat pos[]={0.0, 0.0, 0.0,1.0}; // set position of
light parameters (point light)
GLfloat ambient[]={1.0,1.0,1.0,0.1}; // set ambient light
parameters
glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
glLightfv(GL_LIGHT0, GL_POSITION, pos);
glLightfv(GL_LIGHT0, GL_AMBIENT,ambient );
glShadeModel(GL_SMOOTH);
glEnable(GL_DEPTH_TEST); //elimination of the hidden parts in the
scene
}
void display_solar_system()
{
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the depth
buffer
glEnable(GL_TEXTURE_2D);
glLoadIdentity();
// draw sun
static GLfloat sunwhite[]={255.0, 255.0, 255.0};
glPushAttrib(GL_ALL_ATTRIB_BITS);
glPushMatrix(); //Save the current state of
transformations
glBindTexture(GL_TEXTURE_2D,tex); //lets you use a named texture
glEnable(GL_COLOR_MATERIAL);
glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION,sunwhite); //make the sun like
an emission object
glTranslatef(0.0,0.0,0.0); //positioning the sun at the center
glRotatef(-spin[0],0.0,0.0,1.0); // spin of the sun
q0 = gluNewQuadric(); //create quadratic
object
gluQuadricDrawStyle ( q0, GLU_FILL );
gluQuadricNormals(q0, GLU_SMOOTH); //One normal is generated for
every vertex of the quadric object
gluQuadricTexture(q0, GLU_TRUE); // texture coordinates be
generated
gluSphere(q0,1.5,200,200); // create a sphere from a quadratic
object
gluDeleteQuadric (q0);
glPopMatrix();
glPopAttrib();
//draw and rotate earth
glPushMatrix();
glBindTexture(GL_TEXTURE_2D,tex_1);
glTranslatef(x[0][0],x[0][1],x[0][2]); //position of earth
glRotatef(spin[1],0.0,0.0,1.0); // spin of earth
q1 = gluNewQuadric();
gluQuadricDrawStyle ( q1, GLU_FILL );
gluQuadricNormals(q1, GLU_SMOOTH);
gluQuadricTexture(q1, GLU_TRUE);
gluSphere(q1,0.6,200,200);
gluDeleteQuadric (q1);
glPopMatrix();
//draw and rotate mars
glPushMatrix();
glBindTexture(GL_TEXTURE_2D, tex_2);
glTranslatef(x[1][0],x[1][1],x[1][2]); //position of mars
glRotatef(spin[2],0.0,0.0,1.0); //spin of mars
q2 = gluNewQuadric();
gluQuadricDrawStyle ( q2, GLU_FILL );
gluQuadricNormals(q2, GLU_SMOOTH);
gluQuadricTexture(q2, GLU_TRUE);
gluSphere(q2,0.4,200,200);
gluDeleteQuadric ( q2 );
glPopMatrix();
glFlush();
glDisable (GL_TEXTURE_2D );
glutSwapBuffers();
}

int main(int argc,char **argv){

glutInit(&argc,argv);
glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
//---create window
glutInitWindowSize(width,hieght);
glutInitWindowPosition(0,0);
window=glutCreateWindow("Solar system");
//---load texture---
tex= loadTexture("sun.bmp");
tex_1= loadTexture("earth.bmp");
tex_2 = loadTexture("mars.bmp");
//---initialization---
init();
//---callback function
glutDisplayFunc(display_solar_system);
glutReshapeFunc(reshape);
//---timer functon to update the display
glutTimerFunc(25,spinSphere, 0);
glutMainLoop();
}
