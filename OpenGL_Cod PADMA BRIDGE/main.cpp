#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <windows.h>
#include <glut.h>
#define pi (2*acos(0.0))

double cameraHeight;
double cameraAngle;
int drawgrid;
int drawaxes;
double angle;
struct point
{
	double x,y,z;
};
void drawAxes()
{
	if(drawaxes==1)
	{
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_LINES);{
			glVertex3f( 100,0,0);
			glVertex3f(-100,0,0);

			glVertex3f(0,-100,0);
			glVertex3f(0, 100,0);

			glVertex3f(0,0, 100);
			glVertex3f(0,0,-100);
		}glEnd();
	}
}


void drawGrid()
{
	int i;
	if(drawgrid==1)
	{
		glColor3f(0.6, 0.6, 0.6);	//grey
		glBegin(GL_LINES);{
			for(i=-8;i<=8;i++){

				if(i==0)
					continue;	//SKIP the MAIN axes

				//lines parallel to Y-axis
				glVertex3f(i*10, -90, 0);
				glVertex3f(i*10,  90, 0);

				//lines parallel to X-axis
				glVertex3f(-90, i*10, 0);
				glVertex3f( 90, i*10, 0);
				//lines parallal to z axis

				//glVertex3f( 0, 90, i*10);
				//glVertex3f(0, -90, i*10);


			}
		}glEnd();
	}
}

void drawSquare(double a)
{
    //glColor3f(1.0,0.0,0.0);
	glBegin(GL_QUADS);{
		glVertex3f( a, a,0);
		glVertex3f( a,-a,0);
		glVertex3f(-a,-a,0);
		glVertex3f(-a, a,0);
	}glEnd();
}

//draws a cube of side length 2a
void drawCube(double a)
{
    glBegin(GL_QUADS);{

        //glColor3f(1,0,1);
		glVertex3f( a, a, a);
		glVertex3f( a,-a, a);
		glVertex3f(-a,-a, a);
		glVertex3f(-a, a, a);

        //glColor3f(1,0,1);
		glVertex3f( a, a,-a);
		glVertex3f( a,-a,-a);
		glVertex3f(-a,-a,-a);
		glVertex3f(-a, a,-a);

        //glColor3f(1,1,0);
		glVertex3f( a, a, a);
		glVertex3f( a, a,-a);
		glVertex3f( a,-a,-a);
		glVertex3f( a,-a, a);

		//glColor3f(1,0,0);
		glVertex3f(-a, a, a);
		glVertex3f(-a, a,-a);
		glVertex3f(-a,-a,-a);
		glVertex3f(-a,-a, a);

		//glColor3f(0,1,0);
		glVertex3f( a, a, a);
		glVertex3f( a, a,-a);
		glVertex3f(-a, a,-a);
		glVertex3f(-a, a, a);

		//glColor3f(0,0,1);
		glVertex3f( a,-a, a);
		glVertex3f( a,-a,-a);
		glVertex3f(-a,-a,-a);
		glVertex3f(-a,-a, a);
	}glEnd();
}

