// Developers: dr4g0nbyt3
// Date:       April 4, 2016
// Github:     dr4g0nbyt3 
// Website:    dr4g0nbyt3.github.io 
// Email:      dr4g0nbyt3@gmail.com  
// Twitter:    @dr4g0nbyt3 
// Youtube:    dr4g0nbyt3

// A special thanks to Emerald Development making this possible. Great learning experience I have been looking for something like this for years.
// Go check out his unfinished game at http://www.emeraldkingdom.website/

#include <stdio.h>

#include <windows.h>

#include <GL/GL.h>
#include "glut.h"

int window_width = 0; // GLobal
int window_height = 0; // global

void intOpenGL() {
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
}


void drawCube(float x, float y, float z, float widthHeight) {

	glBegin(GL_QUADS);

		// Front
		glVertex3f(x - ((0.5)*widthHeight), y - ((0.5)*widthHeight), z + 0.5);
		glVertex3f(x + ((0.5)*widthHeight), y - ((0.5)*widthHeight), z + 0.5);
		glVertex3f(x + ((0.5)*widthHeight), y + ((0.5)*widthHeight), z + 0.5);
		glVertex3f(x - ((0.5)*widthHeight), y + ((0.5)*widthHeight), z + 0.5);

		// Back
		glVertex3f(x - ((0.5)*widthHeight), y + ((0.5)*widthHeight), z - 0.5);
		glVertex3f(x + ((0.5)*widthHeight), y + ((0.5)*widthHeight), z - 0.5);
		glVertex3f(x + ((0.5)*widthHeight), y - ((0.5)*widthHeight), z - 0.5);
		glVertex3f(x - ((0.5)*widthHeight), y - ((0.5)*widthHeight), z - 0.5);

		// Top
		glVertex3f(x - ((0.5)*widthHeight), y + 0.5, z + ((0.5)*widthHeight));
		glVertex3f(x + ((0.5)*widthHeight), y + 0.5, z + ((0.5)*widthHeight));
		glVertex3f(x + ((0.5)*widthHeight), y + 0.5, z - ((0.5)*widthHeight));
		glVertex3f(x - ((0.5)*widthHeight), y + 0.5, z - ((0.5)*widthHeight));

		// Bottom
		glVertex3f(x - ((0.5)*widthHeight), y - 0.5, z - ((0.5)*widthHeight));
		glVertex3f(x + ((0.5)*widthHeight), y - 0.5, z - ((0.5)*widthHeight));
		glVertex3f(x + ((0.5)*widthHeight), y - 0.5, z + ((0.5)*widthHeight));
		glVertex3f(x - ((0.5)*widthHeight), y - 0.5, z + ((0.5)*widthHeight));

		// Right
		glVertex3f(x + ((0.5)*widthHeight), y - ((0.5)*widthHeight), z + ((0.5)*widthHeight));
		glVertex3f(x + ((0.5)*widthHeight), y - ((0.5)*widthHeight), z - ((0.5)*widthHeight));
		glVertex3f(x + ((0.5)*widthHeight), y + ((0.5)*widthHeight), z - ((0.5)*widthHeight));
		glVertex3f(x + ((0.5)*widthHeight), y + ((0.5)*widthHeight), z + ((0.5)*widthHeight));
		
		// Left
		glVertex3f(x - ((0.5)*widthHeight), y + ((0.5)*widthHeight), z + ((0.5)*widthHeight));
		glVertex3f(x - ((0.5)*widthHeight), y + ((0.5)*widthHeight), z - ((0.5)*widthHeight));
		glVertex3f(x - ((0.5)*widthHeight), y - ((0.5)*widthHeight), z - ((0.5)*widthHeight));
		glVertex3f(x - ((0.5)*widthHeight), y - ((0.5)*widthHeight), z + ((0.5)*widthHeight));
	glEnd();
}

void ready3D() {
	glViewport(0,0, window_width, window_height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective( 45.0, (float)window_width / (float)window_height, 0.01f, 100.0f );
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void drawCeilingAndGround() 
{

	int size = 50;
	int size_half = size / 2;

	int ceilHeight = 4.0f;
	int floorHeight = 0.0;

	glBegin(GL_LINES); 
	{
		// Ceiling
		glColor3ub(0, 0, 255);
		for (float step = -size_half; step <= size_half; step += 0.25)
		{
			glVertex3f(0 + step, ceilHeight, size_half);
			glVertex3f(0 + step, ceilHeight, -size_half);

			glVertex3f(size_half, ceilHeight, 0 + step);
			glVertex3f(-size_half, ceilHeight, 0 + step);
		}

		for (float step = -size_half; step <= size_half; step += 0.25)
		{
			glVertex3f(0 + step, floorHeight, size_half);
			glVertex3f(0 + step, floorHeight, -size_half);

			glVertex3f(size_half, floorHeight, 0 + step);
			glVertex3f(-size_half, floorHeight, 0 + step);
		}
	}
	glEnd();
}

void Render()
{

	ready3D();
	glClearColor(0,0.4f,0.8f,1.0f);
	glClear( GL_COLOR_BUFFER_BIT );

	glPushMatrix();
	glTranslatef(0, -2.0f,0);
		glPushMatrix();
			drawCeilingAndGround();
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -1, -5);
	drawCube(0, 0, 0, 1);
	glPopMatrix();

	glutSwapBuffers();
}


void GlutMain( int val )
{

	glutPostRedisplay(); // Render()

	// 60 fps 1000/60 == ~16.6666ms.
	// WHY 60? tv monitors in america run at 60 hz anything higher wouldnt get drawn.
	// So you want a framerate divisible by 60 or in Europe 50.
	// Europe monitors have a refresh rate of 50 hz.

	glutTimerFunc(16, GlutMain, NULL);

}



void windowChangedSize(int w, int h) 
{
	printf("Window Changed Size! \n");
	window_width = w;
	window_height = h;
}

int main( int argc, char ** argv ) {

	glutInit( &argc, argv );
	// Double buffer to prevent screen tearing.
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB );

	glutInitWindowSize(1280, 720);
	glutInitWindowPosition(0, 280);

	glutCreateWindow( "MineScape v0.01" );

	intOpenGL();



	glutReshapeFunc(windowChangedSize);
	glutDisplayFunc( Render );

	glutTimerFunc( 16, GlutMain, NULL );

	glutMainLoop();
	return 0;
}