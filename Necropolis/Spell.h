#pragma once
#include "Skill.h"
class Spell :
	public Skill
{
public:
	Spell() : Skill() {};
	Spell(int mpCost, ElementalArray elementalAttributes, double skillValue, ASPECT aspect, std::vector<Token*>  ListOfSkillEffects, TARGET target, double castSpeed, std::vector<int>* upgrades)
		: Skill( mpCost, elementalAttributes, skillValue, aspect, ListOfSkillEffects, target, castSpeed, upgrades)
	{};
	~Spell();

	void cast();

	Skill* Clone() const { return new Spell(*this); };
};

