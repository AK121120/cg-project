#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>

//Declaring Coordinate points (x1,y1) && (x2,y2)
int x1, y11, x2, y2, cases;
//y11 because y1 is already declared in some other program

//Function prototyping
void display();
void init();
void bresenhams(int, int, int, int);


//int argc, char** argv are values taken from command prompt 
void main(int argc, char** argv)
{
//Initializing Glut
	glutInit(&argc, argv);
	printf("Menu:\n1. Positive Slope\n2.Negative Slope\n3. Undefined Slope\n4. Zero Slope\n5. Exit\nEnter your choice below:\n");
		scanf("%d",&cases);
		switch(cases)
		{
		 	case 1: printf("Thank you for choosing positive slope\n");
		 			printf("Enter x1,y1 values less than x2,y2\n");
		 			scanf("%d%d%d%d", &x1, &y11, &x2, &y2);
					//Creating an Window & Changed Window Name
		 			break;
		 	case 2: printf("Thank you for choosing negative slope\n");
		 			printf("Enter x1 value greater than x2 or y1 value greater than y2\n");
		 			scanf("%d%d%d%d", &x1, &y11, &x2, &y2);
		 			break;
		 	case 3: printf("Thank you for choosing undefined slope\n");
		 			printf("Enter only x1,y1 and y2 coordinates we will do the next :-D\n");
		 			scanf("%d%d%d", &x1, &y11, &y2);
		 			x2 = x1;
		 			break;
		 	case 4: printf("Thank you for choosing zero slope\n");
		 			printf("Enter only x1,y1 and x2 coordinates we will do the next :-D\n");
		 			scanf("%d%d%d", &x1, &y11, &x2);
		 			y2 = y11;
		 			break;
		 	case 5: printf("Thank you for experimenting, Good Bye, See you soon :-D\n");
		 			exit(0);
		 	default: printf("Enter a valid option\n");
		 }
	
	glutCreateWindow("Bresenhams Line Drawing By Vineet Nayak S 4SF18CS180");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
}

void init()
{
//glMatrixMode() specifies which matrix is the current matrix
//GL_PROJECTION - Applies subsequent matrix operations to the projection matrix stack.
	glMatrixMode(GL_PROJECTION);
//glLoadIdentity replaces the current matrix with the identity matrix. It is semantically equivalent to calling glLoadMatrix with the identity matrix. 1 0 0 0 0 1 0 0 0 0 1 
	glLoadIdentity();
	gluOrtho2D(-500,500,-500,500);
	glMatrixMode(GL_MODELVIEW);
}

void display()
{
//Changed screen color
	glClearColor(0,1,1,0);
	glClear(GL_COLOR_BUFFER_BIT);
//Changed line color
	glColor3f(1,1,1);
	bresenhams(x1,y11,x2,y2);
	glFlush();
}

void plotline(int x, int y)
{
//Increased point size
	glPointSize(3.0);
	glBegin(GL_POINTS);
		glVertex2f(x,y);
	glEnd();
}

void bresenhams(int x1, int y11, int x2, int y2)
{
	int dx, dy, pk, xinc, yinc, x, y, i;		
	dx = x2-x1;
	dy = y2-y11;
	x = x1;
	y = y11;
	
	plotline(x,y);
	
	if(dx > 0)
		xinc = 1;
	else
		xinc = -1;
	if (dy > 0)
		yinc = 1;
	else
		yinc = -1;
	
	if(fabs(dx)>fabs(dy))
	{
		pk = 2*fabs(dy) - fabs(dx);
		for(i = 0; i < fabs(dx); i++)
		{
			if(pk>0)
			{
				pk = pk + 2 * fabs(dy) - 2 * fabs(dx);
				y += yinc;
			}
			else
			{
				pk = pk + 2 * fabs(dy);
				y = y;
			}
			x += xinc;
			plotline(x,y);
		}
	}
	else
	{
		pk = 2*fabs(dx) - fabs(dy);
		for(i=0;i<fabs(dy);i++)
		{
			if(pk>0)
			{
				pk += 2*fabs(dx) - 2*fabs(dy);
				x += xinc;
			}
			else
			{
				pk += 2 * fabs(dx);
				x = x;
			}
			y += yinc;
			plotline(x,y);
		}
	}	
}
