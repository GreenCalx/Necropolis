#pragma once
#include <vector>
#include "SkillPrototype.h"
#include "Token.h"
#include "ElementalArray.h"

class Skill : public SkillPrototype<Skill>
{
public:
	
	// Skill aspects % defines its archetype
	enum ASPECT{
		OFFENSIVE, DEFENSIVE, MOVEMENT, MODIFICATOR, CONTROL
	};
	// Target of the Skill % will Probably be needed for GUI stuff
	enum TARGET {
		SELF, OTHER
	};

	// Constructors
	// ---------------------
	Skill() 
		: _MPCost(0), _ElementalAttributes(ElementalArray()), _SkillValue(0), _Aspect(MODIFICATOR), _ListOfSkillEffects(0), _Target(SELF), _CastSpeed(0.1), _Upgrades(0) 
		{};

	Skill(int mpCost, ElementalArray elementalAttributes, double skillValue, ASPECT aspect, std::vector<Token> * ListOfSkillEffects, TARGET target, double castSpeed, std::vector<int>* upgrades)
		: _MPCost(mpCost), _ElementalAttributes(elementalAttributes), _SkillValue(skillValue), _Aspect(aspect), _ListOfSkillEffects(ListOfSkillEffects), _Target(target), _CastSpeed(castSpeed), _Upgrades(upgrades)
		{} ;
	
	~Skill();

	// virtuals
	// ---------------------
	virtual void cast() = 0;

	// mutators
	// ---------------------
	 int		getMPCost()				{ return _MPCost; }
	 void	setMPCost(int mp)		{ _MPCost = mp; }

	ElementalArray	getElementalAttributes()									{ return _ElementalAttributes; }
	void			setElementalAttributes(ElementalArray ElementalAttributes)	{ _ElementalAttributes = ElementalAttributes; }

	double	getSkillValue()						{ return _SkillValue; }
	void	setSkillValue(double SkillValue)	{ _SkillValue = SkillValue; }

	ASPECT	getAspect()					{ return _Aspect; }
	void	setAspect(ASPECT Aspect)	{ _Aspect = Aspect; }

	std::vector<Token>*	getListOfSkillEffects()											{ return _ListOfSkillEffects; }
	void				setListOfSkillEffects(std::vector<Token> * ListOfSkillEffects)	{ _ListOfSkillEffects = ListOfSkillEffects; }

	TARGET	getTarget()					{ return _Target; }
	void	setTarget(TARGET Target)	{ _Target = Target; }

	double	getCastSpeed()					{ return _CastSpeed; }
	void	setCastSpeed(double CastSpeed)	{ _CastSpeed = CastSpeed; }

	std::vector<int>*	getUpgrades() { return _Upgrades; }
	void	setUpgrades(std::vector<int>* CastSpeed) { _Upgrades = _Upgrades; }


protected:
	int							_MPCost;
	ElementalArray				_ElementalAttributes;
	double						_SkillValue;			// Value that can be use to define damage/heal
	ASPECT						_Aspect; //
	std::vector<Token>		*	_ListOfSkillEffects;
	TARGET						_Target;
	double						_CastSpeed;
	std::vector<int>		*	_Upgrades;
};

