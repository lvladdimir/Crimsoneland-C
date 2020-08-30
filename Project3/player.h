#pragma once
#include "Unit.h"

class Player :
    public Unit
{
public:
	int coord_x, coord_y; // coords of player on the playground

	Player( int new_windowx, int new_windowy, int new_mapx, int new_mapy) :
		Unit( new_windowx, new_windowy,  new_mapx,  new_mapy)
			{
				sprite = createSprite((base_path + "\\data\\avatar.jpg").c_str());
				x = new_windowx / 2;
				y = new_windowy / 2;
				coord_x = x;
				coord_y = y;
				length = 64;
				width = 64;
			}

	void ChangeLocation(int dx, int dy)
	{
		coord_x += dx;
		coord_y += dy;
	}

	bool OutOfMap(int dx, int dy)
	{
		if ((coord_x +dx < 0) || (coord_x +dx> mapx) || (coord_y +dy < 0) || (coord_y +dy > mapy))
			return true;
		return false;
	}
};

