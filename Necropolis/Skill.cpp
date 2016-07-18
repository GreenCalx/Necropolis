#include "Skill.h"

Skill::~Skill()
{

	// Leak on the SkillTokens very likely.

	if ( _Upgrades!=NULL )
		delete[] _Upgrades;

}