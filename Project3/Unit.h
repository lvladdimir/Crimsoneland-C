#pragma once
#include "Framework.h"
#include <algorithm>
#include <list>


#include <stdio.h>  /* defines FILENAME_MAX */
#define WINDOWS  /* uncomment this line to use it for windows.*/ 
#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif
#include<iostream>


class Unit
{
private:
	std::string GetCurrentWorkingDir(void) {
		char buff[FILENAME_MAX];
		GetCurrentDir(buff, FILENAME_MAX);
		std::string current_working_dir(buff);
		return current_working_dir;
	}

public:
	Sprite *sprite;
	std::string base_path;
	bool isExist = true;
	double x, y;
	int  length=1, width=1, windowx, windowy, mapx,mapy;

	Unit(int new_windowx, int new_windowy, int new_mapx, int new_mapy)
	{
		base_path = GetCurrentWorkingDir();
		mapx = new_mapx;
		mapy = new_mapy;
		windowx = new_windowx;
		windowy = new_windowy;
		isExist = true;
	}

	void displacement(int dx, int dy)
	{
		x += dx;
		y += dy;
		//this.image.Location = new System.Drawing.Point(Convert.ToInt32(this.x), Convert.ToInt32(this.y));
	}

	void Move(int new_x, int new_y)
	{
		x = new_x;
		y = new_y;
		//this.image.Location = new System.Drawing.Point(Convert.ToInt32(this.x), Convert.ToInt32(this.y));
	}

	bool OutOfMap()
	{
		if ((x < 0) || (x > mapx) || (y < 0) || (y > mapy))
			return true;
		return false;
	}
	
	bool IntersectCalculation(Unit unit)
	{

		int x5 = std::max(x, unit.x);
		int y5 = std::max(y, unit.y);
		int x6 = std::min(x+width, unit.x + unit.width);
		int y6 = std::min(y +length, unit.y + unit.length);
		if ((x5>x6) || (y5>y6))
			return false;
		return true;
	}


	bool intersectbullet(std::list<Unit> units)
	{
		for (std::list<Unit>::iterator unit = units.begin(); unit != units.end(); ++unit)
		{
			if (IntersectCalculation(*unit))
			{
				(*unit).isExist = false;
				isExist = false;
			}
		}
	}
	
};
