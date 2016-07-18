#pragma once
#include <iostream>
#include <map>
#include <vector>


class Skill;
class SkillEffect;

// Bundle of upgrades
class UpgradeBundle {
	
public:
	UpgradeBundle() : _Upgrades(std::map<Upgrade, std::string>()), _pAttachedSkill(NULL) 
	{}
	UpgradeBundle(std::map<Upgrade, std::string> iUpgrades) : _Upgrades(iUpgrades), _pAttachedSkill(NULL)
	{}
	UpgradeBundle(Skill* ipAttachedSkill, std::map<Upgrade, std::string> iUpgrades) : _Upgrades(iUpgrades), _pAttachedSkill(ipAttachedSkill)
	{}

	Skill*	getAttachedSkill(void) { return _pAttachedSkill; }
	void	setAttachedSkill(Skill* ipAttachedSkill) { _pAttachedSkill = ipAttachedSkill; }
	std::map<Upgrade, std::string>	getUpgrades(void) { return _Upgrades; }
	void	setUpgrades(std::map<Upgrade, std::string> iUpgrades) { _Upgrades = iUpgrades; }

private:
	Skill							*	_pAttachedSkill;
	std::map<Upgrade, std::string>		_Upgrades;

};

struct Upgrade {

	// Upgrade : physics
	double radius = 0.;
	double blastRadius = 0.;
	double projectileImpulse = 0.;
	double projectileWeight = 0.;

	// Upgrade : Skill
	double skillValue = 0.;
	double skillCost = 0.;
	double castSpeed = 0.;

	// UpgradeMisc :
	unsigned int numberOfProjectiles = 0;
	std::vector<SkillEffect> skillEffects = std::vector<SkillEffect>();

};