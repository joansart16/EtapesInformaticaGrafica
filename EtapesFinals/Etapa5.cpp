#include <iostream>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

int W_WIDTH = 500; // Tama�o incial de la ventana
int W_HEIGHT = 500;



GLfloat angle = 0.0, anglevert = -0.3;
// actual vector representing the camera's direction
float lx = 0.0f, lz = -1.0f, ly = -0.3f;
// XZ position of the camera
float x = 0.0f, z = 4.0f, y = 4.0f;
double ratio = W_WIDTH / W_HEIGHT;
//bool dreta = true;

enum DIMENSION { X, Y, Z, MAX_DIMENSION };
enum TIPO_LUZ { AMBIENTE, DIFUSA, ESPECULAR, MAX_TIPO_LUZ };
enum COMPONENTE_LUZ { R, G, B, A, MAX_COMPONENTE_LUZ };
const int numCamares = 4;
GLfloat x_array[numCamares] = {-22, -22, 22, 22};
GLfloat y_array[numCamares] = {0.5, 0.5, 0.5, 0.5};
GLfloat z_array[numCamares] = {-22, 22, 22, -22};
GLfloat lx_array[numCamares] = { 1, 1, -1, -1 };
GLfloat ly_array[numCamares] = { 0.5,0.5, 0.5, 0.5 };
GLfloat lz_array[numCamares] = { 1, -1, -1, 1 };
int cambiarCamara = 0;
bool modeFixe = false;

GLfloat  RGBAf[MAX_TIPO_LUZ][MAX_COMPONENTE_LUZ] = { { 0.2, 0.3, 0.4, 0.0},  /*Se determina la luz ambiente*/
														{ 1.0, 1.0, 1.0, 0.0},  /*Se determina la luz difusa*/
														{ 0.5, 0.5, 0.5, 0.0} },  /*Se determina la luz especular*/
	Posicion[] = { 0.0, 0.0, 0.0, 1.0 }, /*Se determina la posicion de la luz 0*/
	Direccion[MAX_DIMENSION] = { 0.0, -1.0, 0.0 },
	Especular[MAX_COMPONENTE_LUZ] = { 1.0, 1.0, 1.0, 1.0 },	/*Color especular*/
	Brillo[] = { 100.0 };	/*Brillo de la superficie de un objeto*/


GLfloat light_dir[] = { 0.0,1.0,0.0};
GLfloat light_color[] = { 1.0,1.0,1.0,1.0 };
GLfloat light_color2[] = { 0.5f, 0.5f,  0.5f, 1.0f };
GLfloat pos[] = { 1.0, 1.0, 0.0, 0.0 };
GLfloat pos1[] = { 0.0, -1.0, 0.0, 0.0 };
// Funci�n que visualiza la escena OpenGL

void dibuixarFarola() {

	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
	// Dibuixar base
	glScalef(1.0, 0.5, 1.0);
	glTranslatef(0.0f, 1.0f, 0.0f);
	glutSolidCube(1.0);
	glPopMatrix();
	// Dibuixar cos
	glColor3f(1.0f, 0.2f, 1.0f);
	glPushMatrix();
	glTranslatef(0.0f, 1.5f, 0.0f);
	glScalef(0.4, 2.5, 0.4);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.2f, 0.2f, 1.0f);
	glTranslatef(0.8, 2.9, 0.0);
	glScalef(2.0, 0.4, 0.4);
	glutSolidCube(1.0);
	glPopMatrix();
	//dibuixar bombilla
	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
	glTranslatef(1.5, 2.5, 0.0);
	
	

	glutSolidSphere(0.1f, 30, 30);



	/*Se habilita el proceso de iluminación*/
	glEnable(GL_LIGHTING);	/*Se activa el proceso de iluminación*/
	glEnable(GL_LIGHT0);		/*Se activa la luz nº 0*/
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 1.0); /*La luz se concentra un poco en el centro*/
	glLighti(GL_LIGHT0, GL_SPOT_CUTOFF, 45); /*El ángulo de apertura es de 180º*/
	glLightfv(GL_LIGHT0, GL_POSITION, Posicion);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, Direccion);
	glLightfv(GL_LIGHT0, GL_AMBIENT, RGBAf[AMBIENTE]);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, RGBAf[DIFUSA]);
	glLightfv(GL_LIGHT0, GL_SPECULAR, RGBAf[ESPECULAR]);

	glPopMatrix();
	


}



