#include <glut.h>
#include <math.h>

void init(void)
{
	GLfloat mat_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_position[] = { 0.0, 0.0, 10.0, 1.0 };
	GLfloat lm_ambient[] = { 0.2, 0.2, 0.2, 1.0 };


	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 50.0);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lm_ambient);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT);

	//	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClearColor(0, 0, 1, 1);
	glClearAccum(0.0, 0.0, 0.0, 0.0);
}

void displayObjects(void)
{
	GLfloat torus_diffuse[] = { 0.7, 0.7, 0.0, 1.0 };
	GLfloat cube_diffuse[] = { 0.0, 0.7, 0.7, 1.0 };
	GLfloat sphere_diffuse[] = { 0.7, 0.0, 0.7, 1.0 };
	GLfloat octa_diffuse[] = { 0.7, 0.4, 0.4, 1.0 };
	GLfloat black_diffuse[] = { 0.0, 0.0, 0.0, 0.0 };

	glPushMatrix();
	//glRotatef(30.0, 1.0, 0.0, 0.0);

	glPushMatrix();
	//glTranslatef(-0.80, 0.35, 0.0);
	//glRotatef(100.0, 1.0, 0.0, 0.0);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, torus_diffuse);


	for (int i = 0; i < 20; i++) {

		glutSolidSphere(0.10, 15, 15);

		GLUquadricObj* quadratic;
		quadratic = gluNewQuadric();
		glRotatef(40.0, 0, 1.0, 0.0);
		gluCylinder(quadratic, 0.05f, 0.05f, 0.4f, 32, 32);

		glTranslatef(0, 0, 0.4);
		glutSolidSphere(0.10, 15, 15);
		glTranslatef(0, 0, -0.4);

		glTranslatef(-0.1, 0.150, 0);

	}





	glPopMatrix();
}

#define ACSIZE	8

void display(void)
{
	GLint viewport[4];
	int jitter;

	glGetIntegerv(GL_VIEWPORT, viewport);

	glClear(GL_ACCUM_BUFFER_BIT);
	for (jitter = 0; jitter < ACSIZE; jitter++) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPushMatrix();
		/*	Note that 4.5 is the distance in world space between
		 *	left and right and bottom and top.
		 *	This formula converts fractional pixel movement to
		 *	world coordinates.
		 */

		displayObjects();
		glPopMatrix();
		glAccum(GL_ACCUM, 1.0 / ACSIZE);
	}
	glAccum(GL_RETURN, 1.0);
	glFlush();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-3.25, 3.25, -1.25 * h / w, 4.25 * h / w, -2.0, 2.0);
	else
		glOrtho(-3.25, 3.25, -1.25 * h / w, 4.25 * h / w, -2.0, 2.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}



void renderScene(void)
{
	glRotatef(1.0, 0.0, 60.0, .0);
	glutPostRedisplay();
}

/*  Main Loop
 *  Be certain to request an accumulation buffer.
 */
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB
		| GLUT_ACCUM | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutIdleFunc(renderScene);

	glutMainLoop();
	return 0;
}
