#pragma once
#include "freeglut.h"
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <vector>
#include "EventFunctions.h"
#include <unordered_map>
#include <math.h>
#include <algorithm>
#include <stdlib.h>  
#include <windows.h>




#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480


struct vec3 {
	float x, y, z;

	vec3(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f) : x(_x), y(_y), z(_z) {}

};

vec3 operator + (vec3 a, vec3  b) {
	return vec3(a.x + b.x, a.y + b.y, a.z + b.z);
}


vec3 operator - (vec3 a, vec3 b) {
	return vec3(a.x - b.x, a.y - b.y, a.z - b.z);
}

vec3 operator * (float s, vec3 a) {
	return vec3(s * a.x, s * a.y, s * a.z);
}

vec3 operator / (float s, vec3 a) {
	return vec3(s / a.x, s / a.y, s / a.z);
}


template<class ForwardIt, class T>
constexpr // since C++20
void iota(ForwardIt first, ForwardIt last, T value, T start)
{
	*first = start;
	while (first != last) {
		*++first = *first + value;

	}
}
enum Modes { X_Y_mode, X_Z_mode, Draw_mode };

class Cube
{
public:

	float/* sizex, sizey, sizez,*/ theta1 = 0, size = 50;
	//Cube(float sizex, float sizey, float sizez) {
	//	this->sizex = sizex;
	//	this->sizey = sizey;
	//	this->sizez = sizez;
	//}
	void draw(float r, float g, float b, vec3 slope = { 0,0,0 }, vec3 rotate = { 0,0,0 }, vec3 transfer = { 0,0,0 }, vec3  scale = {1,1,1}) {


		float color[] = { r, g, b, 1 };
		//float specularColor[] = {1.0, 0.0f, 0.0f, 1.0f};
		//glutSolidSphere(size, 360, 100);

		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
		glMaterialfv(GL_FRONT, GL_SPECULAR, color);
		glMateriali(GL_FRONT, GL_SHININESS, 120);
		glPushMatrix();
		glTranslated(transfer.x, transfer.y, transfer.z);
		glRotatef(slope.x, 1, 0, 0);
		glRotatef(slope.y, 0, 1, 0);
		glRotatef(slope.z, 0, 0, 1);
		glRotatef(rotate.x, 1, 0, 0);
		glRotatef(rotate.y , 0, 1, 0);
		glRotatef(rotate.z , 0, 0, 1);
		glScalef(scale.x, scale.y, scale.z);
		/*glRotatef(theta1, 0,1,0);*/
		//glutWireSphere(size,10,10);
		glutSolidTeapot(40);
		glPopMatrix();




	}
};


Cube c1;

const float scal = 0.1f;
class EventFuncs
{
public:
	int w = 0, s = 0;
	static const int devision = 100;
	float arr[devision];
	static const int devision1 = 10;
	float arr1[devision1];

	std::unordered_map<float, float > Distance_in_time;
	bool M_first_time;
	Modes mode;
	int   M_count, M_number_of_points, index_selector;

	float M_g_X, M_g_Z, M_g_Y, M_b_X, M_b_Z, M_r, M_theta2, M_theta1, total_length;
	std::vector<vec3> locations, locations_t, key_point_locations,key_point_angles;
	std::unordered_map<float, vec3> locations_t_map;
	std::vector<float>  curve_len_t;
	std::vector<int> key_times ;



	int path_coeffs_size;



	EventFuncs() : M_first_time(true), M_g_X(0.0f), M_g_Z(0.0f), M_g_Y(0.0f), M_count(0), index_selector(0),
		M_b_X(0.0f), M_b_Z(0.0f), M_r(400.0f), M_theta2(0.0f), M_theta1(0.0f), locations({ {0,0,0} }), mode(Modes::X_Z_mode), total_length(0.0f)
	{
		iota(&arr[0], &arr[devision], 1.0f / devision, 0.0f);
		iota(&arr1[0], &arr1[devision1], 1.0f / devision1, 0.0f);
	}


	static vec3 getBezierPoint(std::vector<vec3>& points, float t) {
		int numPoints = points.size();
		vec3* tmp = new vec3[numPoints];
		/*tmp = points.data();*/
		std::copy(points.begin(), points.end(), tmp);
		//for (int i = 0; i < numPoints;i++) {
		//	tmp[i].x = points[i].x;
		//	tmp[i].y = points[i].y;
		//	tmp[i].z = points[i].z;
		//}

		int i = numPoints - 1;
		while (i > 0) {
			for (int k = 0; k < i; k++)
				tmp[k] = tmp[k] + t * (tmp[k + 1] - tmp[k]);
			i--;
		}
		vec3 answer = tmp[0];
		delete[] tmp;
		return answer;
	}

