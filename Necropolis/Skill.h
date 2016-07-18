#pragma once
#include <vector>
#include "SkillPrototype.h"
#include "Token.h"
#include "ElementalArray.h"
#include "SkillEffect.h"

class Skill : public SkillPrototype<Skill>
{
public:
	
	// Skill aspects % defines its archetype
	enum ASPECT{
		OFFENSIVE	= 0,
		DEFENSIVE	= 1,
		MOVEMENT	= 2,
		MODIFICATOR = 3,
		CONTROL		= 4
	};
	// Target of the Skill % will Probably be needed for GUI stuff
	enum TARGET {
		SELF	= 0,
		OTHER	= 1
	};

	// Constructors
	// ---------------------
	Skill() 
		: _MPCost(0), _ElementalAttributes(ElementalArray()), _SkillValue(0), _Aspect(MODIFICATOR), _ListOfSkillEffects(0), _Target(SELF), _CastSpeed(0.1), _Upgrades(0) 
		{};

	Skill(int mpCost, ElementalArray elementalAttributes, double skillValue, ASPECT aspect, std::vector<Token*>  ListOfSkillEffects, TARGET target, double castSpeed, std::vector<int>* upgrades)
		: _MPCost(mpCost), _ElementalAttributes(elementalAttributes), _SkillValue(skillValue), _Aspect(aspect), _ListOfSkillEffects(ListOfSkillEffects), _Target(target), _CastSpeed(castSpeed), _Upgrades(upgrades)
		{} ;
	
	~Skill();

	// virtuals
	// ---------------------
	virtual void cast() = 0;

	// mutators
	// ---------------------
	std::string		getSkillName() { return _SkillName; }
	void			setSkillName(std::string SkillName) { _SkillName = SkillName; }

	 int		getMPCost()				{ return _MPCost; }
	 void	setMPCost(int mp)		{ _MPCost = mp; }

	ElementalArray	getElementalAttributes()									{ return _ElementalAttributes; }
	void			setElementalAttributes(ElementalArray ElementalAttributes)	{ _ElementalAttributes = ElementalAttributes; }

	double	getSkillValue()						{ return _SkillValue; }
	void	setSkillValue(double SkillValue)	{ _SkillValue = SkillValue; }

	ASPECT	getAspect()					{ return _Aspect; }
	void	setAspect(ASPECT Aspect)	{ _Aspect = Aspect; }
	void	setAspect(int Aspect) { if (Aspect<0 || Aspect>4) return; _Aspect = static_cast<ASPECT>(Aspect); }

	std::vector<Token*>	getListOfSkillEffects()											{ return _ListOfSkillEffects; }
	void				setListOfSkillEffects(std::vector<Token*>  ListOfSkillEffects)	{ _ListOfSkillEffects = ListOfSkillEffects; }

	TARGET	getTarget()					{ return _Target; }
	void	setTarget(TARGET Target)	{ _Target = Target; }
	void	setTarget(int Target) { if (Target<0 || Target>1) return; _Target = static_cast<TARGET>(Target); }

	double	getCastSpeed()					{ return _CastSpeed; }
	void	setCastSpeed(double CastSpeed)	{ _CastSpeed = CastSpeed; }

	std::vector<int>*	getUpgrades() { return _Upgrades; }
	void	setUpgrades(std::vector<int>* CastSpeed) { _Upgrades = _Upgrades; }


protected:
	std::string					_SkillName;
	int							_MPCost;
	ElementalArray				_ElementalAttributes;
	double						_SkillValue;			// Value that can be use to define damage/heal
	ASPECT						_Aspect; //
	std::vector<Token*>			_ListOfSkillEffects;
	TARGET						_Target;
	double						_CastSpeed;
	std::vector<int>		*	_Upgrades;
};

