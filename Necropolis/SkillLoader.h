#pragma once
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <json.hpp>

// ---------------------------------------------------------------------------------------
// Using	: JSON for Modern C++ https://nlohmann.github.io/json/ for the json parser
// Credits	: Niels Lohmann
// License	: MIT
// ---------------------------------------------------------------------------------------

using json = nlohmann::json;

class Skill;
class Spell;
class Technique;

class SkillLoader
{
public:

	static int load(std::string fileName, json & oFile);

	static int save(std::string fileName, json fileToSave, json & oFile);

	static int loadSkill(std::string skillName, Skill *& opSKill);

	SkillLoader();
	~SkillLoader();
};

