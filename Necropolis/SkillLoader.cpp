#include "SkillLoader.h"
#include "Spell.h"
#include "Technique.h"


// SKill Effects : Temporary :: Need a factory ASAP
#include "Ignite.h"
// ---------------------------------------------


// ------------------------------------
// load
// ------------------------------------
int SkillLoader::load(std::string fileName, const char* filePath, json & oFile)
{
	if (fileName.empty())
		return -1;

	// OPEN
	std::string fullPath = filePath + fileName + ".json";
	json File;
	std::ifstream fstream ;
	fstream.open(fullPath);
	if (!fstream.is_open())
		return -1;

	// READ
	std::string toDeserialize;
	std::string line;
	std::istringstream sLine;
	while ( std::getline(fstream, line) )
	{
		if (line.empty()) 
			continue;
		toDeserialize.append(line);
	}
	const char * c = toDeserialize.c_str() ; 
	File = json::parse( c );

	// CLOSE
	fstream.close();
	if (fstream.is_open())
		return -1;
	oFile = File;
	return S_OK;
}


// ------------------------------------
// save
// ------------------------------------
int SkillLoader::save(std::string fileName, const char* filePath, json fileToSave, json & oFile)
{
	if (fileName.empty()) 
		return -1;

	// OPEN
	std::string fullPath = filePath + fileName + ".json";
	json File;
	std::ofstream fstream;
	fstream.open(fullPath);
	if (!fstream.is_open())
		return -1;

	// WRITE
	fstream << fileToSave.dump(4);

	// CLOSE
	fstream.close();
	if (fstream.is_open())
		return -1;
	oFile = File;
	return S_OK;
}


// ------------------------------------
// loadSkill
// ------------------------------------
int SkillLoader::loadSkill(std::string skillName, Skill *& opSkill)
{

	if (skillName.empty())
		return E_INVALIDARG;
	if (NULL != opSkill)
		return E_INVALIDARG;

	// Load the skill
	json File = NULL;
	int retval = SkillLoader::load(skillName, SKILLPATH, File);
	if ( (retval < 0) || File.empty() )
		return -1;

	// Create the corresponding skill structure
	std::string key;
	Skill  * skill = NULL;
	for (json::iterator it = File.begin(); it != File.end(); ++it)
	{
		key = it.key().c_str();

		// Skill Nature
		if (key.compare("SkillNature") == 0)
		{
			std::string value = it.value();
			if (value.compare("Spell"))
				skill = new Spell();
			else
				skill = new Technique();
			break;
		}
		else if (skill == NULL)
			continue;

		else
		{
			std::cerr << "Skill Nature must be define first to create the appropriate structure." << std::endl;
			return E_FAIL;
		}
	}

	// Read flags to fill in the skill
	for (json::iterator it = File.begin(); it != File.end(); ++it)
	{
		key = it.key().c_str();

		if (key.compare("SkillName") == 0)
		{
			std::string value = it.value();
			skill->setSkillName(value);
		}
		else if (key.compare("MPCost") == 0)
		{
			int value = it.value();
			skill->setMPCost(value);
		}
		else if (key.compare("Aspect") == 0)
		{
			int value = it.value();
			skill->setAspect(value);
		}
		else if (key.compare("Target") == 0)
		{
			int value = it.value();
			skill->setTarget(value);
		}
		else if (key.compare("CastSpeed") == 0)
		{
			double value = it.value();
			skill->setCastSpeed(value);
		}
		else if (key.compare("SkillValue") == 0)
		{
			int value = it.value();
			skill->setSkillValue(value);
		}
		else if (key.compare("ElementalAttributes") == 0)
		{
			ElementalArray elems = ElementalArray();
			json value = it.value();
			for (json::iterator iter = value.begin(); iter != value.end(); ++iter)
			{
				std::string elementalLabel	= iter.key().c_str();
				int elementalValue			= iter.value();

				if (elementalLabel.compare("EARTH") == 0)
					elems.setEarth(elementalValue);
				else if (elementalLabel.compare("AIR") == 0)
					elems.setAir(elementalValue);
				else if (elementalLabel.compare("FIRE") == 0)
					elems.setFire(elementalValue);
				else if (elementalLabel.compare("WATER") == 0)
					elems.setWater(elementalValue);
				else if (elementalLabel.compare("LIGHT") == 0)
					elems.setLight(elementalValue);
				else if (elementalLabel.compare("DARK") == 0)
					elems.setDark(elementalValue);
				else // Unexpected
					std::cerr << " Unexpected elemental attribute during the skill deserialization " << std::endl;
			}	
			skill->setElementalAttributes(elems);
		}
		else if (key.compare("ListOfSkillEffects") == 0)
		{
			// Load strings
			std::vector<std::string> effects;
			json value = it.value();
			for (json::iterator iter = value.begin(); iter != value.end(); ++iter)
				effects.push_back(*iter);
			

			// Transform in tokens
			std::vector<Token*> skillEffects = std::vector<Token*>();
			if (tokenizeSkillEffects(effects, skillEffects) < 0)
				return E_FAIL; 

			skill->setListOfSkillEffects(skillEffects);
		}
		else if (key.compare("Upgrades") == 0)
		{
			json value = it.value();
			std::string upgradeName;
			int currentMastery = 0;
			int upgradeLevel = 0;
			std::vector<int> upgradeSockets;
			std::vector<int> upgradeCeilings;

			for (json::iterator iter = value.begin(); iter != value.end(); ++iter)
			{
				std::string upgradeLabel = iter.key().c_str();
				
				if (upgradeLabel.compare("Name") == 0)
				{
					std::string localUpgradeName = iter.value();
					upgradeName = localUpgradeName;
				}
				else if (upgradeLabel.compare("CurrentMastery") == 0)
					currentMastery = iter.value();
				else if (upgradeLabel.compare("UpgradeLevel") == 0)
					upgradeLevel = iter.value();
				else if (upgradeLabel.compare("UpgradeSockets") == 0)
				{
					std::vector<int> localUpgradeSockets = iter.value();
					upgradeSockets = localUpgradeSockets;
				}

				else // Unexpected
					std::cerr << " Unexpected upgrade attribute during the skill deserialization " << std::endl;
			}

			// Now load the actual upgrade
			Upgrade * upgradeBundle = new Upgrade();
			if ( 0 > loadUpgrade(upgradeName, currentMastery, upgradeLevel, upgradeSockets, upgradeBundle) )
			{
				std::cerr << "SL001 : Failed to load an upgrade" << std::endl;
				return E_FAIL;
			}
		}
		else
		{
		}
	}

	// Close
	opSkill = skill;
	return S_OK;
}

