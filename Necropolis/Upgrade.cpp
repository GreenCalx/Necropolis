#include "Upgrade.h"
#include "Defines.h"
#include <string>

#include "Ignite.h"

int Upgrade::setUpgradeValue(std::string valueLabel, std::string value)
{
	if (valueLabel.empty() || value.empty()) 
		return E_INVALIDARG;

	if (valueLabel.compare("Radius") == 0)
	{
		double d_val = std::stod( value.c_str() );
		radius += d_val;
	}
	else if (valueLabel.compare("BlastRadius") == 0)
	{
		double d_val = std::stod(value.c_str());
		blastRadius += d_val;
	}
	else if (valueLabel.compare("ProjectileImpulse") == 0)
	{
		double d_val = std::stod(value.c_str());
		projectileImpulse += d_val;
	}
	else if (valueLabel.compare("ProjectileWeight") == 0)
	{
		double d_val = std::stod(value.c_str());
		projectileWeight += d_val;
	}
	else if (valueLabel.compare("SkillValue") == 0)
	{
		double d_val = std::stod(value.c_str());
		skillValue += d_val;
	}
	else if (valueLabel.compare("SkillCost") == 0)
	{
		double d_val = std::stod(value.c_str());
		skillCost += d_val;
	}
	else if (valueLabel.compare("CastSpeed") == 0)
	{
		double d_val = std::stod(value.c_str());
		castSpeed += d_val;
	}
	else if (valueLabel.compare("NumberOfProjectiles") == 0)
	{
		int i_val = atoi(value.c_str());
		numberOfProjectiles += i_val;
	}
	else if (valueLabel.compare("SkillEffect") == 0)
	{
		if (value.compare("Ignite")) {
			Ignite&  ignite = Ignite();
			skillEffects.push_back( ignite );
		}
		else
		{
			// ..
		}
	}
	else
	{
		// ...
		std::cerr << " WARN >> UPGR01 : Unkown upgrade label." << std::endl;
		return S_FALSE;
	}

	return S_OK;
}
