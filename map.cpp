#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

#define PI (2*acos(0.0))
#define SLICE 20

struct Point {
	double x,y;
};

struct Junction {
	double x,y,r;
} junctions[100];

struct Road {
	struct Point st,en;
} roads[100];

int n,m,camH;
struct Point cam;

void drawFilledCircle(double cx,double cy,double r) {
	int i;
	struct Point pts[SLICE+1];

	for(i=0;i<=SLICE;i++) {
		pts[i].x=r*cos(((double)i/(double)SLICE)*2*PI);
		pts[i].y=r*sin(((double)i/(double)SLICE)*2*PI);
	}

	glColor3f(1.0, 1.0, 1.0);
	for(i=0;i<SLICE;i++) {
		glBegin(GL_TRIANGLES); {
			glVertex3f(cx,cy,0);
			glVertex3f(cx+pts[i].x,cy+pts[i].y,0);
			glVertex3f(cx+pts[i+1].x,cy+pts[i+1].y,0);
		} glEnd();
	}	
}

void drawCircle(double cx,double cy,double r) {
	int i;
	struct Point pts[SLICE+1];

	for(i=0;i<=SLICE;i++) {
		pts[i].x=r*cos(((double)i/(double)SLICE)*2*PI);
		pts[i].y=r*sin(((double)i/(double)SLICE)*2*PI);
	}

	glColor3f(1.0, 1.0, 1.0);
	for(i=0;i<SLICE;i++) {
		glBegin(GL_LINES); {
			glVertex3f(cx+pts[i].x,cy+pts[i].y,0);
			glVertex3f(cx+pts[i+1].x,cy+pts[i+1].y,0);
		} glEnd();
	}	
}

void drawRoad(int id) {
	if(id&1) glColor3f(1.0, 0.0, 0.0);
	else glColor3f(0.0, 1.0, 0.0);
	
	glBegin(GL_LINES); {
		glVertex3f(roads[id].st.x,roads[id].st.y,0);
		glVertex3f(roads[id].en.x,roads[id].en.y,0);
	} glEnd();

	//drawFilledCircle(roads[id].en.x,roads[id].en.y,1);
}

void keyboardListener(unsigned char key, int x,int y) {
	switch(key){
		default:
			break;
	}
}

void specialKeyListener(int key, int x,int y) {
	switch(key) {
		case GLUT_KEY_DOWN:		//down arrow key
			cam.y-=5;
			break;
		case GLUT_KEY_UP:		// up arrow key
			cam.y+=5;
			break;

		case GLUT_KEY_RIGHT:
			cam.x+=5;
			break;
		case GLUT_KEY_LEFT:
			cam.x-=5;
			break;

		case GLUT_KEY_PAGE_UP:
			camH-=5;
			break;
		case GLUT_KEY_PAGE_DOWN:
			camH+=5;
			break;
		default:
			break;
	}
}

void mouseListener(int button, int state, int x, int y) {	//x, y is the x-y of the screen (2D)
	switch(button) {
		default:
			break;
	}
}

void display() {
	int i;
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

	//Camera
	gluLookAt(cam.x,cam.y,camH, cam.x,cam.y,0, 0,1,0);
	
	//again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);


	/****************************
	/ Add your objects from here
	****************************/
	//add objects

	//for(i=0;i<n;i++)
		//drawCircle(junctions[i].x,junctions[i].y,junctions[i].r);
	for(i=0;i<m;i++)
		drawRoad(i);
	glutSwapBuffers();
}

void animate() {
	//codes for any changes in Models, Camera
	glutPostRedisplay();
}

void init() {
	int i,x;

	//codes for initialization
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

	cam.x=0;
	cam.y=0;
	camH=200;

	freopen("glInput.txt","r",stdin);
	scanf("%d",&n);
	for(i=0;i<n;i++)
		scanf("%lf %lf %lf",&junctions[i].x,&junctions[i].y,&junctions[i].r);
	scanf("%d",&m);
	for(i=0;i<m;i++)
		scanf("%d %lf %lf %lf %lf",&x,&roads[i].st.x,&roads[i].st.y,&roads[i].en.x,&roads[i].en.y);
}

int main(int argc, char **argv) {
	glutInit(&argc,argv);
	glutInitWindowSize(1080, 960);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color

	glutCreateWindow("Map");

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
