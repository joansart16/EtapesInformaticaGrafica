#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

#define M_PI 3.14159265358979323846
int W_WIDTH = 500; // Tama�o incial de la ventana
int W_HEIGHT = 500;

int origenX = 0;
int origenY = 0;


// Funci�n que visualiza la escena OpenGL
void Display(void)
{

	// Borramos la escena
	//glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT /*| GL_DEPTH_BUFFER_BIT*/);
	glMatrixMode(GL_PROJECTION);
	glFrustum(-1, 1, -1, 1, 1, 1000);

	glPushMatrix();
	
	
	glTranslatef(0.0, 0.0, -3.0);
	glScalef(2, 2, 2);
	glRotatef(50.0, 1.0, 1.0, 0.0);
	glColor3f(0.22, 0.6, 0.3);
	//glutSolidTorus(0.2, 0.5, 50, 50);
	glutSolidCube(0.8);
	glColor3f(0.0, 0.0, 0.0);
	glutWireCube(0.8);
	/*glBegin(GL_QUADS);
	glVertex3f(-0.8, -0.8, 1.2);
	glVertex3f(-0.8, 0.8, 1.2);
	glVertex3f(0.8, 0.8, 1.2);
	glVertex3f(0.8, -0.8, 1.2);
	glEnd();*/



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
