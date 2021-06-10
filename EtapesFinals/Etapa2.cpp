// Etapa1.cpp
// Fichero principal 
////////////////////////////////////////////////////

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

#define M_PI 3.14159265358979323846
int W_WIDTH = 500; // Tama�o incial de la ventana
int W_HEIGHT = 500;
GLfloat xi = 0.0;
GLfloat yi = 0.0;
GLint numLados = 7;
GLint escalar = 1;
GLdouble puntosx[13];
GLdouble puntosy[13];
GLdouble angulo = 0;


GLfloat fAngulo = 0.0; // Variable que indica el �ngulo de rotaci�n de los ejes.
GLfloat fAngulo2 = 0.0;
GLfloat fAngulo3 = 0.0;
GLfloat fEscalar = 0.3;
GLfloat fEscalar2;

GLfloat fDreta = -0.5;

GLfloat fMovX = -2.0;
GLfloat fMovY = 0.0;

int direccio = 0; //0 dreta-abaix, 1 dreta-adalt, 2 esquerra adalt, 3 esquerra abaix

bool dreta = true;
bool dreta2 = false;
bool creixer = false;
bool creixer2 = false;

int origenX = 0;
int origenY = 0;

GLfloat angle = 0.0;
//bool dreta = true;

// Funci�n que visualiza la escena OpenGL
void Display(void)
{

	// Borramos la escena
	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();

	
	////TRIANGLE ROTANT ENMIG
	//// Rotamos las proximas primitivas
	//glRotatef(fAngulo3, 0.0f, 0.0f, 1.0f);
	//// Creamos a continuaci�n dibujamos los tres poligonos
	//glBegin(GL_POLYGON);
	//glColor3f(1.0f, 1.0f, 1.0f);
	//glVertex3f(0.0f, 0.0f, 0.0f);
	//glColor3f(0.0f, 1.0f, 0.0f);
	//glVertex3f(1.0f, 0.0f, 0.0f);
	//glColor3f(0.0f, 1.0f, 0.0f);
	//glVertex3f(-0.5f, 0.866f, 0.0f);
	//glEnd();

	//glBegin(GL_POLYGON);
	//glColor3f(1.0f, 1.0f, 1.0f);
	//glVertex3f(0.0f, 0.0f, 0.0f);
	//glColor3f(1.0f, 0.0f, 0.0f);
	//glVertex3f(1.0f, 0.0f, 0.0f);
	//glColor3f(0.0f, 0.0f, 1.0f);
	//glVertex3f(-0.5f, -0.866f, 0.0f);
	//glEnd();

	//glBegin(GL_POLYGON);
	//glColor3f(1.0f, 1.0f, 1.0f);
	//glVertex3f(0.0f, 0.0f, 0.0f);
	//glColor3f(0.0f, 1.0f, 1.0f);
	//glVertex3f(-0.5f, 0.866f, 0.0f);
	//glColor3f(0.0f, 0.0f, 1.0f);
	//glVertex3f(-0.5f, -0.866f, 0.0f);
	//glEnd();


////PRIMERA PART, Q ZONES I UN POLÍGON A CADA ZONA
//
//	glMatrixMode(GL_MODELVIEW);
//	//desrotam perque el quadrat no es mogui
//	//glRotatef(fAngulo, 0.0f, 0.0f, -1.0f);
//	//Quadrat adalt esquerra
//
//	glClear(GL_COLOR_BUFFER_BIT);
//
//	glPushMatrix();
//
//
//	//Triangle adalt esquerra
//	glPushMatrix();
//	glLoadIdentity();
//
//	glTranslatef(-0.5f, 0.75f, 0.0f);
//	glRotatef(30.0f, 0.0f, 0.0f, 1.0f);
//	glScalef(0.75, 0.25, 0.0);
//	
//	glTranslatef(0.5f, -0.75f, 0.0f);
//	glBegin(GL_POLYGON);
//
//	glColor3f(1.0f, 1.0f, 0.0f);
//	glVertex3f(-0.5f, 0.75f, 0.0f);
//	glVertex3f(-0.75f, 0.25f, 0.0f);
//	glVertex3f(-0.25f, 0.25f, 0.0f);
//
//
//	glEnd();
//
//	glPopMatrix();
//
//
//
//	//Heptagon adalt esquerra
//
//	int numLados = 7;
//	double grados = (360 / numLados);
//	double aux = grados;
//	
//
//
//	for (int i = 0; i < numLados; i++) {
//		puntosx[i] = ((2 * (cos((M_PI * grados) / 180))) + xi);
//		puntosy[i] = ((2 * (sin((M_PI * grados) / 180))) + yi);
//
//		grados = grados + aux;
//
//	}
//	
//	glPushMatrix();
//	glLoadIdentity();
//	glRotatef(20.0f, 0.0, 0.0, 1.0);
//	glScalef(0.1, 0.1, 0);
//	
//	
//	glTranslatef(5.0f, 5.0f, 0.0);
//
//	//glTranslatef(fMovX, fMovY, 0.0);
//	//glRotatef(fAngulo, 0.0f, 0.0f, 1.0f);
//	glBegin(GL_POLYGON);
//	glColor3f(1.0, 0.5, 0.0);
//	for (int i = 0; i < numLados; i++) {
//		glVertex3f(puntosx[i], puntosy[i], 1.0);
//		
//	}
//	
//	glEnd();
//	glPopMatrix();
//
//
//	
//
//	glPushMatrix();
//
//
//	//Rectangle abaix esquerra
//	glPushMatrix();
//	glLoadIdentity();
//	
//	glScalef(0.5, 0.25, 0.0);
//	glRotatef(30.0f, 0.0f, 0.0f, 1.0f);
//	
//
//	glTranslatef(-2.5f, -2.0f, 0.0f);
//	glBegin(GL_POLYGON);
//
//	glColor3f(0.2f, 0.6f, 0.5f);
//	glVertex3f(0.0f, 0.0f, 0.0f);
//	glVertex3f(1.0f, 0.0f, 0.0f);
//	glVertex3f(1.0f, 1.0f, 0.0f);
//	glVertex3f(0.0f, 1.0f, 0.0f);
//
//
//	glEnd();
//
//	glPopMatrix();
//
//	//Triangle abaix dreta
//	glPushMatrix();
//	glLoadIdentity();
//	glRotatef(30.0f, 0.0f, 0.0f, 1.0f);
//	glScalef(0.5, 0.5, 0.0);
//	
//
//
//	glTranslatef(0.0f, -2.0f, 0.0f);
//	glBegin(GL_POLYGON);
//
//	glColor3f(0.8f, 0.2f, 0.4f);
//	glVertex3f(0.0f, 0.0f, 0.0f);
//	glVertex3f(1.0f, 0.0f, 0.0f);
//	glVertex3f(1.0f, 1.0f, 0.0f);
//
//
//
//	glEnd();
//
//	glPopMatrix();
	////FINALITZACIÓ  4 QUADRANTS



	


	//PÈNDUL

	//Primer pal
	glPushMatrix();
	
	glLoadIdentity();

	glTranslatef(0.0, 1.0, 0.0);
	glRotatef(fAngulo, 0.0, 0.0, 1.0);

	glBegin(GL_POLYGON);

	glColor3f(0.2f, 0.5f, 0.2f);
	glVertex3f(-0.02, 0.0, 0.0);
	glVertex3f(0.02, 0.0, 0.0);
	glVertex3f(0.02, -0.4, 0.0);
	glVertex3f(-0.02, -0.4, 0.0);


	glEnd();

	const  double pi2 = 6.28318530718;
	static double radius = 0.05;

	const double delta_theta = pi2 / 20;

	double xcenter=0;
	double ycenter=0;

	double x, y;

	double theta = 0.0;

	glColor3f(1.0, 0.0, 0.0);
	glTranslatef(0.0, -0.4, 0.0);

	glBegin(GL_POLYGON);

	while (theta <= pi2) {

		x = xcenter + radius * sin(theta);

		y = ycenter + radius * cos(theta);

		glVertex2f(x, y);

		theta += delta_theta;

	};

	glEnd();


	//Segon pal
	glTranslatef(0.0, 0.4, 0.0);
	glTranslatef(0.0f, -0.37f, 0.0f);
	glRotatef(fAngulo2, 0.0, 0.0, 1.0);

	glBegin(GL_POLYGON);

	glColor3f(0.6f, 0.2f, 0.2f);
	glVertex3f(-0.02, 0.0, 0.0);
	glVertex3f(0.02, 0.0, 0.0);
	glVertex3f(0.02, -0.4, 0.0);
	glVertex3f(-0.02, -0.4, 0.0);


	glEnd();

	glColor3f(1.0, 1.0, 0.0);
	glTranslatef(0.0, -0.4, 0.0);

	glBegin(GL_POLYGON);

	xcenter = 0;
	ycenter = 0;

	x = 0;
	y = 0;

	theta = 0.0;

	while (theta <= pi2) {

		x = xcenter + radius * sin(theta);

		y = ycenter + radius * cos(theta);

		glVertex2f(x, y);

		theta += delta_theta;

	};

	glEnd();

	glPopMatrix();


	

	glPopMatrix();


	glFlush();

	glutSwapBuffers();


}

