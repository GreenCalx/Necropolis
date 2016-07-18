#pragma once
#include "Spell.h"
// --------
#include "Projectile.h"

class Fireball :
	public Spell
{

public:

	Fireball() : Spell() {};
	Fireball(int mpCost, ElementalArray elementalAttributes, double skillValue, ASPECT aspect, std::vector<Token> * ListOfSkillEffects, TARGET target, double castSpeed, std::vector<int>* upgrades)
		: Spell(mpCost, elementalAttributes, skillValue, aspect, ListOfSkillEffects, target, castSpeed, upgrades)
	{};
	~Fireball();




private:
	Projectile		* _pProjectile;

	double			blastRadius; // Upgradable


};

