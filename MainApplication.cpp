//Include necessary header files
#include "freeglut.h"
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <vector>
#include "EventFunctions.h"




#define ESC_ASCII 27

int g_Win;	

int number_of_points;
void render(void);
void onKeyboard(unsigned char, int, int);
void Mouse_location( int ,int , int, int);
void update(void);


extern EventFuncs e1;
const int EventFuncs::devision;
const int EventFuncs::devision1;



//#define SCREEN_WIDTH 640
//#define SCREEN_HEIGHT 480
int main(int argc, char** argv)
{	
	//vec3 a1 = { 1.0f,2.0f,3.0f };
	//vec3 a2 = { 1.0f,2.0f,3.0f };
	//vec3 a3 = a2 + a1;
	//std::cout << a3.x << "##" << a3.y << "##" << a3.z << "##";
	std::cout << "Enter the number of pints :: \n";
	std::cin >> number_of_points;
	e1.M_number_of_points = number_of_points;
	//==========================================
	//Step 1: Initialize GLUT
	//==========================================
	glutInit(&argc, argv);
	glEnable(GL_DEPTH_TEST);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glClearDepth(0.0f);
	glDepthFunc(GL_LEQUAL);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutInitWindowPosition(550, 250);
	g_Win = glutCreateWindow("simple shape ");
	//glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
	glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, -1000, 1000);
	glMatrixMode(GL_MODELVIEW);
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//gluPerspective(90, SCREEN_WIDTH/ SCREEN_HEIGHT,.1, 1000.0f);
	//glMatrixMode(GL_MODELVIEW);
	//==========================================
	//Step 2: Register callback functions
	//==========================================
	glutDisplayFunc(render);
	glutKeyboardFunc(onKeyboard);
	glutMouseFunc(Mouse_location);
	glutIdleFunc(update);
	//==========================================
	//Step 3: Enter main loop
	//==========================================
	glutMainLoop();
	return 0;
	}



//Modes mode = Modes::X_Y_mode;
//int X_Y_count = 0, Z_count = 0;
//std::vector<Location > Path_locations;
//bool first_time = true;
//int selector = 0;
//float Const_theta_start = 180 / 3.14;e
//float g_X = 0.0f, g_Z = 50.0f, g_Y = 0.0, b_X = 0, b_Z = 0;
//float r = 400, theta2 = 0, theta1 = 0;
//std::vector<Location > locations = { {0,0,0} };
//
//int number_of_points;
//int x_count = 0;