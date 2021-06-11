/*
===============================================================================
Pràctica Final Informàtica Gràfica: Grua
Autors: Joan Sart i Carles Serrano
Data: 16/06/21
===============================================================================
*/
#include <stdio.h>
#include <iostream>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "TextureLoader.h"
#define PI 3.14159265358979323846

using namespace std;
int W_WIDTH = 500;
int W_HEIGHT = 500;
//Llum_____________________
//Components de la llum blanca, que és la que emprarem
GLfloat luz_blanca_ambiente[] = {0.2, 0.2, 0.2, 1.0 };
GLfloat luz_blanca_difusa[] = {0.8, 0.8, 0.8, 1.0 };
GLfloat luz_blanca_especular[] = {0.5, 0.5, 0.5, 1.0 };
//Direcció de les dues llums que emprarem
GLfloat luz_direccion_0[] = {20, 0.0, 20.0, 1.0 };
GLfloat luz_direccion_1[] = {-20.0, 0.0, -20.0, 0.0 };
bool llum1 =false;
bool llum2 = false;
//Boira_____________________
void boira();
float boiraV = 80;
//GRUA______________________
void grua();
int TAMANY_GRUA = 5;
int POS_GRUA = -10;
// YGHJ valor de les tecles moviment de la grua
float movVertical = 0.0f, movHoritzontal = 0.0f;
float movBolla = 0.0f;
//TEXTURA___________________
unsigned int alturaImgTerra;
unsigned int ampladaImgTerra;
unsigned int alturaImgBP;
unsigned int ampladaImgBP;
unsigned int alturaImgParet;
unsigned int ampladaImgParet;
unsigned char* texture;
unsigned char* textureParet;
unsigned char* textureParet2;
//CÀMERA____________________
GLfloat angle = 0.0, anglevert = 1.0;
//Direcció de la càmera
float lx = 0.0f, lz = -1.0f, ly = -1.0f;
//Posició de la càmera
float x = 1.0f, z = 10.0f, y = 40.0f;

//Càmera fixa
const int numCamares = 5;
GLfloat x_array[numCamares] = {-22, -22, 22, 22, 24};
GLfloat y_array[numCamares] = {0.5, 0.5, 0.5, 0.5, 12};
GLfloat z_array[numCamares] = {-22, 22, 22, -22, -24};
GLfloat lx_array[numCamares] = { 1, 1, -1, -1, -1};
GLfloat ly_array[numCamares] = { 0.5,0.5, 0.5, 0.5, 0.0 };
GLfloat lz_array[numCamares] = { 1, -1, -1, 1, 1 };
int cambiarCamara = 0;
bool modeFixe = false;

double ratio = W_WIDTH / W_HEIGHT;
GLfloat angObserv = 0.0;

//Funció que crea la boira
void boira(void) {
    glEnable(GL_FOG);
    glFogi(GL_FOG_MODE, GL_LINEAR);
    glFogf(GL_FOG_DENSITY, 0.0000002);
    glFogf(GL_FOG_START, 1);
    glFogf(GL_FOG_END, boiraV);
    float color[] = {0.7843137f, 0.8117647f, 0.8039215f, 0.0f};
    glFogfv(GL_FOG_COLOR, color);
}

//Funció que s'encarrega de dibuixar les parets i el terra
void dibuixarParets(void){
    //Habilitam les textures
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, alturaImgTerra, ampladaImgTerra, 0,
        GL_BGR_EXT, GL_UNSIGNED_BYTE, texture);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glEnable(GL_TEXTURE_2D);
    //Cream el terra que tendrà la textura
    //anomenada texturaTerra
    glBegin(GL_QUADS);
    glNormal3f(0.0,0.0,1.0);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-25.0, 0.0, -25.0);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-25.0, 0.0, 25.0);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(25.0, 0.0, 25.0);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(25.0, 0.0, -25.0);
    glEnd();
    //Cream 3 parets que tindran una textura de herbes
    //anomenada texturaParet
    glTexImage2D(GL_TEXTURE_2D, 0, 3, alturaImgParet, ampladaImgParet, 0,
        GL_BGR_EXT, GL_UNSIGNED_BYTE, textureParet2);
    glBegin(GL_QUADS);
    glNormal3f(0.0, 0.0, 1.0);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(-25.0, 0.0, -25.0);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-25.0, 0.0, 25.0);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-25.0, 25.0, 25.0);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(-25.0, 25.0, -25.0);
    glEnd();
    
    glBegin(GL_QUADS);
    glNormal3f(0.0, 0.0, 1.0);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(-25.0, 0.0, 25.0);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(25.0, 0.0, 25.0);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(25.0, 25.0, 25.0);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(-25.0, 25.0, 25.0);
    glEnd();

    glBegin(GL_QUADS);
    glNormal3f(0.0, 0.0, 1.0);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(25.0, 0.0, 25.0);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(25.0, 0.0, -25.0);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(25.0, 25.0, -25.0);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(25.0, 25.0, 25.0);
    glEnd();
    //Cream la darrera paret que tindrà
    //com a textura el logo del grup musical Blues Productions
    glTexImage2D(GL_TEXTURE_2D, 0, 3, alturaImgBP, ampladaImgBP, 0,
        GL_BGR_EXT, GL_UNSIGNED_BYTE, textureParet);
    glBegin(GL_QUADS);
    glNormal3f(0.0, 0.0, 1.0);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(25.0, 0.0, -25.0);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-25.0, 0.0, -25.0);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-25.0, 25.0, -25.0);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(25.0, 25.0, -25.0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}
