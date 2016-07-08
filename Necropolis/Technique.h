#pragma once
#include "Skill.h"
class Technique :
	public Skill
{
public:


	Technique() : Skill() {};
	Technique(int mpCost, ElementalArray elementalAttributes, double skillValue, ASPECT aspect, std::vector<Token> * ListOfSkillEffects, TARGET target, double castSpeed, std::vector<int>* upgrades)
		: Skill( mpCost, elementalAttributes, skillValue, aspect, ListOfSkillEffects, target, castSpeed, upgrades)
	{};

	~Technique();

	void cast();

	Skill* Clone() const { return new Technique(*this); };
};

