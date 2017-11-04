//Semestre 2017 - 2
//************************************************************//
//************************************************************//
//************** Alumno: ALVAREZ POCEROS ABRAHAM ARTURO    ****//
//*************	 VISUAL STUDIO 2017						*****//
//*************											******//
//************************************************************//
#include "Main.h"

float transZ = -3.0f;
float transX = 0.0f;
float transY = 3.0f;
float angleX = 0.0f;
float angleY = 0.0f;
float angleHombro = 0.0f;
float angleCodo = 0.0f;
float angleMano = 0.0f;
float anglePulgar1 = 0.0f;
float anglePulgar2 = 0.0f;
float angleIndice1 = 0.0f;
float angleIndice2 = 0.0f;
float angleMedio1 = 0.0f;
float angleMedio2 = 0.0f;
float angleAnular1 = 0.0f;
float angleAnular2 = 0.0f;
float angleMen1 = 0.0f;
float angleMen2 = 0.0f;
int screenW = 0.0;
int screenH = 0.0;

//Indice
float Indice1 = 0.0f, Indice2 = 0.0f, separacion = 0.0f;
//Medio
float Medio1 = 0.0f, Medio2 = 0.0f;
//Anular
float Anular1 = 0.0f, Anular2 = 0.0f;
//Meñique
float Men1 = 0.0f, Men2 = 0.0f;
//Dedo gordo
float Pulgar1 = 0.0f, Pulgar2 = 0.0f;


GLfloat Position[] = { 0.0f, 3.0f, 0.0f, 1.0f };			// Light Position
GLfloat Position2[] = { 0.0f, 0.0f, -5.0f, 1.0f };	// Light Position

float posX = 0, posY = 2.5, posZ = -3.5, rotRodIzq = 0;


#define MAX_FRAMES 6//aumenta numero de frames
int i_max_steps = 990;//max de cuadros frames intermedios
int i_curr_steps = 0;

int w = 500, h = 500;
int frame = 0, time, timebase = 0;

//Frame
typedef struct _frame
{
	//Variables para GUARDAR Key Frames
	float angleIndice1;
	float incIndice1;
	float angleIndice2;
	float incIndice2;
	float separacion;
	float incSeparacion;
	float angleMedio1;
	float incMedio1;
	float angleMedio2;
	float incMedio2;
	float angleAnular1;
	float incAnular1;
	float angleAnular2;
	float incAnular2;
	float angleMen1;
	float incMen1;
	float angleMen2;
	float incMen2;
	float anglePulgar1;
	float incPulgar1;
	float anglePulgar2;
	float incPulgar2;

}FRAME;

FRAME KeyFrame[MAX_FRAMES];//arreglo que almacena frames
						   //int FrameIndex = 0;			//introducir datos
bool play = false;
int playIndex = 0;


//metodos del frame
void resetElements(void)
{
	angleIndice1 = KeyFrame[0].angleIndice1;
	angleIndice2 = KeyFrame[0].angleIndice2;
	separacion = KeyFrame[0].separacion;
	angleMedio1 = KeyFrame[0].angleMedio1;
	angleMedio2 = KeyFrame[0].angleMedio2;
	angleAnular1 = KeyFrame[0].angleAnular1;
	angleAnular2 = KeyFrame[0].angleAnular2;
	angleMen1 = KeyFrame[0].angleMen1;
	angleMen2 = KeyFrame[0].angleMen2;
	anglePulgar1 = KeyFrame[0].anglePulgar1;
	anglePulgar2 = KeyFrame[0].anglePulgar2;
}