//draws a cylinder of given radius and height
void drawCylinder(double radius,double height,int segments)
{
    int i;
    double shade;
    struct point points[100];
    //generate points
    for(i=0;i<=segments;i++)
    {
        points[i].x=radius*cos(((double)i/(double)segments)*2*pi);
        points[i].y=radius*sin(((double)i/(double)segments)*2*pi);
    }
    //draw quads using generated points
    for(i=0;i<segments;i++)
    {

        glBegin(GL_QUADS);
        {
			glVertex3f(points[i].x,points[i].y,height/2);
			glVertex3f(points[i+1].x,points[i+1].y,height/2);
			glVertex3f(points[i].x,points[i].y,-height/2);
			glVertex3f(points[i+1].x,points[i+1].y,-height/2);
        }
        glEnd();
    }
}
void drawCircle(double radius,int segments)
{
    int i;
    struct point points[100];
    glColor3f(.7,0.7,0.7);
   //generate points
    for(i=0;i<=segments;i++)
    {
        points[i].x=radius*cos(((double)i/(double)segments)*2*pi);
        points[i].y=radius*sin(((double)i/(double)segments)*2*pi);
    }
    //draw segments using generated points
    for(i=0;i<segments;i++)
    {
        glBegin(GL_LINES);
        {
			glVertex3f(points[i].x,points[i].y,0);
			glVertex3f(points[i+1].x,points[i+1].y,0);
        }
        glEnd();
    }
     //generate points
    for(i=0;i<=segments;i++)
    {
        points[i].x=radius*cos(((double)i/(double)segments)*2*pi);
        points[i].y=radius*sin(((double)i/(double)segments)*2*pi);
    }
    //draw segments using generated points
    for(i=0;i<segments;i++)
    {
        glBegin(GL_QUADS);
        {
			glVertex3f(points[i].x,points[i].y,90);
			glVertex3f(points[i+1].x,points[i+1].y,90);
			glVertex3f(points[i].x,points[i].y,-90);
			glVertex3f(points[i+1].x,points[i+1].y,-90);
        }
        glEnd();
    }
}
void drawCone(double radius,double height,int segments)
{
    int i;
    double shade;
    struct point points[100];
    //generate points
    for(i=0;i<=segments;i++)
    {
        points[i].x=radius*cos(((double)i/(double)segments)*2*pi);
        points[i].y=radius*sin(((double)i/(double)segments)*2*pi);
    }
    //draw triangles using generated points
    for(i=0;i<segments;i++)
    {
        //create shading effect
        if(i<segments/2)shade=2*(double)i/(double)segments;
        else shade=2*(1.0-(double)i/(double)segments);
        glColor3f(shade,shade,shade);

        glBegin(GL_TRIANGLES);
        {
            glVertex3f(0,0,height);
			glVertex3f(points[i].x,points[i].y,0);
			glVertex3f(points[i+1].x,points[i+1].y,0);
        }
        glEnd();
    }
}
void drawSphere(double radius,int slices,int stacks)
{
	struct point points[100][100];
	int i,j;
	double h,r;
	//generate points
	for(i=0;i<=stacks;i++)
	{
		h=radius*sin(((double)i/(double)stacks)*(pi/2));
		r=radius*cos(((double)i/(double)stacks)*(pi/2));
		for(j=0;j<=slices;j++)
		{
			points[i][j].x=r*cos(((double)j/(double)slices)*2*pi);
			points[i][j].y=r*sin(((double)j/(double)slices)*2*pi);
			points[i][j].z=h;
		}
	}
	//draw quads using generated points
	for(i=0;i<stacks;i++)
	{
        glColor3f((double)i/(double)stacks,(double)i/(double)stacks,(double)i/(double)stacks);
		for(j=0;j<slices;j++)
		{
			glBegin(GL_QUADS);{
			    //upper hemisphere
				glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);
                //lower hemisphere
                glVertex3f(points[i][j].x,points[i][j].y,-points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,-points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,-points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,-points[i+1][j].z);
			}glEnd();
		}
	}
}
double tx= 0;