GLfloat vertices[][3] =
{
    {-1.0,-1.0,-1.0},   //v[0]
    {1.0,-1.0,-1.0},    //v[1]
    {1.0,1.0,-1.0},     //v[2]
    {-1.0,1.0,-1.0},    //v[3]
    {-1.0,-1.0,1.0},    //v[4]
    {1.0,-1.0,1.0},     //v[5]
    {1.0,1.0,1.0},      //v[6]  
    {-1.0,1.0,1.0}      //v[7]
};


void polygon(int a, int b, int c, int d)
{
    glBegin(GL_POLYGON);
    glVertex3fv(vertices[a]);
    glVertex3fv(vertices[b]);
    glVertex3fv(vertices[c]);
    glVertex3fv(vertices[d]);
    glEnd();
}
//Funció que s'encarrega de contruïr un cub
void cub()
{
    glScalef(0.5, 0.5, 0.5);
    //Cara posterior
    glNormal3f(0.0, 0.0, -1.0);
    polygon(0, 1, 2, 3);

    //Cara superior
    glNormal3f(0.0, 1.0, 0.0);
    polygon(2, 3, 7, 6);

    //Cara esquerra
    glNormal3f(-1.0, 0.0, 0.0);
    polygon(3, 7, 4, 0);

    //Cara dreta
    glNormal3f(1.0, 0.0, 0.0);
    polygon(5, 1, 2, 6);

    //Cara frontal
    glNormal3f(0.0, 0.0, 1.0);
    polygon(4, 5, 6, 7);

    //Cara part baixa
    glNormal3f(0.0, -1.0, 0.0);
    polygon(4, 5, 1, 0);
}

//Funció que s'encarrega de contruïr un cilindre
void cilindre()
{
    double alt, ang, radi;
    static GLUquadric* quad;
    float i;
    alt = radi = 1;
    quad = gluNewQuadric();
    gluCylinder(quad, radi, radi, alt, 100, 100);

    //Tapes pel cilindre
    glPushMatrix();
    glNormal3f(0.0, 0.0, -1.0);
    glBegin(GL_POLYGON);
    for (i = 0; i < 100; i++)
    {
        ang = i * 2 * PI / 100;
        glVertex2f(cos(ang) * radi, sin(ang) * radi);
    }
    glEnd();

    glTranslatef(0.0, 0.0, 1.0);
    glNormal3f(0.0, 0.0, 1.0);

    glBegin(GL_POLYGON);
    for (i = 0; i < 100; i++)
    {
        float ang = i * 2.0 * PI / 100;
        glVertex2f(cos(ang) * radi, sin(ang) * radi);
    }
    glEnd();
    glPopMatrix();
}
//Funció que s'encarregarà de construïr tota la grua
void grua()
{
    glColor3f(1.0f, 0.2f, 0.2f);
    //Base de la grua. Té forma de cub
    glPushMatrix();
    glScalef(2.0, 0.5, 2.0);
    cub();
    glPopMatrix();
    glRotatef(0.0, 0.0, 1.0, 0.0);

    //Base cilindrica encima de la base cilindrica
    glColor3f(1.0f, 0.5f, 0.5f);
    glPushMatrix();
    glRotatef(-90, 1.0, 0.0, 0.0);
    glScalef(0.5, 0.5, 0.5);
    cilindre();
    glPopMatrix();

    //Columna principal de la grua
    glColor3f(1.0f, 0.2f, 0.2f);
    glPushMatrix();
    glRotatef(-90, 1.0, 0.0, 0.0);
    glScalef(0.2, 0.2, 5.0);
    cilindre();
    glPopMatrix();

    //Tope cilindric
    glColor3f(1.0f, 0.5f, 0.5f);
    glPushMatrix();
    glRotatef(0, 1.0, 0.0, 0.0);
    glTranslatef(0.0, 4.75, -0.35);
    glScalef(0.05, 0.05, 0.7);
    cilindre();
    glPopMatrix();
        
    //Cilindre que uneix la columna central amb el braç de la grua
    glColor3f(1.0f, 0.5f, 0.5f);
    glPushMatrix();
    glRotatef(movHoritzontal, 0, 1, 0);
    glTranslatef(0.0, 2.75 + movVertical, -0.25);
    glScalef(0.4, 0.4, 0.5);
    cilindre();
    glPopMatrix();
       
    //Braç de la grua
    glColor3f(1.0f, 0.2f, 0.2f);
    glPushMatrix();
    glRotatef(movHoritzontal, 0, 1, 0);
    glTranslatef(2, 2.75 + movVertical, 0); 
    glScalef(4.0, 0.3, 0.15);
    cub();
    glPopMatrix();

    //Cilindre que conecta el braç amb el pal de la esfera
    glColor3f(1.0f, 0.5f, 0.5f);
    glPushMatrix();
    glRotatef(movHoritzontal, 0, 1, 0);
    glTranslatef(4.0+movBolla, 2.75 + movVertical, -0.0375);
    glScalef(0.2, 0.2, 0.075);
    cilindre();
    glPopMatrix();

    //Pal que uneix el cilindre del braç amb la esfera
    glColor3f(1.0f, 0.2f, 0.2f);
    glPushMatrix();
    glRotatef(movHoritzontal, 0, 1, 0);
    glTranslatef(4.0+movBolla, 1.75 + movVertical, 0.0);
    glScalef(0.05, 2, 0.075);
    cub();
    glPopMatrix();
            
    //Esfera
    glColor3f(1.0f, 0.5f, 0.5f);
    glPushMatrix();
    glRotatef(movHoritzontal, 0, 1, 0);
    glTranslatef(4.0+movBolla, 0.95 + movVertical, 0.0);
    glutSolidSphere(0.3, 100.0, 100.0);
    glPopMatrix();
}