void Display(void)
{

	// Borramos la escena
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	
	
	glLoadIdentity();
	if (modeFixe) {
		gluLookAt(x_array[cambiarCamara], y_array[cambiarCamara], z_array[cambiarCamara],
		x_array[cambiarCamara] + lx_array[cambiarCamara], y_array[cambiarCamara] + ly_array[cambiarCamara], z_array[cambiarCamara] + lz_array[cambiarCamara],
		0.0f, 1.0f, 0.0f);
	}
	else {
		gluLookAt(x, y, z,
		x + lx, y + ly, z + lz,
		0.0f, 1.0f, 0.0f);
	}
	
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, light_color);
	////glLightfv(GL_LIGHT0, GL_SPECULAR, light_color);
	//glLightfv(GL_LIGHT0, GL_POSITION, pos);
	//glEnable(GL_LIGHT0);
	glColor3f(0.9, 0.2, 0.4);

	glBegin(GL_QUADS);
	glNormal3d(0, 1, 0);
	glVertex3f(-20.0, 0.0, -20.0);
	glVertex3f(-20.0, 0.0, 20.0);
	glVertex3f(20.0, 0.0, 20.0);
	glVertex3f(20.0, 0.0, -20.0);
	
	glEnd();



	//glPushMatrix();
	//glColor3f(0.2, 0.2, 0.4);
	//glutSolidCube(0.8);
	//glColor3f(0.0, 0.0, 0.0);
	//glutWireCube(0.8);
	glPushMatrix();
	dibuixarFarola();
	glPopMatrix();
	glFlush();

	glutSwapBuffers();
	




}

void processSpecialKeys(int key, int xx, int yy) {

	float fraction = 0.01f;

	switch (key) {
	case GLUT_KEY_LEFT:
		angle -= 0.05f;
		lx = sin(angle);
		lz = -cos(angle);
		break;
	case GLUT_KEY_RIGHT:
		angle += 0.1f;
		lx = sin(angle);
		lz = -cos(angle);
		break;
	case GLUT_KEY_UP:
		anglevert += 0.0005;
		ly += cos(anglevert) * fraction;
		break;
	case GLUT_KEY_DOWN:
		anglevert -= 0.0005f;
		ly -= cos(anglevert) * fraction;
		break;
	}

}
void processNormalKeys(unsigned char key, int xx, int yy) {
	float fraction = 0.1f;
	switch (key) {
	case 97:
		x += lz * fraction;
		z -= lx * fraction;
		break;
	case 100:
		x -= lz * fraction;
		z += lx * fraction;
		break;
	case 119:
		x += lx * fraction;
		z += lz * fraction;
		break;
	case 115:
		x -= lx * fraction;
		z -= lz * fraction;
		break;
	case 101://E, pujar
		y += 0.2;
		
		break;
	case 113://Q, baixar
		y -= 0.2;
		break;
	case 99://C, per cambiar el tipus de càmara
		modeFixe = !modeFixe;
		break;
	case 51://cambiar la camara
		cambiarCamara = (cambiarCamara + 1) % numCamares;
		break;
	}
	

	


}
void reshape(int w, int h) {
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0) {
		h = 1;
	}
	float ratio = w * 1.0 / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);

}

// Funci�n que se ejecuta cuando el sistema no esta ocupado
void Idle(void)
{




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
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	// Creamos la nueva ventana
	glutCreateWindow("Mi primera Ventana");

	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);


	// Indicamos cuales son las funciones de redibujado e idle
	glutDisplayFunc(Display);
	glutReshapeFunc(reshape);
	glutIdleFunc(Idle);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_LIGHT1);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);

	glEnable(GL_DEPTH_TEST);


	// El color de fondo ser� el negro (RGBA, RGB + Alpha channel)
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glOrtho(-1.0, 1.0f, -1.0, 1.0f, -1.0, 1.0f);

	// Comienza la ejecuci�n del core de GLUT
	glutMainLoop();
	return 1;
}