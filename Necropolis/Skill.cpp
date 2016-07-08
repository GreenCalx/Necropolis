#include "Skill.h"

Skill::~Skill()
{

	if ( _ListOfSkillEffects!=NULL )
		delete[] _ListOfSkillEffects;
	if ( _Upgrades!=NULL )
		delete[] _Upgrades;

}