void interpolation(void)
{
	KeyFrame[playIndex].incIndice1 = (KeyFrame[playIndex + 1].angleIndice1 - KeyFrame[playIndex].angleIndice1) / i_max_steps;
	KeyFrame[playIndex].incIndice2 = (KeyFrame[playIndex + 1].angleIndice2 - KeyFrame[playIndex].angleIndice2) / i_max_steps;
	KeyFrame[playIndex].incMedio1 = (KeyFrame[playIndex + 1].angleMedio1 - KeyFrame[playIndex].angleMedio1) / i_max_steps;
	KeyFrame[playIndex].incMedio2 = (KeyFrame[playIndex + 1].angleMedio2 - KeyFrame[playIndex].angleMedio2) / i_max_steps;
	KeyFrame[playIndex].incAnular1 = (KeyFrame[playIndex + 1].angleAnular1 - KeyFrame[playIndex].angleAnular1) / i_max_steps;
	KeyFrame[playIndex].incAnular2 = (KeyFrame[playIndex + 1].angleAnular2 - KeyFrame[playIndex].angleAnular2) / i_max_steps;
	KeyFrame[playIndex].incMen1 = (KeyFrame[playIndex + 1].angleMen1 - KeyFrame[playIndex].angleMen1) / i_max_steps;
	KeyFrame[playIndex].incMen2 = (KeyFrame[playIndex + 1].angleMen2 - KeyFrame[playIndex].angleMen2) / i_max_steps;
	KeyFrame[playIndex].incPulgar1 = (KeyFrame[playIndex + 1].anglePulgar1 - KeyFrame[playIndex].anglePulgar1) / i_max_steps;
	KeyFrame[playIndex].incPulgar2 = (KeyFrame[playIndex + 1].anglePulgar2 - KeyFrame[playIndex].anglePulgar2) / i_max_steps;

}


void animacion()
{
	/*fig3.text_izq -= 0.001;
	fig3.text_der -= 0.001;
	if (fig3.text_izq<-1)
	fig3.text_izq = 0;
	if (fig3.text_der<0)
	fig3.text_der = 1;
	*/
	//Movimiento del la mano
	if (play)
	{

		if (i_curr_steps >= i_max_steps) //end of animation between frames?
		{
			playIndex++;
			if (playIndex>MAX_FRAMES - 1)	//end of total animation?
			{
				printf("termina anim\n");
				playIndex = 0;
				play = false;
			}
			else //Next frame interpolations
			{
				i_curr_steps = 0; //Reset counter
								  //Interpolation
				interpolation();

			}
		}
		else
		{
			//Draw animation

			angleIndice1 += KeyFrame[playIndex].incIndice1;
			angleIndice2 += KeyFrame[playIndex].incIndice2;
			separacion += KeyFrame[playIndex].incSeparacion;
			angleMedio1 += KeyFrame[playIndex].incMedio1;
			angleMedio2 += KeyFrame[playIndex].incMedio2;
			angleAnular1 += KeyFrame[playIndex].incAnular1;
			angleAnular2 += KeyFrame[playIndex].incAnular2;
			angleMen1 += KeyFrame[playIndex].incMen1;
			angleMen2 += KeyFrame[playIndex].incMen2;
			anglePulgar1 += KeyFrame[playIndex].incPulgar1;
			anglePulgar2 += KeyFrame[playIndex].incPulgar2;

			i_curr_steps++;

		}

	}


	glutPostRedisplay();
}