	void cal_path_t() {
		for (int i = 0; i < devision;i++) {
			locations_t.push_back(getBezierPoint(locations, arr[i]));
			locations_t_map[arr[i]] = locations_t[i];
		}
	}


	static float Calculate_slope(const vec3& a1, const vec3& a2)
	{
		return std::sqrtf(pow(a2.x - a1.x, 2) +
			pow(a2.y - a1.y, 2) +
			pow(a2.z - a1.z, 2));
	}
	static vec3 Calculate_angle(const vec3& a1, const vec3& a2)
	{

		vec3 t = float(devision)*(a2 - a1)  ;
		float  len1 = sqrtf(pow(t.x, 2.0f) + pow(t.y, 2.0f)+ pow(t.z, 2.0f));
		return { atanf(t.x / len1)*180.f/3.14f,atanf(t.y / len1) * 180.f / 3.14f ,atanf(t.z / len1) * 180.f/ 3.14f };

	}

	void cal_curve_lenght() {
		for (int i = 0;i < locations_t.size() - 1;i++) {
			curve_len_t.push_back(total_length);
			total_length += Calculate_slope(locations_t[i], locations_t[i + 1]);
		}
		for (int i = 0;i < locations_t.size() - 1;i++) {
			curve_len_t[i] /= total_length;
		}
	}


	int index_find(float& a) {
		for (int i = 0;i < curve_len_t.size();i++)
			if (a > curve_len_t[i])
				;
			else
				return i;
		std::cout << "not found ";
		return -1;
	}

	void cal_key_points_t() {
		for (int i=0;i<devision1;i++)
		{
			key_times.push_back(index_find(arr1[i]));
			key_point_locations.push_back(locations_t_map[arr[key_times[i]]]);
			key_point_angles.push_back(Calculate_angle(locations_t[key_times[i]], locations_t[key_times[i]+1]));
		}
		key_point_angles.push_back(Calculate_angle(locations_t[locations_t.size() - 2], locations_t[locations_t.size() - 1] ));
		key_point_locations.push_back(locations[locations.size()-1]);
	}

	

	void ultimate_function() {
		cal_path_t();
		cal_curve_lenght();
		cal_key_points_t();
	}
};


float  r = 500;

EventFuncs e1;
EventFuncs e2;
EventFuncs e3;
void render(void)
{


	int n = e1.locations.size();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (e1.mode == Modes::X_Z_mode) {
		//gluLookAt(100, 100, 0, 0, 0, 0, -1, 0, 0);
		glLoadIdentity();
		gluLookAt(0, 1000, 0, 0, 0, 0, 1, 0, 0);

		glBegin(GL_LINE_STRIP);
		for (int i = 0; i < e1.M_count;i++)
			glVertex3f(e1.locations[i].z, e1.locations[i].y, e1.locations[i].x);
		glEnd();



		//int* lineVertices = (int*)malloc(sizeof(int) * e1.locations.size() * 2);
		//int counter = 0;
		//for (vec3 i : e1.locations) {
		//	lineVertices[counter++] = i.x;
		//	lineVertices[counter++] = i.z;
		//}
		//glClear(GL_COLOR_BUFFER_BIT);
		////std::cout << sizeof(lineVertices) << std::endl;
		//glEnableClientState(GL_VERTEX_ARRAY);
		//glVertexPointer(2, GL_INT, 0, lineVertices);
		//glDrawArrays(GL_LINE_STRIP, 0, e1.locations.size());
		//glDisableClientState(GL_VERTEX_ARRAY);

	}

	else if (e1.mode == Modes::X_Y_mode) {

		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glLoadIdentity();
		gluLookAt(0, 0, 1000, 0, 0, 0, 0, 1, 0);
		//gluLookAt(0, 100, 0, 0, 0, 0, -1, 0, 0);

		glBegin(GL_LINE_STRIP);
		for (int i = 0; i < e1.M_count;i++)
			glVertex3f(e1.locations[i].x, e1.locations[i].y, e1.locations[i].z);
		glEnd();
	}
	else {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();

		float second_R = r * cosf(e1.M_theta2);

		gluLookAt(second_R * sinf(e1.M_theta1), r * sin(e1.M_theta2), second_R * cosf(e1.M_theta1), 0, 0.0, 0, 0, r * cos(e1.M_theta2), 0);


		c1.draw(1, 0, 0, e1.key_point_angles[e1.index_selector], /*{0,0,0}*/e2.key_point_locations[e1.index_selector], e1.key_point_locations[e1.index_selector], e3.key_point_locations[e1.index_selector]);


		glBegin(GL_LINE_STRIP);
		for (int i = 0; i < e1.M_count;i++)
			glVertex3f(e1.locations[i].x, e1.locations[i].y, e1.locations[i].z);
		glEnd();
		//glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();


		glPopMatrix();
	}
	glutSwapBuffers();

}


