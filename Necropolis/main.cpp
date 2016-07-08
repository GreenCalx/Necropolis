// Example program:
// Using SDL2 to create an application window

#include <SDL\SDL.h>
#include <GL\glew.h>
#include <GLM\glm.hpp>
#include <stdio.h>
#include <iostream>

// -------------------
#include "Spell.h"
#include "Technique.h"
#include "SkillFactory.h"
bool test();
// -------------------

int main(int argc, char* argv[]) {

	SDL_Window *window;                    // Declare a pointer

	SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2

	test();
										   // Create an application window with the following settings:
	window = SDL_CreateWindow(
		"An SDL2 window",                  // window title
		SDL_WINDOWPOS_UNDEFINED,           // initial x position
		SDL_WINDOWPOS_UNDEFINED,           // initial y position
		640,                               // width, in pixels
		480,                               // height, in pixels
		SDL_WINDOW_OPENGL                  // flags - see below
	);
	
	// Check that the window was successfully created
	if (window == NULL) {
		// In the case that the window could not be made...
		printf("Could not create window: %s\n", SDL_GetError());
		return 1;
	}

	// The window is open: could enter program loop here (see SDL_PollEvent())

	SDL_Delay(3000);  // Pause execution for 3000 milliseconds, for example

					  // Close and destroy the window
	SDL_DestroyWindow(window);

	// Clean up
	SDL_Quit();
	return 0;
}

bool test()
{
	SkillFactory * factory = new SkillFactory();
	Technique    * fireslash = new Technique();
	Spell        * fireball = new Spell();
	fireball->setSkillValue(5);

	factory->submit("fireball", fireball);
	factory->submit("fireslash", fireslash);
	std::vector<int> upgrades;
	upgrades.resize(4, 0);
	factory->build( "fireball");
	upgrades.resize(4, 2);
	factory->build("fireball");

	Spell		* fireball2 = (Spell*)factory->getBuiltSkill("fireball");
	Technique    * fireslash2 = (Technique*)factory->getBuiltSkill("fireslash");
	fireball->setSkillValue(2);
	Spell		* fireball3 = (Spell*)factory->getBuiltSkill("fireball");

	std::cout << " fireball ATK ?" << fireball2->getSkillValue() << std::endl;
	fireball->setSkillValue(5);
	std::cout << " fireslash ATK ?" << fireball3->getSkillValue() << std::endl;
	std::cout << "-----------"  << std::endl;
	fireball2->setSkillValue(3);
	std::cout << " fireball ATK ?" << fireball2->getSkillValue() << std::endl;
	std::cout << " fireslash ATK ?" << fireball3->getSkillValue() << std::endl;

	std::cout << "-----------" << std::endl;
	upgrades.resize(3, 1);
	Spell* fireball4 = (Spell*)factory->build("fireball");
	fireball4->setSkillValue(23);
	std::cout << " fireball ATK ?" << fireball2->getSkillValue() << std::endl;
	std::cout << " fireball4 ATK ?" << fireball4->getSkillValue() << std::endl;
	fireball2->setSkillValue(26);
	std::cout << " fireball ATK ?" << fireball2->getSkillValue() << std::endl;
	std::cout << " fireball4 ATK ?" << fireball4->getSkillValue() << std::endl;
	std::cout << "-----------" << std::endl;
	upgrades.resize(4, 1);
	Spell* fireball5 = (Spell*)factory->build("fireball");
	std::cout << " fireball ATK ?" << fireball2->getSkillValue() << std::endl;
	std::cout << " fireball4 ATK ?" << fireball4->getSkillValue() << std::endl;
	std::cout << " fireball5 ATK ?" << fireball5->getSkillValue() << std::endl;

	std::cout << " fireball ATK ?" << fireball2->getSkillValue() << std::endl;
	std::cout << " fireball4 ATK ?" << fireball4->getSkillValue() << std::endl;
	std::cout << " fireball5 ATK ?" << fireball5->getSkillValue() << std::endl;
	std::cout << "-----------" << std::endl;
	return true;
}

