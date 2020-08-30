#include "Framework.h"
#include <list>
#include "Bullet.h"
#include "Enemy.h"
#include "Player.h"
#include "Reticle.h"

#include <string>
#include <iostream>
#include <fstream>

/* Test Framework realization */
class MyFramework : public Framework {

public:

	int tickcounter=1;
	Player* player;
	Reticle* reticle;
	std::list<Enemy*> enemies = {};
	std::list<Bullet*> bullets = {};
	std::list<Bullet*> oldbullets = {};
	int windowx = 800, windowy = 640;
	int mapx = 800, mapy = 640;
	int maxbullets = 2, maxenemies = 10;


	virtual void PreInit(int& width, int& height, bool& fullscreen)
	{
		width = 800;
		height = 640;
		fullscreen = false;
		read_init_file();
		if (windowx == 0)
		{
			windowx = width;
		}
		width = windowx;
		height = windowy;
	}

	void read_init_file()
	{
		std::ifstream myfile;
		myfile.open("example.txt");
		myfile >> windowx;
		myfile >> windowy;
		myfile >> mapx;
		myfile >> mapy;
		myfile >> maxbullets;
		myfile >> maxenemies;
		myfile.close();
	}

	
	virtual bool Init() {
		player = new Player(windowx, windowy,mapx,mapy);
		reticle = new Reticle(windowx, windowy, mapx, mapy);
		enemies = {};
		bullets = {};
		oldbullets = {};
		return true;
	}

	virtual void Close() {
	
	}


	virtual bool Tick() {

		if (player->isExist == false)
		{
			Init();
			return false;
		}
		tickcounter++;
		tickcounter = tickcounter % 100;
        drawTestBackground();

		drawSprite(player->sprite, windowx/2, windowy/2);

		drawSprite(reticle->sprite, reticle->x, reticle->y);

		//Reload bullets
		Reload();

		// delete old bullets. previous reload
		oldbullets.erase(
			std::remove_if(oldbullets.begin(), oldbullets.end(),
				[](Bullet* o) { return !o->isExist; }),
			oldbullets.end());

		//old bullets move
		for (std::list<Bullet*>::iterator bullet = oldbullets.begin(); bullet != oldbullets.end(); ++bullet) {
			(*bullet)->Move(enemies);
			drawSprite((*bullet)->sprite, (*bullet)->x, (*bullet)->y);
		}
	
		//bullets move
		for (std::list<Bullet*>::iterator bullet = bullets.begin(); bullet != bullets.end(); ++bullet){
			if ((*bullet)->isExist == false)
			{
				continue;
			}
			(*bullet)->Move(enemies);
			drawSprite((*bullet)->sprite, (*bullet)->x, (*bullet)->y);

		}
		
		//spawn new enemy
		if ((tickcounter == 0) && (enemies.size()<maxenemies))
		{
			enemies.push_back((new Enemy(enemies,windowx, windowy, mapx, mapy)));

			//drawSprite(enemies.back().sprite, enemies.back().x, enemies.back().y);
		}

		// delete notExisting enemies
		enemies.erase(
			std::remove_if(enemies.begin(), enemies.end(),
				[]( Enemy* o) { return !o->isExist; }),
			enemies.end());
		
		//enemies move
		for (std::list<Enemy*>::iterator enemy = enemies.begin(); enemy != enemies.end(); ++enemy) {
			(*enemy)->Move(enemies, &player );
			drawSprite((*enemy)->sprite, (*enemy)->x, (*enemy)->y);

		}
		
		return false;
	}

	//Reload bullets
	void Reload()
	{
		if (bullets.size() == maxbullets) 
		{
			reticle->sprite = reticle->reloadsprite;
			if ((*(bullets.back())).isExist == false)
			{
				oldbullets=bullets;
				bullets.clear();
				reticle->sprite = reticle->usualsprite;
			}
		}
	}


	virtual void onMouseMove(int x, int y, int xrelative, int yrelative) {
		reticle->x = x;
		reticle->y = y;
	}

	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased) {
		if ((isReleased) && (bullets.size()< maxbullets))
		{
			bullets.push_back(
				(new Bullet(reticle->x, reticle->y,windowx, windowy, mapx, mapy)));
		};
	}
	
	virtual void onKeyPressed(FRKey k) {
		
		switch (k) {

		case FRKey::RIGHT:
			if (!(*player).OutOfMap(10,0))
				MoveAll(-10,0);
			break;

		case FRKey::LEFT:
			if (!(*player).OutOfMap(-10, 0))
				MoveAll(10, 0);
			break;

		case FRKey::DOWN:
			if (!(*player).OutOfMap(0, 10))
				MoveAll(0, -10);
			break;

		case FRKey::UP:
			if (!(*player).OutOfMap(0, -10))
				MoveAll(0, 10);
			break;
		}

	}

	virtual void onKeyReleased(FRKey k) {

	}

	 void MoveAll(int x, int y)
	{
		(*player).ChangeLocation(-x, -y);
		for (std::list<Bullet*>::iterator b = bullets.begin(); b != bullets.end(); ++b)
		{
			(*b)->displacement(x, y);
		}

		for (std::list<Enemy*>::iterator e = enemies.begin(); e != enemies.end(); ++e)
		{
			(*e)->displacement(x, y);
		}
	}
};


void ConsoleParcer(int argc, char* argv[])
{
	int windowx = 800, windowy = 640;
	int mapx = 800, mapy = 640;
	int maxbullets = 2, maxenemies = 10;

	if (argc % 2 == 0)
	{
		return;
	}
	std::string key, myvalue;
	for (int i = 0; i < argc /2; i++)
	{
		key = argv[i * 2 + 1];
		myvalue = argv[i * 2 + 2];
		std::cout<<key + " " + myvalue;
		if (key == "-window")
		{          
			windowy = std::stoi( myvalue.substr(1, myvalue.find( 'x')));
			windowx = std::stoi(myvalue.substr(0, myvalue.find('x')));
		}
		if (key == "-map")
		{
			mapy = std::stoi(myvalue.substr(1, myvalue.find('x')));
			mapx = std::stoi(myvalue.substr(0, myvalue.find('x')));

		}
		if (key == "-num_enemies")
		{
			maxenemies = std::stoi(myvalue);
		}
		if (key == "-num_ammo")
		{
			maxbullets= std::stoi(myvalue);
		}
	}

	std::ofstream myfile;
	myfile.open("example.txt");
	myfile << windowx + "\n";
	myfile << windowy + "\n";
	myfile << mapx + "\n";
	myfile << mapy + "\n";
	myfile << maxbullets + "\n";
	myfile << maxenemies + "\n";
	myfile.close();

}




int main(int argc, char *argv[])
{
	ConsoleParcer(argc, argv);
	return run(new MyFramework);
}