void InitGL(void)     // Inicializamos parametros
{

	glShadeModel(GL_SMOOTH);							// Habilitamos Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// Negro de fondo
	glClearDepth(1.0f);									// Configuramos Depth Buffer
	glEnable(GL_DEPTH_TEST);							// Habilitamos Depth Testing

														//Configuracion luz
	glLightfv(GL_LIGHT0, GL_POSITION, Position);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, Position2);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);


	glDepthFunc(GL_LEQUAL);								// Tipo de Depth Testing a realizar
	glEnable(GL_COLOR_MATERIAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	///////////////////////////////////////////////////
	//Valores Frame
	KeyFrame[0].angleIndice1 = 0;
	KeyFrame[0].angleIndice2 = 0.0;
	KeyFrame[0].angleMedio1 = 0;			//LIKE
	KeyFrame[0].angleMedio2 = 0.0;
	KeyFrame[0].angleAnular1 = 0;
	KeyFrame[0].angleAnular2 = 0.0;
	KeyFrame[0].angleMen1 = 0;
	KeyFrame[0].angleMen2 = 0.0;
	KeyFrame[0].anglePulgar1 = 0.0;
	KeyFrame[0].anglePulgar2 = 0;


	KeyFrame[1].angleIndice1 = -117.0;
	KeyFrame[1].angleIndice2 = -119.0;
	KeyFrame[1].angleMedio1 = -107.0;			//piedra
	KeyFrame[1].angleMedio2 = -141.0;
	KeyFrame[1].angleAnular1 = -135.0;
	KeyFrame[1].angleAnular2 = -115.0;
	KeyFrame[1].angleMen1 = -142.0;
	KeyFrame[1].angleMen2 = -60.0;
	KeyFrame[1].anglePulgar1 = -78.0;
	KeyFrame[1].anglePulgar2 = -77;

	KeyFrame[2].angleIndice1 = 0.0;
	KeyFrame[2].angleIndice2 = 0.00;
	KeyFrame[2].angleMedio1 = 0;
	KeyFrame[2].angleMedio2 = 0;
	KeyFrame[2].angleAnular1 = 0;			//PAPEL
	KeyFrame[2].angleAnular2 = 0;
	KeyFrame[2].angleMen1 = 0;
	KeyFrame[2].angleMen2 = 50;
	KeyFrame[2].anglePulgar1 = 0.0;
	KeyFrame[2].anglePulgar2 = 0;

	KeyFrame[3].angleIndice1 = 0.0;
	KeyFrame[3].angleIndice2 = 0.0;
	KeyFrame[3].angleMedio1 = 0.0;
	KeyFrame[3].angleMedio2 = 0.0;
	KeyFrame[3].angleAnular1 = -135.0;
	KeyFrame[3].angleAnular2 = -135.0;			//TIJERA
	KeyFrame[3].angleMen1 = -142.0;
	KeyFrame[3].angleMen2 = -60;
	KeyFrame[3].anglePulgar1 = 0.0;
	KeyFrame[3].anglePulgar2 = -10.50;

	KeyFrame[4].angleIndice1 = -117.0;
	KeyFrame[4].angleIndice2 = -119.0;
	KeyFrame[4].angleMedio1 = -107.0;			//LIKE
	KeyFrame[4].angleMedio2 = -141.0;
	KeyFrame[4].angleAnular1 = -135.0;
	KeyFrame[4].angleAnular2 = -115.0;
	KeyFrame[4].angleMen1 = -142.0;
	KeyFrame[4].angleMen2 = -60.0;
	KeyFrame[4].anglePulgar1 = 0.0;
	KeyFrame[4].anglePulgar2 = 0;

	KeyFrame[5].angleIndice1 = 0;
	KeyFrame[5].angleIndice2 = 0.0;
	KeyFrame[5].angleMedio1 = 0;			//LIKE
	KeyFrame[5].angleMedio2 = 0.0;
	KeyFrame[5].angleAnular1 = 0;
	KeyFrame[5].angleAnular2 = 0.0;
	KeyFrame[5].angleMen1 = 0;
	KeyFrame[5].angleMen2 = 0.0;
	KeyFrame[5].anglePulgar1 = 0.0;
	KeyFrame[5].anglePulgar2 = 0;

}

