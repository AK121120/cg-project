#include<stdio.h>
#include<stdlib.h> 
#include<GL/glut.h> 

#define WINDOW_HEIGHT 500 

/*The edge data structure*/ 
typedef struct tEdge 
{ 
	int yUpper; 
	float xIntersect, dxPerScan; 
	struct tEdge * next; 
} Edge; 
typedef struct tPoint
{ 
	int x; 
	int y; 
} Point; 

int n; 
Point v[60]; 

/* Inserts edge into list in order of increasing xIntersect field. */ 
void insertEdge (Edge * list, Edge * edge) 
{ 
	Edge * p, * q = list; 
	p = q->next; 
	while (p != NULL) 
	{ 
		if (edge->xIntersect < p->xIntersect) 
			p = NULL; 
		else 
		{ 
			q = p; 
			p = p->next; 
		} 
	} 
	edge->next = q->next; 
	q->next = edge; 
} 

/* Store lower-y coordinate and inverse slope for each edge. Adjust and store upper-y coordinate for edges that are the lower member 
of a monotically increasing or decreasing pair of edges */ 

void makeEdgeRec(Point lower, Point upper, int yComp, Edge * edge, Edge * edges[]) 
{ 
//Edge *q; 
	edge->dxPerScan =(float) (upper.x - lower.x) / (upper.y - lower.y); 
	edge->xIntersect = lower.x; 
	if (upper.y < yComp)
		edge->yUpper = upper.y - 1; 
	else 
		edge->yUpper = upper.y; 
	insertEdge (edges[lower.y], edge); 
/*checking the values inserted into edge records uncomment if you want to check 
q=edges[lower.y]->next; 
while(q!=NULL) 
{ 
printf("xi=%f\n",q->xIntersect); 
q=q->next; 
}*/ 
}
 
/* For an index, return y-coordinate of next nonhorizontal line */ 
int yNext (int k, int n, Point * v) 
{ 
	int j; 
	if ((k+1) > (n-1)) 
		j = 0; 
	else 
		j = k + 1; 
	while (v[k].y == v[j].y) 
		if ((j+1) > (n-1)) 
			j = 0; 
		else 
			j++; 
	return (v[j].y); 
} 

void buildEdgeList (int n, Point * v, Edge * edges[]) 
{ 
	Edge * edge; 
	Point v1, v2; 
	int i, yPrev = v[n - 2].y; 
	v1.x = v[n-1].x; v1.y = v[n-1].y; 
	for (i=0; i<n; i++) 
	{ 
		v2 = v[i]; 
		if (v1.y != v2.y) 
		{ /* nonhorizontal line */ 
			edge = (Edge *) malloc (sizeof (Edge)); 
			if (v1.y < v2.y) /* up-going edge */ 
				makeEdgeRec (v1, v2, yNext (i, n, v), edge, edges); 
			else /* down-going edge */ 
				makeEdgeRec (v2, v1, yPrev, edge, edges); 
		} 
		yPrev = v1.y;
		v1 = v2; 
	} 
} 

void buildActiveList (int scan, Edge * active, Edge * edges[]) 
{ 
	Edge * p, * q; 
	p = edges[scan]->next; 
	while (p) 
	{ 
		q = p->next; 
		insertEdge (active, p); 
		p = q; 
	} 
} 

void fillScan (int scan, Edge * active) 
{ 
	Edge * p1, * p2; 
	int i; 
	p1 = active->next; 
	while (p1) 
	{ 
		p2 = p1->next; 
		glBegin(GL_POINTS); 
		for (i=p1->xIntersect; i<p2->xIntersect; i++) 
			glVertex2i((int) i, scan); 
		glEnd(); 
		p1 = p2->next; 
	} 
} 

void deleteAfter (Edge * q) 
{ 
	Edge * p = q->next; 
	q->next = p->next; 
	free (p); 
} 
/* Delete completed edges. Update 'xIntersect' field for others */ 
void updateActiveList (int scan, Edge * active) 
{ 
	Edge * q = active, * p = active->next; 
	while (p) 
	if (scan >= p->yUpper) 
	{ 
		p = p->next; 
		deleteAfter (q); 
	}
	else 
	{ 
		p->xIntersect = p->xIntersect + 
		p->dxPerScan;/*x=x+1/m*/ 
		q = p; 
		p = p->next; 
	} 
} 

void resortActiveList (Edge * active) 
{ 
	Edge * q, * p = active->next; 
	active->next = NULL; 
	while (p) 
	{ 
		q = p->next; 
		insertEdge (active, p); 
		p = q; 
	} 
} 

void scanFill (int n, Point * v) 
{ 
	Edge * edges[WINDOW_HEIGHT], * active; 
	int i, scan; 
	for (i=0; i<WINDOW_HEIGHT; i++) 
	{ 
		edges[i] = (Edge *) malloc (sizeof (Edge)); 
		edges[i]->next = NULL; 
	} 
	buildEdgeList (n, v, edges); 
	active = (Edge *) malloc (sizeof (Edge)); 
	active->next = NULL; 
	for (scan=0; scan<WINDOW_HEIGHT; scan++) 
	{ 
		buildActiveList (scan, active, edges); 
		

		if (active->next) 
		{ 
			fillScan (scan, active); 
			updateActiveList (scan, active); 
			resortActiveList (active); 
		} 
	} 
/* Free edge records that have been malloc'ed ... */ 
	free(active); 
}

void display() 
{ 
	int i;
	glClear(GL_COLOR_BUFFER_BIT); 
	glBegin(GL_LINE_LOOP); 
	for(i=0;i<n; i++) 
	{ 
		glVertex2i(v[i].x,v[i].y); 
	} 
	glEnd(); 
	scanFill(n,v); 
	glFlush(); 
} 

void myinit() 
{ 
	glClearColor(1.0,1.0,1.0,1.0);
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity(); 
	gluOrtho2D(0,499.0,0.0,499.0); 
	glMatrixMode(GL_MODELVIEW); 
	glColor3f(1.0,0.0,0.0);
} 

void menu(int id)
{
	if (id == 1)
		glClearColor(1, 0.5, 0, 0);
	if (id==2)
		glClearColor(0, 1, 1, 0);
	if (id==3)
		glColor3f(0, 0, 1);
	if (id==4)
		glColor3f(1, 1, 0);
	glutPostRedisplay();
}

void main(int argc, char **argv) 
{ 
	int i;
	printf("Enter the no of points\n"); 
	scanf("%d",&n); 
	printf("Enter the vertices\n"); 
	for(i=0;i<n; i++) 
		scanf("%d%d",&v[i].x,&v[i].y); 
	glutInit(&argc,argv); 
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB); 
	glutInitWindowPosition(0,0); 
	glutInitWindowSize(500,500); 
	glutCreateWindow("Scan Line Area Filling Algorithm"); 
	myinit(); 
	glutDisplayFunc(display); 
	int bgcolor=glutCreateMenu(menu);
	glutAddMenuEntry("orange",1);
	glutAddMenuEntry("cyan",2);
	int fillcolor=glutCreateMenu(menu);
	glutAddMenuEntry("blue",3);
	glutAddMenuEntry("yellow",4);
	glutCreateMenu(menu);
	glutAddSubMenu("Background",bgcolor);
	glutAddSubMenu("Fill color",fillcolor);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop(); 
}
