//Etapa4
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

int W_WIDTH = 500; // Tama�o incial de la ventana
int W_HEIGHT = 500;



GLfloat angle = 0.0, anglevert = 1.0;;
// actual vector representing the camera's direction
float lx = 0.0f, lz = -1.0f, ly = 0.0f;
// XZ position of the camera
float x = 0.0f, z = 5.0f, y = 1.0f;
double ratio = W_WIDTH / W_HEIGHT;
//bool dreta = true;

// Funci�n que visualiza la escena OpenGL
void Display(void)
{

	// Borramos la escena
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(x, y, z,
		x + lx, y+ly, z + lz,
		0.0f, 1.0f, 0.0f);

	glColor3f(0.9, 0.8, 0.8);

	glBegin(GL_QUADS);
	glVertex3f(-100.0, 0.0, -100.0);
	glVertex3f(-100.0, 0.0, 100.0);
	glVertex3f(100.0, 0.0, 100.0);
	glVertex3f(100.0, 0.0, -100.0);
	
	glEnd();


	
	glPushMatrix();
	glColor3f(0.2, 0.2, 0.4);
	glutSolidCube(0.8);
	glColor3f(0.0, 0.0, 0.0);
	glutWireCube(0.8);
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

	


	// Indicamos cuales son las funciones de redibujado e idle
	glutDisplayFunc(Display);
	glutReshapeFunc(reshape);
	glutIdleFunc(Idle);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);

	glEnable(GL_DEPTH_TEST);
	
	
	// El color de fondo ser� el negro (RGBA, RGB + Alpha channel)
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glOrtho(-1.0, 1.0f, -1.0, 1.0f, -1.0, 1.0f);

	// Comienza la ejecuci�n del core de GLUT
	glutMainLoop();
	return 1;
}