//Funció que s'encarrega de la il·luminació de l'escenari
//Hem emprat la mateixa iluminació per que no és distorsioni el color dels elements
void iluminacio() {
    //Indicam les components de la primera llum
    glLightfv(GL_LIGHT0, GL_AMBIENT, luz_blanca_ambiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luz_blanca_difusa);
    glLightfv(GL_LIGHT0, GL_SPECULAR, luz_blanca_especular);
    glLightfv(GL_LIGHT0, GL_POSITION, luz_direccion_0);
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 1.0);
    glLighti(GL_LIGHT0, GL_SPOT_CUTOFF, 45);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, luz_direccion_0);
    //Cream la segona llum que emprarem
    glLightfv(GL_LIGHT1, GL_AMBIENT, luz_blanca_ambiente);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, luz_blanca_difusa);
    glLightfv(GL_LIGHT1, GL_SPECULAR, luz_blanca_especular);
    glLightfv(GL_LIGHT1, GL_POSITION, luz_direccion_1);
    glEnable(GL_LIGHTING);
    //Miram si les llum estan actives o no ho estan
    if (llum1) {
        glEnable(GL_LIGHT0);
    }
    else {
        glDisable(GL_LIGHT0);
    }
    if (llum2) {
        glEnable(GL_LIGHT1);
    }
    else {
        glDisable(GL_LIGHT1);
    }
}
//Mètode que pinta la pantalla
void Display(void)
{
    // Borram l'escena
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glLoadIdentity();
    //Look at per poder moure'ns per l'escena.
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

    //Il·luminació
    glColor3f(0.9, 0.8, 0.8);
    iluminacio();
    //Parets
    dibuixarParets();
    //Grua
    glPushMatrix();
    glTranslatef(POS_GRUA, 0.0, 0.0);
    glScalef(TAMANY_GRUA, TAMANY_GRUA, TAMANY_GRUA);
    grua();
    glPopMatrix();
    //Boira
    boira();
    glPopMatrix();
    glFlush();
    glutSwapBuffers();
}
//Aquest Mètode l'empram per capturar les fletxes del teclat
void processSpecialKeys(int key, int xx, int yy) {
    //La fracció que canviarem la horientació
    float fraction = 0.1f;

    switch (key) {
    case GLUT_KEY_LEFT:
        angle -= 0.01f;
        lx = sin(angle);
        lz = -cos(angle);
        break;
    case GLUT_KEY_RIGHT:
        angle += 0.01f;
        lx = sin(angle);
        lz = -cos(angle);
        break;
    case GLUT_KEY_UP:
		anglevert += 0.0005;
		ly += cos(anglevert)*fraction;
		break;
	case GLUT_KEY_DOWN:
		anglevert -= 0.0005f;
		ly -= cos(anglevert)*fraction;
		break;
	
    }
}
void processNormalKeys(unsigned char key, int xx, int yy) {
    float fraction = 0.5f;
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
    //Cas de la lletra del teclat "y" que serveix per 
    //pujar el braç de la grua
    case 121:
        if (movVertical < 1.5) {
            movVertical = movVertical + 0.02;
        }
        break;
    //Cas de la lletra del teclat "h" que serveix per 
    //pujar el braç de la grua
    case 104:
        if (movVertical > 0) {
            movVertical = movVertical - 0.02;
        }
        break;
    //Cas de la lletra del teclat "g" que serveix per 
    //girar el braç de la grua
    case 103:
        if (movHoritzontal < 90) {
            movHoritzontal = movHoritzontal + 1;
        }
        break;
    //Cas de la lletra del teclat "j" que serveix per 
    //girar el braç de la grua
    case 106:
        if (movHoritzontal > -90) {
            movHoritzontal = movHoritzontal - 1;
        }
        break;
    //Cas de la lletra del teclat "f" que serveix per 
    //baixar l'altura de la boira
    case 102:
        if (boiraV>2) {
            boiraV = boiraV - 2;
        }
        break;
    //Cas de la lletra del teclat "r" que serveix per 
    //baixar l'altura de la boira
    case 114:
        boiraV = boiraV + 2;
        break;
    //Cas de la lletra del teclat "1" que serveix per 
    //apagar i encendre
    case 49:
        llum1 = !llum1;
        break;
    //Cas de la lletra del teclat "2" que serveix per 
    //apagar i encendre
    case 50:
        llum2 = !llum2;
        break;
    //Cas de la lletra del teclat "o" que serveix per 
    //moure el pal amb la bolla en interior exterior
    case 111:
        if (movBolla < 0.0) {
            movBolla = movBolla + 0.1;
        }
        break;
    //Cas de la lletra del teclat "i" que serveix per 
    //moure el pal amb la bolla en sentit interior
    case 105:
        if (movBolla > -2.0) {
            movBolla = movBolla - 0.1;
        }
        break;
    //Cas de la lletra del teclat "e" que serveix per 
    //pujar la càmera la càmera d'altura
    case 101:
		y += 0.2;
		
		break;
    //Cas de la lletra del teclat "q" que serveix per 
    //baixae la càmara la càmera d'altura
	case 113:
		y -= 0.2;
		break;
    //Cas de la lletra del teclat "c" que serveix per 
    //canviar el tipus de càmera, fixe o dinàmica
    case 99:
		modeFixe = !modeFixe;
		break;
    //Cas de la lletra del teclat "3" que serveix per 
    //canviar la càmera entre les fixes
	case 51:
		cambiarCamara = (cambiarCamara + 1) % numCamares;
		break;
	}
}
void reshape(int w, int h) {
    //Prevé la divisió entre 0 quan la finestra és massa petita
    if (h == 0) {
        h = 1;
    }
    float ratio = w * 1.0 / h;

    glMatrixMode(GL_PROJECTION);

    //Reinicialitzam la matriu
    glLoadIdentity();

    //Posam que el viewport sigui tota la finestra
    glViewport(0, 0, w, h);

    //Posam la perspectiva correcta
    gluPerspective(45.0f, ratio, 0.1f, 1000.0f);

    //Tornam al Modelview
    glMatrixMode(GL_MODELVIEW);
}

