//#include <allegro5/allegro.h>
//#include <allegro5/allegro_font.h>
//#include <allegro5/allegro_ttf.h>
//#include <allegro5/allegro_audio.h>
//#include <allegro5/allegro_acodec.h>
//#include <allegro5/allegro_image.h>
//#include <allegro5/allegro_primitives.h>

#include <iostream>
#include <cassert>
#include <string>

#include <PerformanceTracker.h>
#include <MemoryTracker.h>
#include <Timer.h>
#include <EventSystem.h>

#include "Game.h"

using namespace std;

int main()
{
	PerformanceTracker* pPerformanceTracker = new PerformanceTracker;

	EventSystem::initInstance();
	EventSystem* eventSystem = EventSystem::getInstance();

	eventSystem->init();

	Game::createInstance();
	Game* game = Game::getInstance();
	
	game->init();
	game->doLoop();

	Game::destroyInstance();
	EventSystem::cleanupInstance();

	MemoryTracker::getInstance()->reportAllocations(cout);

	system("pause");
	return 0;
}
