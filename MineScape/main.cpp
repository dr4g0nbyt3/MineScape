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


void drawSquare( float x, float y, float widthHeight ) {
	glBegin( GL_QUADS );

		glColor3ub(0, 0, 255);
			glVertex3f( x - ((0.5) * widthHeight), y - ((0.5) * widthHeight), 0 );
			glVertex3f( x + ((0.5) * widthHeight), y - ((0.5) * widthHeight), 0 );
			glVertex3f( x + ((0.5) * widthHeight), y + ((0.5) * widthHeight), 0 );
			glVertex3f( x - ((0.5) * widthHeight), y + ((0.5) * widthHeight), 0 );

	glEnd();
}

void Render()
{

	static int anim = 0;
	anim++;

	anim = ( anim > 200 ) ? -200 : anim;

	float animF = anim / 200.0f;

	glClear( GL_COLOR_BUFFER_BIT );

		glPushMatrix();
			glScalef( animF, animF, 0 );
			drawSquare( 0, 0, 0.5 );
		glPopMatrix();

	glBegin( GL_LINES );

		glColor3ub( 0, 0, 255 );
			glVertex3f( -1, 0, 0 ); 
			glVertex3f( 1, 0, 0 );

			glVertex3f( 0, -1, 0 ); 
			glVertex3f( 0, 1, 0 );
	glEnd();

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


int main( int argc, char ** argv ) {

	glutInit( &argc, argv );

	// Double buffer to prevent screen tearing.
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB );

	glutCreateWindow( "MineScape v0.01" );

	glutDisplayFunc( Render );

	glutTimerFunc( 16, GlutMain, NULL );

	glutMainLoop();
	return 0;
}