void prisma(void)
{
	GLfloat vertice[8][3] = {
		{ 0.5 ,-0.5, 0.5 },    //Coordenadas Vértice 0 V0
		{ -0.5 ,-0.5, 0.5 },    //Coordenadas Vértice 1 V1
		{ -0.5 ,-0.5, -0.5 },    //Coordenadas Vértice 2 V2
		{ 0.5 ,-0.5, -0.5 },    //Coordenadas Vértice 3 V3
		{ 0.5 ,0.5, 0.5 },    //Coordenadas Vértice 4 V4
		{ 0.5 ,0.5, -0.5 },    //Coordenadas Vértice 5 V5
		{ -0.5 ,0.5, -0.5 },    //Coordenadas Vértice 6 V6
		{ -0.5 ,0.5, 0.5 },    //Coordenadas Vértice 7 V7
	};

	glBegin(GL_POLYGON);	//Front
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3fv(vertice[0]);
	glVertex3fv(vertice[4]);
	glVertex3fv(vertice[7]);
	glVertex3fv(vertice[1]);
	glEnd();

	glBegin(GL_POLYGON);	//Right
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3fv(vertice[0]);
	glVertex3fv(vertice[3]);
	glVertex3fv(vertice[5]);
	glVertex3fv(vertice[4]);
	glEnd();

	glBegin(GL_POLYGON);	//Back
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3fv(vertice[6]);
	glVertex3fv(vertice[5]);
	glVertex3fv(vertice[3]);
	glVertex3fv(vertice[2]);
	glEnd();

	glBegin(GL_POLYGON);  //Left
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3fv(vertice[1]);
	glVertex3fv(vertice[7]);
	glVertex3fv(vertice[6]);
	glVertex3fv(vertice[2]);
	glEnd();

	glBegin(GL_POLYGON);  //Bottom
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3fv(vertice[0]);
	glVertex3fv(vertice[1]);
	glVertex3fv(vertice[2]);
	glVertex3fv(vertice[3]);
	glEnd();

	glBegin(GL_POLYGON);  //Top
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3fv(vertice[4]);
	glVertex3fv(vertice[5]);
	glVertex3fv(vertice[6]);
	glVertex3fv(vertice[7]);
	glEnd();
}

void display(void)   // Creamos la funcion donde se dibuja
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Limiamos pantalla y Depth Buffer
														//glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(transX, transY, transZ);
	glRotatef(angleY, 0.0, 1.0, 0.0);
	glRotatef(angleX, 1.0, 0.0, 0.0);
	//Poner Código Aquí.
	//BRAZO DETYALLADO

	//antebrazo
	glTranslatef(0.0, -0.75, 0.0);
	glPushMatrix();
	glColor3f(1.0, 1.0, 0.0);
	glScalef(0.5, 1.0, 0.5);
	prisma();
	glPopMatrix();
	//mano
	glTranslatef(0.0, -0.75, 0.0);
	glRotatef(angleMano, 0.0, 0.0, 1.0);
	glPushMatrix();
	glColor3f(0.0, 1.0, 1.0);
	glScalef(0.5, 0.5, 0.25);
	prisma();
	glPopMatrix();
	//pulgar

	glPushMatrix();
	glRotatef(anglePulgar1, 0.0, 1.0, 0.0);
	glTranslatef(0.25, 0.0, 0.0);
	glTranslatef(0.1, 0.0, 0.0);
	glColor3f(0.3, 0.5, 0.0);
	//parte 1


	glPushMatrix();
	glScalef(0.15, 0.15, 0.155);
	prisma();
	glPopMatrix();
	glTranslatef(0.15, 0.0, 0.0);
	glRotatef(anglePulgar2, 0.0, 1.0, 0.0);
	glColor3f(0.3, 0.6, 1.0);
	//parte 2
	glPushMatrix();
	glScalef(0.15, 0.15, 0.15);
	prisma();
	glPopMatrix();

	glPopMatrix();

	//indice

	glPushMatrix();
	glTranslatef(0.1, -0.4, 0.0);
	glRotatef(angleIndice1, 1.0, 0.0, 0.0);
	glTranslatef(0.1, 0.0, 0.0);
	glColor3f(0.3, 0.5, 0.0);
	//parte 1

	glPushMatrix();
	glScalef(0.1, 0.3, 0.5);
	prisma();
	glPopMatrix();
	glTranslatef(0.0, -0.25, 0.0);
	glRotatef(angleIndice2, 1.0, 0.0, 0.0);
	glColor3f(0.3, 0.6, 1.0);
	//parte 2
	glPushMatrix();
	glScalef(0.1, 0.2, 0.5);
	prisma();
	glPopMatrix();
	glPopMatrix();

	//medio
	//	
	glPushMatrix();
	glTranslatef(-0.025, -0.4, 0.0);
	glRotatef(angleMedio1, 1.0, 0.0, 0.0);
	glTranslatef(0.1, 0.0, 0.0);
	glColor3f(0.3, 0.5, 0.0);
	//parte 1
	//		
	glPushMatrix();
	glScalef(0.1, 0.3, 0.5);
	prisma();
	glPopMatrix();
	glTranslatef(0.0, -0.3, 0.0);
	glRotatef(angleMedio2, 1.0, 0.0, 0.0);
	glColor3f(0.3, 0.6, 1.0);
	//parte 2
	glPushMatrix();
	glScalef(0.1, 0.3, 0.5);
	prisma();
	glPopMatrix();
	glPopMatrix();
	//anular
	//
	glPushMatrix();
	glTranslatef(-0.175, -0.4, 0.0);
	glRotatef(angleAnular1, 1.0, 0.0, 0.0);
	glTranslatef(0.1, 0.0, 0.0);
	glColor3f(0.3, 0.5, 0.0);
	//parte 1
	//	
	glPushMatrix();
	glScalef(0.1, 0.3, 0.5);
	prisma();
	glPopMatrix();
	glTranslatef(0.0, -0.25, 0.0);
	glRotatef(angleAnular2, 1.0, 0.0, 0.0);
	glColor3f(0.3, 0.6, 1.0);
	//parte 2
	glPushMatrix();
	glScalef(0.1, 0.2, 0.5);
	prisma();
	glPopMatrix();
	glPopMatrix();
	//meñique
	//	
	glPushMatrix();
	glTranslatef(-0.3, -0.4, 0.0);
	glRotatef(angleMen1, 1.0, 0.0, 0.0);
	glTranslatef(0.1, 0.0, 0.0);
	glColor3f(0.3, 0.5, 0.0);
	//parte 1
	//	
	glPushMatrix();
	glScalef(0.1, 0.3, 0.5);
	prisma();
	glPopMatrix();
	glTranslatef(0.0, -0.3, 0.0);
	glRotatef(angleMen2, 1.0, 0.0, 0.0);
	glColor3f(0.3, 0.6, 1.0);
	//parte 2
	glPushMatrix();
	glScalef(0.1, 0.3, 0.5);
	prisma();
	glPopMatrix();
	glPopMatrix();

	glPopMatrix();

	glutSwapBuffers();//c
					  // Swap The Buffers
}

