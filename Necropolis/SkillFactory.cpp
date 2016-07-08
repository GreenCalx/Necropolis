#include "SkillFactory.h"



SkillFactory::SkillFactory()
{
}


SkillFactory::~SkillFactory()
{
}

void SkillFactory::submit(const std::string & skillName, Skill * skillToRegister)
{
	if ( _SkillMap.find(skillName) == _SkillMap.end() )
	{
		// Skill doesn't exists within the map
		_SkillMap[skillName] = skillToRegister;
	}
}

Skill * SkillFactory::build(const std::string & skillName) const
{
	Skill* skillToBuild = NULL;
	std::map<std::string, Skill*>::const_iterator it = _SkillMap.find(skillName);
	if (it != _SkillMap.end())
	{
		// Skill already exists within the map
		skillToBuild = ((*it).second)->Clone();
	}

	// Throw Exception if skill not found
	// TODO

	return skillToBuild;
}

Skill * SkillFactory::getBuiltSkill(const std::string & skillName)
{
	Skill* builtSkill = NULL;
	std::map<std::string, Skill*>::const_iterator it = _SkillMap.find(skillName);
	if ( it != _SkillMap.end() )
	{
		// Skill exists within the map
		builtSkill = _SkillMap[skillName];
	}
	return builtSkill;
}

void SkillFactory::flushSkillMap(void)
{
	_SkillMap.clear();
}

void SkillFactory::eraseSkill(const std::string & skillName)
{
	if (_SkillMap.find(skillName) == _SkillMap.end())
	{
		// Skill doesn't exists within the map
		_SkillMap.erase(skillName);
	}
}
