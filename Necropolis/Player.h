#pragma once
#include "BasePawn.h"

#include "SkillBook.h"
#include "ElementalArray.h"

class Player : public BasePawn
{
public:
	Player();
	~Player();



	// Attributes;
private:
	
	// Stats
	int _HP;
	int _MP;
	int _ATK;
	int _DEF;
	// Elemental Defenses
	ElementalArray _ElemDEF;
	// Elemental Attacks
	ElementalArray _ElemATK;

	int _LVL;
	int _ProfilesCount;
	
	// Learned Skills
	SkillBook	* pSkillBook;
	
	// Equipped Skills


};