void Bridge()
{

/**pillar of the bridze**/
    glPushMatrix();
   {
    glColor3f(0.5f, 0.3f, 0.0f);
    glRotated(90,1,0,0);
    glTranslatef(-140,80,130);
    glScalef(6,5,20);
    drawCylinder(5,10,20);

    }
   glPopMatrix();

    glPushMatrix();
   {
    glColor3f(0.5f, 0.3f, 0.0f);
    glRotated(90,1,0,0);
    glTranslatef(-140,-80,130);
    glScalef(6,5,20);
    drawCylinder(5,10,20);

    }
   glPopMatrix();

    glPushMatrix();
   {
    glColor3f(0.5f, 0.3f, 0.0f);
    glRotated(90,1,0,0);
    glTranslatef(140,80,130);
    glScalef(6,5,20);
    drawCylinder(5,10,20);

    }
   glPopMatrix();

     glPushMatrix();
   {
    glColor3f(0.5f, 0.3f, 0.0f);
    glRotated(90,1,0,0);
    glTranslatef(140,-80,130);
    glScalef(6,5,20);
    drawCylinder(5,10,20);

    }
   glPopMatrix();

    glPushMatrix();
   {
    glColor3f(0.5f, 0.3f, 0.0f);
    glTranslatef(-140,-10,0);
    glScalef(6,5,18);
    drawCube(5);

    }
   glPopMatrix();

    glPushMatrix();
   {
    glColor3f(0.5f, 0.3f, 0.0f);
    glTranslatef(140,-10,0);
    glScalef(6,5,18);
    drawCube(5);

    }
   glPopMatrix();


/**train track**/
    glPushMatrix();
   {
    glColor3f(1,1,0);
    glTranslatef(-100,20,45);
    glScalef(100,.7,2);
    drawCube(5);

    }
   glPopMatrix();

   glPushMatrix();
   {
    glColor3f(1,1,0);
    glTranslatef(-100,20,-45);
    glScalef(100,.7,2);
    drawCube(5);

    }
   glPopMatrix();

    glPushMatrix();
   {
    glColor3f(0.3,0,0);
    glTranslatef(380,20,0);
    glScalef(1,1,8);
    drawCube(5);

    }
   glPopMatrix();

    glPushMatrix();
   {
    glColor3f(0.3,0,0);
    glTranslatef(340,20,0);
    glScalef(1,1,8);
    drawCube(5);

    }
   glPopMatrix();

    glPushMatrix();
   {
    glColor3f(0.3,0,0);
    glTranslatef(300,20,0);
    glScalef(1,1,8);
    drawCube(5);

    }
   glPopMatrix();

     glPushMatrix();
   {
    glColor3f(0.3,0,0);
    glTranslatef(260,20,0);
    glScalef(1,1,8);
    drawCube(5);

    }
   glPopMatrix();

     glPushMatrix();
   {
    glColor3f(0.3,0,0);
    glTranslatef(220,20,0);
    glScalef(1,1,8);
    drawCube(5);

    }
   glPopMatrix();

    glPushMatrix();
   {
    glColor3f(0.3,0,0);
    glTranslatef(180,20,0);
    glScalef(1,1,8);
    drawCube(5);

    }
   glPopMatrix();
   glPushMatrix();
   {
    glColor3f(0.3,0,0);
    glTranslatef(140,20,0);
    glScalef(1,1,8);
    drawCube(5);

    }
   glPopMatrix();

    glPushMatrix();
   {
    glColor3f(0.3,0,0);
    glTranslatef(100,20,0);
    glScalef(1,1,8);
    drawCube(5);

    }
   glPopMatrix();

    glPushMatrix();
   {
    glColor3f(0.3,0,0);
    glTranslatef(60,20,0);
    glScalef(1,1,8);
    drawCube(5);

    }
   glPopMatrix();

    glPushMatrix();
   {
    glColor3f(0.3,0,0);
    glTranslatef(20,20,0);
    glScalef(1,1,8);
    drawCube(5);

    }
   glPopMatrix();

    glPushMatrix();
   {
    glColor3f(0.3,0,0);
    glTranslatef(-20,20,0);
    glScalef(1,1,8);
    drawCube(5);

    }
   glPopMatrix();

    glPushMatrix();
   {
    glColor3f(0.3,0,0);
    glTranslatef(-60,20,0);
    glScalef(1,1,8);
    drawCube(5);

    }
   glPopMatrix();

    glPushMatrix();
   {
    glColor3f(0.3,0,0);
    glTranslatef(-100,20,0);
    glScalef(1,1,8);
    drawCube(5);

    }
   glPopMatrix();

    glPushMatrix();
   {
    glColor3f(0.3,0,0);
    glTranslatef(-140,20,0);
    glScalef(1,1,8);
    drawCube(5);

    }
   glPopMatrix();

    glPushMatrix();
   {
    glColor3f(0.3,0,0);
    glTranslatef(-180,20,0);
    glScalef(1,1,8);
    drawCube(5);

    }
   glPopMatrix();

   glPushMatrix();
   {
    glColor3f(0.3,0,0);
    glTranslatef(-220,20,0);
    glScalef(1,1,8);
    drawCube(5);

    }
   glPopMatrix();

   glPushMatrix();
   {
    glColor3f(0.3,0,0);
    glTranslatef(-260,20,0);
    glScalef(1,1,8);
    drawCube(5);

    }
   glPopMatrix();
   glPushMatrix();
   {
    glColor3f(0.3,0,0);
    glTranslatef(-300,20,0);
    glScalef(1,1,8);
    drawCube(5);

    }
   glPopMatrix();

    glPushMatrix();
   {
    glColor3f(0.3,0,0);
    glTranslatef(-340,20,0);
    glScalef(1,1,8);
    drawCube(5);

    }
   glPopMatrix();

    glPushMatrix();
   {
    glColor3f(0.3,0,0);
    glTranslatef(-380,20,0);
    glScalef(1,1,8);
    drawCube(5);

    }
   glPopMatrix();

    glPushMatrix();
   {
    glColor3f(0.3,0,0);
    glTranslatef(-420,20,0);
    glScalef(1,1,8);
    drawCube(5);

    }
   glPopMatrix();



/**Bridge Structure*/

   glPushMatrix();
   {
    glColor3f(0.5, 0.0, 0.5);
    glTranslatef(-30,20,60);
    glScalef(50,3,.5);
    drawCube(5);

    }
   glPopMatrix();

   glPushMatrix();
   {
    glColor3f(0.5, 0.0, 0.5);
    glTranslatef(-30,20,-60);
    glScalef(50,3,.5);
    drawCube(5);

    }
   glPopMatrix();
//1st
    glPushMatrix();
   {

    glColor3f(1,0,0);
    glTranslatef(-230,65,59);
    glRotatef(-50,0,0,1);
    glScalef(1,10,.5);
    drawCube(5);

    }
   glPopMatrix();

    glPushMatrix();
   {

    glColor3f(1,0,0);
    glTranslatef(-150,65,59);
    glRotatef(50,0,0,1);
    glScalef(1,10,.5);
    drawCube(5);

    }
   glPopMatrix();

    glPushMatrix();
   {

    glColor3f(1,0,0);
    glTranslatef(-80,65,59);
    glRotatef(-50,0,0,1);
    glScalef(1,10,.5);
    drawCube(5);

    }
   glPopMatrix();

     glPushMatrix();
   {

    glColor3f(1,0,0);
    glTranslatef(0,65,59);
    glRotatef(50,0,0,1);
    glScalef(1,10,.5);
    drawCube(5);

    }
   glPopMatrix();

    glPushMatrix();
   {

    glColor3f(1,0,0);
    glTranslatef(80,65,59);
    glRotatef(-50,0,0,1);
    glScalef(1,10,.5);
    drawCube(5);

    }
   glPopMatrix();

    glPushMatrix();
   {

    glColor3f(1,0,0);
    glTranslatef(80,65,-59);
    glRotatef(-50,0,0,1);
    glScalef(1,10,.5);
    drawCube(5);

    }
   glPopMatrix();

    glPushMatrix();
   {

    glColor3f(1,0,0);
    glTranslatef(160,65,59);
    glRotatef(50,0,0,1);
    glScalef(1,10,.5);
    drawCube(5);

    }
   glPopMatrix();

    glPushMatrix();
   {

    glColor3f(1,0,0);
    glTranslatef(160,65,-59);
    glRotatef(50,0,0,1);
    glScalef(1,10,.5);
    drawCube(5);

    }
   glPopMatrix();


    glPushMatrix();
   {

    glColor3f(1,0,0);
    glTranslatef(-230,65,-59);
    glRotatef(-50,0,0,1);
    glScalef(1,10,.5);
    drawCube(5);

    }
   glPopMatrix();

   glPushMatrix();
   {

    glColor3f(1,0,0);
    glTranslatef(-150,65,-59);
    glRotatef(50,0,0,1);
    glScalef(1,10,.5);
    drawCube(5);

    }
   glPopMatrix();

    glPushMatrix();
   {

    glColor3f(1,0,0);
    glTranslatef(-80,65,-59);
    glRotatef(-50,0,0,1);
    glScalef(1,10,.5);
    drawCube(5);

    }
   glPopMatrix();

   glPushMatrix();
   {

    glColor3f(1,0,0);
    glTranslatef(0,65,-59);
    glRotatef(50,0,0,1);
    glScalef(1,10,.5);
    drawCube(5);

    }
   glPopMatrix();


   //2ndset

    glPushMatrix();
   {

    glColor3f(1,0,0);
    glTranslatef(-33,96,59);
    glScalef(32.5,1,.5);
    drawCube(5);

    }
   glPopMatrix();

   glPushMatrix();
   {

    glColor3f(1,0,0);
    glTranslatef(-33,96,-59);
    glScalef(32.5,1,.5);
    drawCube(5);

    }
   glPopMatrix();

/**Train**/

    glPushMatrix();
   {
       glTranslatef(tx,0,0);

    glPushMatrix();
   {
    glColor3f(1,1,1);
    glTranslatef(0,40,0);
    glScalef(15,1,8.5);
    drawCube(5);

    }
   glPopMatrix();

   glPushMatrix();
   {
    glColor3f(1,0,0);
    glTranslatef(45,38,50);
    glScalef(3,3,8);
    glRotatef(2*angle,0,0,1);
    drawCylinder(5,2,10);

    }
   glPopMatrix();

   glPushMatrix();
   {
    glColor3f(1,0,0);
    glTranslatef(45,38,-50);
    glScalef(3,3,8);
    glRotatef(2*angle,0,0,1);
    drawCylinder(5,2,10);

    }
   glPopMatrix();

   glPushMatrix();
   {
    glColor3f(1,0,0);
    glTranslatef(-45,38,-50);
    glScalef(3,3,8);
    glRotatef(2*angle,0,0,1);
    drawCylinder(5,2,10);

    }
   glPopMatrix();

   glPushMatrix();
   {
    glColor3f(1,0,0);
    glTranslatef(-45,38,50);
    glScalef(3,3,8);
    glRotatef(2*angle,0,0,1);
    drawCylinder(5,2,10);

    }
   glPopMatrix();



    glPushMatrix();
   {
    glColor3f(0.4, 0.4, 0.4);
    glTranslatef(40,65,0);
    glScalef(6,4.5,8);
    drawCube(5);

    }
   glPopMatrix();

    glPushMatrix();
   {
    glColor3f(0.4, 0.4, 0.4);
    glTranslatef(-30,55,0);
    glScalef(10,2,5);
    drawCube(5);

    }
   glPopMatrix();

     glPushMatrix();
   {
    glColor3f(0.8, 0.8, 0.8);
    glTranslatef(-70,80,0);
    glRotated(90,1,0,0);
    glScalef(2,2,5);
    drawCylinder(3,5,20);

    }
   glPopMatrix();

    glPushMatrix();
   {
    glColor3f(0.8, 0.8, 0.8);
    glTranslatef(-70,98,0);
    glRotated(90,1,0,0);
    glScalef(4,2,2);
    drawCylinder(3,5,20);

    }
   glPopMatrix();

      glPushMatrix();
   {
    glColor3f(0.8, 0.8, 0.8);
    glTranslatef(-35,75,0);
    glRotated(90,1,0,0);
    glScalef(2,2,3);
    drawCylinder(3,5,20);

    }
   glPopMatrix();

    glPushMatrix();
   {
    glColor3f(0.8, 0.8, 0.8);
    glTranslatef(-35,88,0);
    glRotated(90,1,0,0);
    glScalef(3,2,2);
    drawCylinder(3,5,20);

    }
   glPopMatrix();

   glPushMatrix();
   {
    glColor3f(0,0,0);
    glTranslatef(10,75,0);
    glScalef(.2,1.6,7);
    drawCube(5);

    }
   glPopMatrix();

    glPushMatrix();
   {
    glColor3f(0,0,0);
    glTranslatef(40,75,40);
    glScalef(4.5,2,.5);
    drawCube(5);

    }
   glPopMatrix();

   glPushMatrix();
   {
    glColor3f(0,0,0);
    glTranslatef(40,75,-40);
    glScalef(4.5,2,.5);
    drawCube(5);

    }
   glPopMatrix();

/**link**/

   glPushMatrix();
   {
    glColor3f(1,0,0);
    glTranslatef(80,40,0);
    glScalef(1.5,.5,.5);
    drawCube(5);

    }
   glPopMatrix();

   glPushMatrix();
   {
    glColor3f(1,0,0);
    glTranslatef(95,40,0);
    glScalef(1.5,2,1);
    drawCube(5);

    }
   glPopMatrix();

   glPushMatrix();
   {
    glColor3f(1,0,0);
    glTranslatef(110,40,0);
    glScalef(1.5,.5,.5);
    drawCube(5);

    }
   glPopMatrix();
/**2nd bogi**/
    glPushMatrix();
   {
    glColor3f(1,1,1);
    glTranslatef(190,40,0);
    glScalef(15,1,8.5);
    drawCube(5);

    }
   glPopMatrix();

    glPushMatrix();
   {
    glColor3f(1,0,0);

    glTranslatef(240,38,50);
    glScalef(3,3,8);
    glRotatef(2*angle,0,0,1);
    drawCylinder(5,2,10);

    }
   glPopMatrix();

   glPushMatrix();
   {
    glColor3f(1,0,0);
    glTranslatef(240,38,-50);
    glScalef(3,3,8);
    glRotatef(2*angle,0,0,1);
    drawCylinder(5,2,10);

    }
   glPopMatrix();

   glPushMatrix();
   {
    glColor3f(1,0,0);
    glTranslatef(140,38,-50);
    glScalef(3,3,8);
    glRotatef(2*angle,0,0,1);
    drawCylinder(5,2,10);

    }
   glPopMatrix();

   glPushMatrix();
   {
    glColor3f(1,0,0);
    glTranslatef(140,38,50);
    glScalef(3,3,8);
    glRotatef(2*angle,0,0,1);
    drawCylinder(5,2,10);

    }
   glPopMatrix();

    glPushMatrix();
   {
    glColor3f(0.5f, 0.0f, 0.1f);
    glTranslatef(190,65,0);
    glScalef(14,4.5,8.3);
    drawCube(5);

    }
   glPopMatrix();


    glPushMatrix();
   {
    glColor3f(0,0,0);
    glTranslatef(165,75,40);
    glScalef(1,1.5,.5);
    drawCube(5);

    }
   glPopMatrix();

   glPushMatrix();
   {
    glColor3f(0,0,0);
    glTranslatef(165,75,-40);
    glScalef(1,1.5,.5);
    drawCube(5);

    }
   glPopMatrix();

   glPushMatrix();
   {
    glColor3f(0,0,0);
    glTranslatef(188,75,40);
    glScalef(1,1.5,.5);
    drawCube(5);

    }
   glPopMatrix();

   glPushMatrix();
   {
    glColor3f(0,0,0);
    glTranslatef(188,75,-40);
    glScalef(1,1.5,.5);
    drawCube(5);

    }
   glPopMatrix();

   glPushMatrix();
   {
    glColor3f(0,0,0);
    glTranslatef(210,75,40);
    glScalef(1,1.5,.5);
    drawCube(5);

    }
   glPopMatrix();

    glPushMatrix();
   {
    glColor3f(0,0,0);
    glTranslatef(210,75,-40);
    glScalef(1,1.5,.5);
    drawCube(5);

    }
   glPopMatrix();

    glPushMatrix();
   {
    glColor3f(0,0,0);
    glTranslatef(230,63,40);
    glScalef(1.5,3.5,.5);
    drawCube(5);

    }
   glPopMatrix();

   glPushMatrix();
   {
    glColor3f(0,0,0);
    glTranslatef(230,63,-40);
    glScalef(1.5,3.5,.5);
    drawCube(5);

    }
   glPopMatrix();



    glPushMatrix();
   {
    glColor3f(0,0,0);
    glTranslatef(140,63,40);
    glScalef(1.5,3.5,.5);
    drawCube(5);

    }
   glPopMatrix();

   glPushMatrix();
   {
    glColor3f(0,0,0);
    glTranslatef(140,63,-40);
    glScalef(1.5,3.5,.5);
    drawCube(5);

    }
   glPopMatrix();

   }
   glPopMatrix();


}
void river()
{
     glPushMatrix();
   {
   glTranslatef(0,-200,-200);
    glScalef(40,5,100);
    glColor3f(0,0,1);
    drawCube(5);
     }
   glPopMatrix();

    glPushMatrix();
   {
   glTranslatef(280,-200,-200);
    glScalef(15,5,100);
    glColor3f(0,1,0);
    drawCube(5);
     }
   glPopMatrix();

    glPushMatrix();
   {
   glTranslatef(-280,-200,-200);
    glScalef(15,5,100);
    glColor3f(0,1,0);
    drawCube(5);
     }
   glPopMatrix();

}


