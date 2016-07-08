#pragma once
#include <iostream>
#include <vector>
#include <map>

#include "Skill.h"

class SkillFactory
{
	// Le tableau d'upgrade s'utilise comme ce qu'il suit :
	//  raw vector [ 0 , 1 , 2,  3, ..]
	//			     |   |   |   |     
	//	skillIds   [ a,  b,  c,  d, ..]
	//  a = UpgradeID slot 1, b = upgradeID slot2, etc..
	// --------------------------------------------------------
	//
	//	Create all the skills first.
	//

public:
	SkillFactory();
	~SkillFactory();

	void submit(const std::string& skillName, Skill* skillToRegister);

	Skill* build( const std::string& skillName) const;
	
	Skill* getBuiltSkill(const std::string& skillName);

	void flushSkillMap(void);

	void eraseSkill(const std::string& skillName);

private:
	std::map<std::string, Skill*>	_SkillMap;
};

