#pragma once
#include "Unit.h"
class Reticle :
    public Unit
{
public:
	Sprite* reloadsprite;
	Sprite* usualsprite;

	Reticle( int new_windowx, int new_windowy, int new_mapx, int new_mapy) :
		Unit( new_windowx, new_windowy, new_mapx, new_mapy)
	{
		x = 0;
		y = 0;
		usualsprite = createSprite((base_path + "\\data\\circle.tga").c_str());
		reloadsprite = createSprite((base_path + "\\data\\reticle.png").c_str());
		sprite = usualsprite;
		length = 32;
		width = 32;
	}
};

