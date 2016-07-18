#include "SkillLoader.h"
#include "Spell.h"
#include "Technique.h"

#define	 SKILLPATH	"Data/Skills/"

// SKill Effects : Temporary :: Need a factory ASAP
#include "Ignite.h"
// ---------------------------------------------


// ------------------------------------
// load
// ------------------------------------
int SkillLoader::load(std::string fileName, json & oFile)
{
	if (fileName.empty())
		return -1;

	// OPEN
	std::string fullPath = SKILLPATH + fileName + ".json";
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
	std::cout << c << std::endl;
	File = json::parse( c );
	std::cout << File.dump(4) << std::endl;

	// CLOSE
	fstream.close();
	if (fstream.is_open())
		return -1;
	oFile = File;
	return 1;
}


// ------------------------------------
// save
// ------------------------------------
int SkillLoader::save(std::string fileName, json fileToSave, json & oFile)
{
	if (fileName.empty()) 
		return -1;

	// OPEN
	std::string fullPath = SKILLPATH + fileName + ".json";
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
	return 1;
}


// ------------------------------------
// loadSkill
// ------------------------------------
int SkillLoader::loadSkill(std::string skillName, Skill *& opSkill)
{

	if (skillName.empty())
		return -1;
	if (NULL != opSkill)
		return -1;

	// Load the skill
	json File = NULL;
	int retval = SkillLoader::load(skillName, File);
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
			return -1;
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
				return -1; // Todo : Handle it better later on.

			skill->setListOfSkillEffects(skillEffects);
		}
		else if (key.compare("Upgrades") == 0)
		{

		}
		else
		{
		}
	}

	// Close
	opSkill = skill;
	return 1;
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