void update(void) {
	if (e1.mode == Modes::Draw_mode && e1.index_selector + 1 < e1.key_point_locations.size()) {
		e1.index_selector++;
		Sleep(int(3000 / 28));
	}
	else
		e1.index_selector = 0;
	glutPostRedisplay();
}


void Mouse_location(int button, int  state, int x, int y)
{
	if (button == 0)
		if (state == 1) {
			if (e1.mode == Modes::X_Z_mode)

				if (e1.M_count++ <= e1.M_number_of_points)
				{
					if (e1.M_first_time) {
						vec3 finish_rotation = { 0.0f,360.f,0.0f };
						vec3 finish_scale  = { 2.0f,2.0f,2.0f };
						e2.locations.push_back({ 0.0f,0.0f,0.0f });
						e2.locations.push_back(finish_rotation);
						e2.cal_path_t();						
						e3.locations.push_back({ 1.0f,1.0f,1.0f });
						e3.locations.push_back(finish_scale);
						e3.cal_path_t();

						for (int i = 0;i < e1.devision;i += 10) {
							e2.key_point_locations.push_back(e2.locations_t[i]);
							e3.key_point_locations.push_back(e3.locations_t[i]);

						}							
						e2.key_point_locations.push_back(finish_rotation);
						e3.key_point_locations.push_back(finish_scale);
						e1.locations.pop_back();
						e1.locations.push_back({ float(x),float(0),float(SCREEN_HEIGHT - y - 1 )});
						e1.M_first_time = false;
					}
					else
						e1.locations.push_back({ float(x) ,float(0),float(SCREEN_HEIGHT - y - 1) });
					std::cout << e1.locations.size() << std::endl;
				}
				else {
					e1.mode = Modes::X_Y_mode;
					e1.M_count = 0;
				}

			else if (e1.mode == X_Y_mode)
				if (e1.M_count <= e1.M_number_of_points) {
					e1.locations[e1.M_count++].y = float(SCREEN_HEIGHT - y - 1);
					std::cout << e1.M_count << "'th point " << std::endl;
				}
				else {
					e1.mode = Modes::Draw_mode;
					e1.ultimate_function();
					std::cout << "";
				}
		}
	glutPostRedisplay();
}

void onKeyboard(unsigned char key, int, int)
{

	switch (key)
	{
	case 'd': {
		e1.M_theta1 += scal;
		std::cout << e1.w << std::endl;
		std::cout << e1.s << std::endl;
		std::cout << "#####################" << std::endl;;
		//e1.M_theta2 += .1;
		break;
	}
	case 'a': {
		e1.M_theta1 -= scal;
		std::cout << e1.w << std::endl;
		std::cout << e1.s << std::endl;
		std::cout << "#####################" << std::endl;;
		//e1.M_theta2 -= .1;
		break;
	}
	case 'w': {
		e1.M_theta2 += scal;
		std::cout << e1.w << std::endl;
		std::cout << e1.s << std::endl;
		std::cout << "#####################" << std::endl;;
		//e1.M_theta1 += .1;
		break;
	}

	case 's': {
		e1.M_theta2 -= scal;
		std::cout << e1.w << std::endl;
		std::cout << e1.s << std::endl;
		std::cout << "#####################" << std::endl;
		//e1.M_theta1 -= .1;
		break;
	}
	case 'p': {
		e1.M_theta1 = 0;
		e1.M_theta2 = 0;

		break;
	}
	case 'r': {
		r += 50;
		break;
	}
	case 't': {
		r -= 50;
		break;
	}
	}
	glutPostRedisplay();
}