void reshape(int width, int height)   // Creamos funcion Reshape
{
	if (height == 0)										// Prevenir division entre cero
	{
		height = 1;
	}

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);						// Seleccionamos Projection Matrix
	glLoadIdentity();

	// Tipo de Vista
	//glOrtho(-5,5,-5,5,0.2,20);	
	glFrustum(-0.1, 0.1, -0.1, 0.1, 0.1, 50.0);

	glMatrixMode(GL_MODELVIEW);							// Seleccionamos Modelview Matrix
														//glLoadIdentity();									
}

void keyboard(unsigned char key, int x, int y)  // Create Keyboard Function
{
	switch (key) {
	case 'u':
	case 'U':
		angleMano += 0.5f; //mano
		break;
	case 'j':
	case 'J':
		angleMano -= 0.5f;//mano rotacion
		break;
	case 'i':
		angleIndice1 += 1.0f;
		break;
	case 'I':
		angleIndice2 += 1.0f;
		break;
	case 'o':
		angleIndice1 -= 1.0f;
		break;
	case 'O':
		angleIndice2 -= 1.0f;
		break;

	case 'm':
		angleMedio1 += 1.0f;
		break;
	case 'M':
		angleMedio2 += 1.0f;
		break;
	case 'n':
		angleMedio1 -= 1.0f; //pulgar 1
		break;
	case 'N':
		angleMedio2 -= 1.0f;//pulgar 2
		break;

	case 'b':
		angleAnular1 += 1.0f;
		break;
	case 'B':
		angleAnular2 += 1.0f;//pulgar 2
							 //Posicion de ambos en Y en 90 para cerrar pulgar
		break;
	case 'v':
		angleAnular1 -= 1.0f; //pulgar 1
		break;
	case 'V':
		angleAnular2 -= 1.0f;//pulgar 2
		break;
	case 'c':
		angleMen1 += 1.0f;
		break;
	case 'C':
		angleMen2 += 1.0f;//pulgar 2
						  //Posicion de ambos en Y en 90 para cerrar pulgar
		break;
	case 'x':
		angleMen1 -= 1.0f; //pulgar 1
		break;
	case 'X':
		angleMen2 -= 1.0f;//pulgar 2
		break;

	case '1':
		anglePulgar1 += 1.0f;
		break;
	case '2':
		anglePulgar2 += 1.0f;//pulgar 2
							 //Posicion de ambos en Y en 90 para cerrar pulgar
		break;
	case '3':
		anglePulgar1 -= 1.0f; //pulgar 1
		break;
	case '4':
		anglePulgar2 -= 1.0f;//pulgar 2
		break;

	case 'w':
	case 'W':
		transY += 0.1f;
		break;
	case 's':
	case 'S':
		transY -= 0.1f;
		break;
	case 'a':
	case 'A':
		transX += 0.1f;
		break;
	case 'd':
	case 'D':
		transX -= 0.1f;
		break;
	case 'q':
	case 'Q':
		transZ += 0.1f;
		break;
	case 'e':
	case 'E':
		transZ -= 0.1f;
		break;
	case '0':
		angleY -= 1;
		break;
	case 'k':
	case 'K':
		printf("***********VALORES*****************\n");
		printf("\Indice1: %f  Indice2: %f\n", angleIndice1, angleIndice2);
		printf("\Medio1: %f  Medio2: %f\n", angleMedio1, angleMedio2);
		printf("\Anular1: %f  Anular2: %f\n", angleAnular1, angleAnular2);
		printf("\Men1: %f  Men2: %f\n", angleMen1, angleMen2);
		printf("\Pulgar1: %f  Pulgar2: %f\n", anglePulgar1, anglePulgar2);
		break;
	case 'l':
	case 'L':
		if (play == false)
		{
			resetElements();
			//First Interpolation	

			interpolation();

			play = true;
			playIndex = 0;
			i_curr_steps = 0;
		}
		else
		{
			play = false;
		}
		break;

	case 27:        // Cuando Esc es presionado...
		exit(0);   // Salimos del programa
		break;
	default:        // Cualquier otra
		break;
	}
	glutPostRedisplay();
}

