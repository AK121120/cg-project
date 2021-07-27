#include<stdio.h>
#include<stdbool.h>
#include<GL/glut.h>

float xmin, ymin, xmax, ymax;//window boundaries
float xvmin, yvmin, xvmax, yvmax; //viewport boundaries
float x1, y1, x2, y2;

//bit codes for the right, left, top, & bottom
const int RIGHT = 2;
const int LEFT = 1;
const int TOP = 8;
const int BOTTOM = 4;

int computeOutCode(double x, double y);

void cohenSutherlandLineClipAndDraw(double x1, double y1, double x2, double y2)
{
	int outcode1, outcode2, outcodeOut;
	double x, y;
	bool accept = false, done = false;

	outcode1 = computeOutCode(x1, y1);
	outcode2 = computeOutCode(x2, y2);
	do
	{
		if (!(outcode1 | outcode2))
		{
			accept = true;
			done = true;
		}
		else if (outcode1 & outcode2)
		{
			done = true;
		}

		else
		{
			outcodeOut = outcode1 ? outcode1 : outcode2;

			if (outcodeOut & TOP)
			{
				//point is above the clip rectangle
				x = x1 + ((x2 - x1) / (y2 - y1)) * (ymax - y1);
				y = ymax;
			}
			else if (outcodeOut & BOTTOM)
			{
				//point is below the clip rectangle
				x = x1 + ((x2 - x1) / (y2 - y1)) * (ymin - y1);
				y = ymin;
			}
			else if (outcodeOut & RIGHT)
			{
				//point is to the right of clip rectangle
				y = y1 + ((y2 - y1) / (x2 - x1)) * (xmax - x1);
				x = xmax;
			}

			else
			{
				//point is to the left of clip rectangle
				y = y1 + ((y2 - y1) / (x2 - x1)) * (xmin - x1);
				x = xmin;
			}

			if (outcodeOut == outcode1)
			{
				x1 = x;
				y1 = y;
				outcode1 = computeOutCode(x1, y1);
			}
			else
			{
				x2 = x;
				y2 = y;
				outcode2 = computeOutCode(x2, y2);
			}
		}
	} while (!done);
	if (accept)
	{
		//window to viewport mappings
		float sx = (xvmax - xvmin) / (xmax - xmin); //scale parameters
		float sy = (yvmax - yvmin) / (ymax - ymin);
		float vx1 = xvmin + (x1 - xmin) * sx;
		float vy1 = yvmin + (y1 - ymin) * sy;
		float vx2 = xvmin + (x2 - xmin) * sx;
		float vy2 = yvmin + (y2 - ymin) * sy;

		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_LINE_LOOP);
		glVertex2f(xvmin, yvmin);
		glVertex2f(xvmax, yvmin);
		glVertex2f(xvmax, yvmax);
		glVertex2f(xvmin, yvmax);
		glEnd();
		glColor3f(0.0, 0.0, 1.0);
		glBegin(GL_LINES);
		glVertex2f(vx1, vy1);
		glVertex2f(vx2, vy2);
		glEnd();
	}

}

int computeOutCode(double x, double y)
{
	int code = 0;
	if (y > ymax)//above the clip window
		code |= TOP;
	else if (y < ymin)//below the clip window
		code |= BOTTOM;
	if (x > xmax)//to the right of clip window
		code |= RIGHT;
	else if (x < xmin)//to the left of clip window
		code |= LEFT;
	return code;
}

void display()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 499.0, 0.0, 499.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glEnd();
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(xmin, ymin);
	glVertex2f(xmax, ymin);
	glVertex2f(xmax, ymax);
	glVertex2f(xmin, ymax);
	glEnd();
	cohenSutherlandLineClipAndDraw(x1, y1, x2, y2);
	glFlush();
}

int main(int argc, char** argv)
{
	printf("Enter the boundaries of window for clipping\n");
	printf("Enter xmin, ymin, xmax, ymax :\n");
	scanf("%f%f%f%f", &xmin, &ymin, &xmax, &ymax);
	printf("Enter the boundaries of view port\n");
	printf("Enter xvmin, yvmin, xvmax, yvmax :\n");
	scanf("%f%f%f%f", &xvmin, &yvmin, &xvmax, &yvmax);
	printf("Enter the vertices of line (x1,y1,x2,y2):\n");
	scanf("%f%f%f%f", &x1, &y1, &x2, &y2);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(10, 10);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Cohen Sutherland Line Clipping Algorithm");
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