int SkillLoader::loadUpgrade(std::string upgradeName, const int currentMastery, const int upgradeLevel, std::vector<int> upgradeSockets, Upgrade *& upgradeBundle)
{
	if ( upgradeName.empty() || upgradeSockets.empty() )
		return E_INVALIDARG;

	if (NULL == upgradeBundle)
		upgradeBundle = new Upgrade();

	if (upgradeLevel == 0)
		return S_FALSE;


	// Load the skill
	json File = NULL;
	int retval = SkillLoader::load(upgradeName, UPGRADEPATH, File);
	if ((retval < 0) || File.empty())
		return E_FAIL;

	// Tranform values into string so we can compare the thingz
	std::stringstream ss;

	ss << currentMastery;
	std::string s_currentMaster = ss.str();

	ss << upgradeLevel;
	std::string s_upgradeLevel = ss.str();

	int n_upgradeSockets = upgradeSockets.size();
	std::vector<std::string> s_upgradeSockets;
	s_upgradeSockets.resize(n_upgradeSockets);
	for (int i(0); i < n_upgradeSockets; ++i)
	{
		ss << upgradeSockets.at(i);
		s_upgradeSockets.at(i) = ss.str();
	}


	// Create the corresponding upgrade structure
	std::vector<int> upgradeCeilings;
	std::string key;
	Upgrade  * upgrade = NULL;
	upgrade = new Upgrade();
	int currentUpgradeSlot = 0;
	int currentLabelSocket = 0;
	std::string::size_type sz;

	for (json::iterator it = File.begin(); it != File.end(); ++it)
	{
		std::string upgradeLabel = it.key().c_str();
		currentUpgradeSlot = std::stoi(upgradeLabel, &sz);
		if (currentUpgradeSlot < 0)
		{
			std::cerr << "SL002 : currentUpgradeSLot is inferior to 0 !" << std::endl;
			continue;
		}
		json upgradeLayer = it.value();

		for (json::iterator layer_it = upgradeLayer.begin(); layer_it != upgradeLayer.end(); ++layer_it)
		{

			std::string upgradeInnerLabel = layer_it.key().c_str();

			if (upgradeLabel.compare("MasteryCeiling") == 0)
			{
				// ..
			}
			else if (upgradeLabel.compare("MasteryObjective") == 0)
			{
				// ..
			}
			else
			{
				currentLabelSocket = std::stoi(upgradeLabel, &sz);
				if (currentUpgradeSlot < 0)
				{
					std::cerr << "SL003 : currentLabelSocket is inferior to 0 !" << std::endl;
					continue;
				}

				json upgradeSocketValue = layer_it.value();
				std::string upgradeInnerLabel;

				for (json::iterator socket_layer_it = upgradeSocketValue.begin(); socket_layer_it != upgradeSocketValue.end(); ++socket_layer_it)
				{
					upgradeInnerLabel = socket_layer_it.key().c_str();
					std::string upgradeInnerValue = socket_layer_it.value();
					if ( upgradeInnerLabel.compare("Description") == 0 )
					{
						upgrade->description = upgradeInnerValue;
					}
					else if ( !upgradeInnerLabel.empty() )
					{
						// Any upgrade item
						if (S_OK != upgrade->setUpgradeValue(upgradeInnerLabel, upgradeInnerValue))
						{
							std::cerr << " SL003 : An error occured while setting the upgrade" << std::endl;
						}
					}
					else
					{
						// ..
					}
				} // EoL Socket
			}
		} // EoL Inner Upgrade
	} // EoL Upgrade File

	upgradeBundle = upgrade;
	return S_OK;
}


// ------------------------------------
// tokenizeSkillEffects
// ------------------------------------
int SkillLoader::tokenizeSkillEffects(std::vector<std::string> iEffects, std::vector<Token*>& oEffects)
{
	int n_effects = iEffects.size();
	if (n_effects <= 0)
		return 1;

	std::vector<Token*> localListOfEffects = std::vector<Token*>();
	for (int i_effect = 0; i_effect < n_effects; ++i_effect)
	{
		std::string currentEffect = iEffects.at(i_effect);
		if (currentEffect.empty()) 
			continue;
		// INSERT LIST OF EXISTING EFFECTS
		Token * newEffect = NULL;
		if (currentEffect.compare("IGNITE") == 0)
			newEffect = new Ignite();

		localListOfEffects.push_back(newEffect);
		// -----------------------------------
	}


	if (localListOfEffects.size() > 0)
		oEffects = localListOfEffects;

	return 1;
}


SkillLoader::SkillLoader()
{
}


SkillLoader::~SkillLoader()
{
}