void keyboardListener(unsigned char key, int x,int y){
	switch(key){

		case '1':
			drawgrid=1-drawgrid;
			break;

		default:
			break;
	}
}


void specialKeyListener(int key, int x,int y){
	switch(key){
		case GLUT_KEY_DOWN:		//down arrow key
			cameraHeight -= 3.0;
			break;
		case GLUT_KEY_UP:		// up arrow key
			cameraHeight += 3.0;
			break;

		case GLUT_KEY_RIGHT:
			cameraAngle += 0.03;
			break;
		case GLUT_KEY_LEFT:
			cameraAngle -= 0.03;
			break;

		case GLUT_KEY_PAGE_UP:
			break;
		case GLUT_KEY_PAGE_DOWN:
			break;

		case GLUT_KEY_INSERT:
			break;

		case GLUT_KEY_HOME:
			break;
		case GLUT_KEY_END:
			break;

		default:
			break;
	}
}
void mouseListener(int button, int state, int x, int y){	//x, y is the x-y of the screen (2D)
	switch(button){
		case GLUT_LEFT_BUTTON:
			if(state == GLUT_DOWN){		// 2 times?? in ONE click? -- solution is checking DOWN or UP
				drawaxes=1-drawaxes;
			}
			break;

		case GLUT_RIGHT_BUTTON:
			//........
			break;

		case GLUT_MIDDLE_BUTTON:
			//........
			break;

		default:
			break;
	}
}
void display(){
	//clear the display
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0,0,0,0);	//color black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/********************
	/ set-up camera here
	********************/
	//load the correct matrix -- MODEL-VIEW matrix
	glMatrixMode(GL_MODELVIEW);

	//initialize the matrix
	glLoadIdentity();

	//now give three info
	//1. where is the camera (viewer)?
	//2. where is the camera looking?
	//3. Which direction is the camera's UP direction?

	//gluLookAt(100,100,100,	0,0,0,	0,0,1);
	//gluLookAt(200*cos(cameraAngle), 200*sin(cameraAngle), cameraHeight,		0,0,0,		0,0,1);
	gluLookAt(400,200,400,	0,0,0,	0,1,0);


	//again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);


	/****************************
	/ Add your objects from here
	****************************/
	//add objects

	drawAxes();
	drawGrid();

    glColor3f(1,0,0);
    //car();
    Bridge();
    river();

    //drawSquare(10);
    //drawSS();
    //drawCircle(30,24);
    //drawCone(20,50,24);
	//drawSphere(30,24,20);
	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}
