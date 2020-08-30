#pragma once
#include "Unit.h"
#include <cmath>
#include "Player.h"

class Enemy :
    public Unit
{
protected:
     double vectx, vecty;
     double speed = 0.1;
	 int player_x = windowx / 2, player_y = windowy / 2;

private:
	void spawn()
	{
		int radius = 100;		
		x = windowx / 2 + (radius + rand() % ((windowx - radius) / 2)) * (1 - 2 * (rand() % 2));
		y = windowy / 2 + (radius + rand() % ((windowy - radius) / 2)) * (1 - 2 * (rand() % 2));
	}


public:
	Enemy(std::list<Enemy*> enemies, int new_windowx, int new_windowy, int new_mapx, int new_mapy) :
		Unit( new_windowx, new_windowy,  new_mapx,  new_mapy) {
		spawn();
		length = 35;
		width = 34;
		if (intersect_enemy(enemies))
		{
			isExist = false;
			return;
		}

		sprite = createSprite((base_path + "\\data\\enemy.png").c_str());
		vectx = speed * (player_x - x) / sqrt((player_x - x) * (player_x - x) + (player_y - y) * (player_y - y));
		vecty = speed * (player_y - y) / sqrt((player_x - x) * (player_x - x) + (player_y - y) * (player_y - y));
	}

	bool intersect_player(std::list<Player**> units)
	{
		for (std::list<Player**>::iterator unit = units.begin(); unit != units.end(); ++unit)
		{
			if (IntersectCalculation(***unit))
			{
				(***unit).isExist = false;
				isExist = false;
			}
		}
		return false;
	}

	bool intersect_enemy(std::list<Enemy*> units)
	{
		for (std::list<Enemy*>::iterator unit = units.begin(); unit != units.end(); ++unit)
		{
			if (Equal(**unit))
			{
				continue;
			}
			if (IntersectCalculation(**unit) )
			{
				return true;
			}
		}
		return false;
	}

	bool Equal(Enemy enemy)
	{
		if ((enemy.x == x) && (enemy.y == y) && (enemy.vectx == vectx) && (enemy.vecty == vecty))
		{
			return true;
		}
		return false;
	}


	void Move(std::list<Enemy*> enemies, Player** player)
	{

		
		//not intersect with other enemies
		if (!(intersect_enemy(enemies)))
		{
			vectx = speed * (player_x - x) / sqrt((player_x - x) * (player_x - x) + (player_y - y) * (player_y - y));
			vecty = speed * (player_y - y) / sqrt((player_x - x) * (player_x - x) + (player_y - y) * (player_y - y));
			x += vectx;
			y += vecty;
		}

		// intersect with player
		intersect_player({ player});
		

		
	}

};

