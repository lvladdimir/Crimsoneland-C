#pragma once
#include "Unit.h"
#include <cmath>
#include "Enemy.h"

class Bullet :
    public Unit
{
protected:
    double vectx, vecty;
    int speed = 3;

public: Bullet(int point_x, int point_y, int new_windowx, int new_windowy, int new_mapx, int new_mapy):
	Unit( new_windowx, new_windowy,  new_mapx,  new_mapy) {
		x = new_windowx / 2 + 32;
		y = new_windowy / 2 + 32;

		sprite = createSprite((base_path + "\\data\\bullet.png").c_str());
		length = 13;
		width = 12;

		vectx = speed * (point_x - x) / sqrt((point_x - x)* (point_x - x) + (point_y - y)* (point_y - y));
		vecty = speed * (point_y - y) / sqrt((point_x - x)* (point_x - x) + (point_y - y)* (point_y - y));	
	}

	  void Move(std::list<Enemy*> enemies)
	  {
		  x += vectx;
		  y += vecty;
		  intersectbullet(enemies);

		  if (OutOfMap())
			  isExist = false;
	  }

private:

	void intersectbullet(std::list<Enemy*> units)
	{
		for (std::list<Enemy*>::iterator unit = units.begin(); unit != units.end(); ++unit)
		{
			if (IntersectCalculation(**unit))
			{
				(**unit).isExist = false;
				isExist = false;
			}
		}
	}

	bool Equal(Bullet bullet)
	{
		if ((bullet.x == x) && (bullet.y == y) && (bullet.vectx == vectx) && (bullet.vecty == vecty))
		{
			return true;
		}
		return false;
	}

	bool Reload(std::list<Bullet> bullets, int num_ammo=3)
	{
		if ((bullets.size() == num_ammo) && (Equal(bullets.back()) ))
		{
			return true;
		}
		return false;
	}


/*	public void Dispose()
	{
		this.timer.Dispose();
		this.image.Dispose();
		this.Reload();

	}
	*/
	


/*	private void timer_Tick(object sender, EventArgs e)
	{
		this.Move();

		if (this.OutOfMap())
		{
			this.Dispose();
		}
	}
*/
};

