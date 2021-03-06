// Example program:
// Using SDL2 to create an application window

#include <SDL\SDL.h>
#include <GL\glew.h>
#include <GLM\glm.hpp>
#include <stdio.h>
#include <iostream>

// -------------------
#include "Defines.h"

#include "Spell.h"
#include "Technique.h"
#include "SkillFactory.h"
#include "SkillLoader.h"

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

	json FILE_A, FILE_B;
	SkillLoader::load("Fireball", SKILLPATH, FILE_A)  ;
	std::cout << FILE_A.dump(4) << std::endl;
	SkillLoader::save("Fireball2", SKILLPATH, FILE_A, FILE_B) ;
	SkillLoader::load("Fireball2", SKILLPATH, FILE_B)  ;
	std::cout << FILE_B.dump(4) << std::endl;

	Skill * test = NULL;
	SkillLoader::loadSkill("Fireball", test);
	std::cout << " OK " << std::endl;
	return true;
}