void animate(){

    //tx+=0.01;
    tx-=((2*pi*20)/360)*.1;
    if(tx<-180)
    {
        tx=180;
    }
    angle+=0.05;
    //angle+=0.01;
    //codes for any changes in Models, Camera
	glutPostRedisplay();
}
void init(){
	//codes for initialization
	//drawgrid=1;
	drawaxes=1;
	cameraHeight=100.0;
	cameraAngle=1.0;
	angle=0;

	//clear the screen
	glClearColor(0,0,0,0);

	/************************
	/ set-up projection here
	************************/
	//load the PROJECTION matrix
	glMatrixMode(GL_PROJECTION);

	//initialize the matrix
	glLoadIdentity();

	//give PERSPECTIVE parameters
	gluPerspective(80,	1,	1,	1000.0);
	//field of view in the Y (vertically)
	//aspect ratio that determines the field of view in the X direction (horizontally)
	//near distance
	//far distance
}

int main(int argc, char **argv){
	glutInit(&argc,argv);
	glutInitWindowSize(650, 650);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color

	glutCreateWindow("My OpenGL Program");

	init();

	glEnable(GL_DEPTH_TEST);	//enable Depth Testing

	glutDisplayFunc(display);	//display callback function
	glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)

	glutKeyboardFunc(keyboardListener);
	glutSpecialFunc(specialKeyListener);
	glutMouseFunc(mouseListener);

	glutMainLoop();		//The main loop of OpenGL

	return 0;
}
