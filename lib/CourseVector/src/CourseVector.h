#pragma once

/* sectors
1     2     3
 x1y1   x2y1
4     5     6
 x1y2   x2y2 
7     8     9
*/

class CourseVector
{
public:
	CourseVector();
	CourseVector(int x1, int y1, int x2, int y2, int r);
	~CourseVector();
	void setPoints(int x1, int y1, int x2, int y2, int r);
	float getDistanceFromCourse(int x, int y);
private:
	void determineSector(int x, int y);
	float getDistanceFromPole(int x, int y);
	int x_now;
	int y_now;
	int x_pole[2];
	int y_pole[2];
	int r;
	int sector;
};