void reshape(int width, int height) {
	if (width > height) {
		glViewport(width / 2 - height / 2, 0, height, height);
		W_WIDTH = height;
		W_HEIGHT = height;
		origenX = width / 2 - height / 2;
		origenY = 0;


	}
	else {
		glViewport(0, height / 2 - width / 2, width, width);
		W_WIDTH = width;
		W_HEIGHT = width;
		origenX = 0;
		origenY = height / 2 - width / 2;
	}


}

// Funci�n que se ejecuta cuando el sistema no esta ocupado
void Idle(void)
{
	
	if (dreta) {
		fAngulo += 0.03;
		if (fAngulo > 30.0) {
			dreta = false;
		}
	}
	else {
		fAngulo -= 0.03;
		if (fAngulo < -30.0) {
			dreta = true;
		}
	}

	if (dreta2) {
		fAngulo2 += 0.025;
		if (fAngulo2 > 35.0) {
			dreta2 = false;
		}
	}
	else {
		fAngulo2 -= 0.025;
		if (fAngulo2 < -35.0) {
			dreta2 = true;
		}
	}
	fAngulo3 += 0.3;	
	
	// Indicamos que es necesario repintar la pantalla
	glutPostRedisplay();
}

// Funci�n principal
int main(int argc, char** argv)
{
	// Inicializamos la librer�a GLUT
	glutInit(&argc, argv);

	// Indicamos como ha de ser la nueva ventana
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(W_WIDTH, W_HEIGHT);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

	// Creamos la nueva ventana
	glutCreateWindow("Mi primera Ventana");

	glutReshapeFunc(reshape);


	// Indicamos cuales son las funciones de redibujado e idle
	glutDisplayFunc(Display);
	glutIdleFunc(Idle);

	// El color de fondo ser� el negro (RGBA, RGB + Alpha channel)
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glOrtho(-1.0, 1.0f, -1.0, 1.0f, -1.0, 1.0f);

	// Comienza la ejecuci�n del core de GLUT
	glutMainLoop();
	return 0;
}