// Funció que s'executa quan el sistema no està ocupat
void Idle(void)
{
    // Indicam que es necessàri repintar la pantalla
    glutPostRedisplay();
}

// Funció principal
int main(int argc, char** argv)
{
    //Inicialitzam la llibreria GLUT
    glutInit(&argc, argv);

    //Indicam com ha de ser la npva finestra
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(W_WIDTH, W_HEIGHT);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

    //Cream la finestra
    glutCreateWindow("Grua");
    //Carregam les textures
    texture = loadBMPRaw("texturaTerra.bmp", alturaImgTerra, ampladaImgTerra, true);
    textureParet = loadBMPRaw("BluesProductions.bmp", alturaImgBP, ampladaImgBP, true);
    textureParet2 = loadBMPRaw("texturaParet.bmp", alturaImgParet, ampladaImgParet, true);
    //Habilitam l'iluminació
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    //Funcions per dibuixar, redimensionar, la funcio idle i les funcions per capturar
    //les tecles
    glutDisplayFunc(Display);
    glutReshapeFunc(reshape);
    glutIdleFunc(Idle);
    glutKeyboardFunc(processNormalKeys);
    glutSpecialFunc(processSpecialKeys);

    glEnable(GL_DEPTH_TEST);

    glClearColor(0.7843137f, 0.8117647f, 0.8039215f, 0.0f);

    glOrtho(-1.0, 1.0f, -1.0, 1.0f, -1.0, 1.0f);
    
    //Comença la execució del core de GLUT
    glutMainLoop();
    return 1;
}

