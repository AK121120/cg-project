#include<stdio.h>
#include<GL/glut.h>
#include<string.h>
int j=0;
void init()
{
	glClearColor(1,1,1,0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,1000,0,800);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glBegin(GL_QUADS);
	
		glColor3f(0.8,0.9,1.0);//sky
		glVertex2f(0,400);
		glVertex2f(0,800);
		glColor3f(1,0.9,0.6);
		glVertex2f(1000,800);
		glColor3f(0.8,0.9,1.0);
		glVertex2f(1000,400);
		
		for(int i=0;i<50;i++){
			j=j+i*0.8;
			glColor3f(0,0,0);//sky
			glVertex2f(0+i,0+j);
			glVertex2f(0+i,20+j);
			glVertex2f(20+i,20+j);
			glVertex2f(20+i,0+j);
		}
	glEnd();

	glFlush();
}
void main(int argc, char *argv[])
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowPosition(10,10);
	glutInitWindowSize(1200,800);
	glutCreateWindow("Anantha krishna G.K 4SF18CS011 Perspective View");
	init();
	glutDisplayFunc(display);
	//glutTimerFunc(0, Timer, 0);
	glEnable(GL_DEPTH_TEST);
	//glutKeyboardFunc(keys);
	glutMainLoop();
}