void arrow_keys(int a_keys, int x, int y)  // Funcion para manejo de teclas especiales (arrow keys)
{
	switch (a_keys) {
	case GLUT_KEY_UP:		// Presionamos tecla ARRIBA...
		angleX += 2.0f;
		break;
	case GLUT_KEY_DOWN:		// Presionamos tecla ABAJO...
		angleX -= 2.0f;
		break;
	case GLUT_KEY_LEFT:
		angleY += 2.0f;
		break;
	case GLUT_KEY_RIGHT:
		angleY -= 2.0f;
		break;
	default:
		break;
	}
	glutPostRedisplay();
}


int main(int argc, char** argv)   // Main Function
{
	glutInit(&argc, argv); // Inicializamos OpenGL
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // Display Mode (Clores RGB y alpha | Buffer Doble )
	screenW = glutGet(GLUT_SCREEN_WIDTH);
	screenH = glutGet(GLUT_SCREEN_HEIGHT);
	glutInitWindowSize(500, 500);	// Tamaño de la Ventana
	glutInitWindowPosition(0, 0);	//Posicion de la Ventana
	glutCreateWindow("Practica 11, reporte"); // Nombre de la Ventana
	printf("Resolution H: %i \n", screenW);
	printf("Resolution V: %i \n", screenH);
	InitGL();						// Parametros iniciales de la aplicacion
	glutDisplayFunc(display);  //Indicamos a Glut función de dibujo
	glutReshapeFunc(reshape);	//Indicamos a Glut función en caso de cambio de tamano
	glutKeyboardFunc(keyboard);	//Indicamos a Glut función de manejo de teclado
	glutSpecialFunc(arrow_keys);	//Otras
	glutIdleFunc(animacion);

	glutMainLoop();          // 

	return 0;
}



