#include "Arduino.h"
#include "CourseVector.h"


CourseVector::CourseVector()
{
}

CourseVector::CourseVector(int x1, int y1, int x2, int y2, int r) {
	this->x_pole[0] = x1;
	this->x_pole[1] = x2;
	this->y_pole[0] = y1;
	this->y_pole[1] = y2;
	this->r = r;
}

CourseVector::~CourseVector()
{
}

float CourseVector::getDistanceFromCourse(int x, int y) {
	determineSector(x, y);
	if ((this->sector) % 2 == 1) {
		// if sector is 1, 3, 7, 9
		return getDistanceFromPole(x, y) - this->r;
	}
	else {
		switch (this->sector)
		{
		case 2:
			return (float)(this->y_pole[0] - this->r - y);
		case 8:
			return (float)(-(this->y_pole[1] + this->r - y));
		case 4:
			return (float)(this->x_pole[0] - this->r - x);
		case 6:
			return (float)(-(this->x_pole[1] + this->r - x));
		default:
			return 0;
		}
	}
}

float CourseVector::getDistanceFromPole(int x, int y) {
	int x_pole_idx = 0;
	int y_pole_idx = 0;
	switch (this->sector) {
	case 1:
		x_pole_idx = 0;
		y_pole_idx = 0;
		break;
	case 3:
		x_pole_idx = 1;
		y_pole_idx = 0;
		break;
	case 7:
		x_pole_idx = 0;
		y_pole_idx = 1;
		break;
	case 9:
		x_pole_idx = 1;
		y_pole_idx = 1;
		break;
	}
	int xp = this->x_pole[x_pole_idx];
	int yp = this->y_pole[y_pole_idx];
	return  sqrt((xp - x)*(xp - x) + (yp - y)*(yp - y));
}

void CourseVector::determineSector(int x, int y) {
	int x_pos, y_pos;
	if (x < this->x_pole[0]) {
		x_pos = 0;
	}
	else if (this->x_pole[0] <= x && x < this->x_pole[1]) {
		x_pos = 1;
	}
	else {
		x_pos = 2;
	}

	if (y < this->y_pole[0]) {
		y_pos = 0;
	}
	else if (this->y_pole[0] <= y && y < this->y_pole[1]) {
		y_pos = 1;
	}
	else {
		y_pos = 2;
	}

	int sector = y_pos * 3 + x_pos + 1;
	this->sector = sector;
}
