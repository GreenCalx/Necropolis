#include "SkillLoader.h"
#include "Spell.h"
#include "Technique.h"

#define	 SKILLPATH	"Data/Skills/"


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
			//ElementalArray value = it.value();

		}
		else if (key.compare("ListOfSkillEffects") == 0)
		{

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

SkillLoader::SkillLoader()
{
}


SkillLoader::~SkillLoader()
{
}
