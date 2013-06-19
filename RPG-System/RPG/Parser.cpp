#include "Parser.h"

#include "Map.h"
// include game object types
#include "GameObject.h"
#include "HeroCharacter.h"
#include "LocalObject.h"
#include "QuestItem.h"
#include "Chest.h"
#include "Door.h"
#include "LocalObject.h"
#include "Enemy.h"
#include "StepOnScriptObj.h"
// include scripts
#include "Script.h"
#include "Scripts.h"
#include "IFScript.h"
#include "Dialog.h"
#include "GiveItem.h"
#include "NoScript.h"
#include "ChangeMap.h"
#include "EndingScript.h"
// Graphics types
#include "Graphics.h"
#include "NoGraphics.h"
#include "StaticGraphics.h"
// movement types
#include "Movement.h"
#include "NoMovement.h"
#include "UserMovement.h"
#include "RandMovement.h"
#include "FollowIdMovement.h"

#include <iostream>
#include <fstream>

#include "Bank.h"

// Constructor
// create the database for the make functions
Parser::Parser(istream& infd) : _infd(infd)
{
	_gameObjFactoryMap["LOCALOBJECT"] = &Parser::makeLocalObject;
	_gameObjFactoryMap["ENEMY"] = &Parser::makeEnemy;
	_gameObjFactoryMap["DOOR"] = &Parser::makeDoor;
	_gameObjFactoryMap["CHEST"] = &Parser::makeChest;
	_gameObjFactoryMap["STEPON"] = &Parser::makeStepOnScriptObj;

	_scriptFactoryMap["SCRIPTS"] = &Parser::readScripts;
	_scriptFactoryMap["NOSCRIPT"] = &Parser::readNoScript;
	_scriptFactoryMap["DIALOG"] = &Parser::readDialog;
	_scriptFactoryMap["GIVEITEM"] = &Parser::readGiveItem;
	_scriptFactoryMap["IFQITEM"] = &Parser::readIFQItem;
	_scriptFactoryMap["IFLEVEL"] = &Parser::readIFLevel;
	_scriptFactoryMap["CHANGEMAP"] = &Parser::readChangeMap;
	_scriptFactoryMap["ENDING"] = &Parser::readEndingScript;

	_movementFactoryMap["NOMOVEMENT"] = &Parser::readNoMovement;
	_movementFactoryMap["RANDMOVEMENT"] = &Parser::readRandMovement;
	_movementFactoryMap["USERMOVEMENT"] = &Parser::readUserMovement;
	_movementFactoryMap["FOLLOWIDMOVEMENT"] = &Parser::readFollowIdMovement;
}

// read data from file and add GameObjects to map accordingly
void Parser::Read(Map& map)
{
	while (true) // end condition is finding END instead of a game object to create
	{
		std::string temp;
		_infd >> temp;

		if (temp == "END") // end condition
			break;
		else if (temp == "#") // documentation
		{
			getline(_infd, temp); // skip line
			continue; // start over
		}

		// create object
		shared_ptr<GameObject> obj = (this->*_gameObjFactoryMap.at(temp))(_infd);

		// get position on map
		unsigned pos;
		try { _infd >> pos; }
		catch (...) { std::cerr << "bad position"; break; }

		// add to map
		map.addGameObject(obj, pos);
	} 
}

// read graphics from file
Graphics* Parser::readGraphics(istream& infd)
{
	string type;
	infd >> type; // graphics type
	if (type == "NOGRAPHICS")
		return new NoGraphics;

	string filename;
	sf::Vector2i loc_on_file;
	sf::Vector2u size;
	try { // reading location and size
		infd >> filename >> loc_on_file.x >> loc_on_file.y >> size.x >> size.y;
	}
	catch (...) { throw std::exception("can't read graphics"); }

	if (type == "STATICGRAPHICS")
		return new StaticGraphics(&(Bank<sf::Texture>::getInstance().get(filename)), loc_on_file, size);

	else return new Graphics(&(Bank<sf::Texture>::getInstance().get(filename)), loc_on_file, size);

	return new NoGraphics;
}
// read movement
Movement* Parser::readMovement(istream& infd)
{
	string movement;
	infd >> movement;

	return  (this->*_movementFactoryMap.at(movement))(_infd);
}
// read user movement
Movement* Parser::readUserMovement(istream& infd)
{
	return new UserMovement;
}
// read random movement
Movement* Parser::readRandMovement(istream& infd)
{
	float time_between_moves;
	try {
		infd >> time_between_moves;
	} catch(...) { throw std::exception("couldn't read time between moves of random movement"); }
	return new RandMovement(time_between_moves);
}
// read follow id movement
Movement* Parser::readFollowIdMovement(istream& infd)
{
	int id;
	float radius;
	try {
		infd >> id >> radius;
	} catch(...) { throw std::exception("couldn't read follow movement"); }

	return new FollowIdMovement(id, radius);
}
// read no movement
Movement* Parser::readNoMovement(istream& infd)
{
	return new NoMovement;
}

// ================================================================================================
// make objects

// make local object
shared_ptr<GameObject> Parser::makeLocalObject(istream& infd)
{
	string script_name;
	infd >> script_name;

	// read script
	shared_ptr<Script> (Parser::*readscript)(istream& infd) = _scriptFactoryMap.at(script_name);
	shared_ptr<Script> script = (this->*readscript)(infd);
	
	// read movement and graphics and return local object
	return shared_ptr<GameObject>(new LocalObject( script, readGraphics(infd), readMovement(infd), false));
}

// make enemy
shared_ptr<GameObject> Parser::makeEnemy(istream& infd)
{
	unsigned atk, def, lck, hp;
	try { // read stats
		infd >> atk >> def >> lck >> hp;
	} catch(...) { throw std::exception("couldn't read enemy stats"); }

	// make stats
	Stats stats(atk, def, lck);

	// read movement and graphics and return enemy
	return shared_ptr<GameObject>(new Enemy(readGraphics(infd), readMovement(infd), stats, hp));
}
// make door
shared_ptr<GameObject> Parser::makeDoor(istream& infd)
{
	// read change map script and return door
	return shared_ptr<GameObject>(new Door(readChangeMap(infd)));
}

// make chest
shared_ptr<GameObject> Parser::makeChest(istream& infd)
{
	string item;
	infd >> item; // read item
	// return chest
	return shared_ptr<GameObject>(new  Chest(item));
}

// make step on script object.
shared_ptr<GameObject> Parser::makeStepOnScriptObj(istream& infd)
{
	string script_name;
	infd >> script_name;

	// read script
	shared_ptr<Script> (Parser::*readscript)(istream& infd) = _scriptFactoryMap.at(script_name);
	shared_ptr<Script> script = (this->*readscript)(infd);

	// make obj and return it
	return shared_ptr<GameObject>(new StepOnScriptObj(script));
}

// ==========================================================================
// scripts

// read dialog
shared_ptr<Script> Parser::readDialog(istream& infd)
{
	string str;
	getline(infd, str); // get string of dialog
	// return dialog script
	return shared_ptr<Script>(new Dialog(str));
}
// read ending script
shared_ptr<Script> Parser::readEndingScript(istream& infd)
{
	string str;
	getline(infd, str); // get string to show at the end
	// return Ending script
	return shared_ptr<Script>(new EndingScript(str));
}

// read give item script
shared_ptr<Script> Parser::readGiveItem(istream& infd)
{
	string item_name;
	infd >> item_name;
	return shared_ptr<Script>(new GiveItem(item_name));
}

// read IF Script: IFQItem
shared_ptr<Script> Parser::readIFQItem(istream& infd)
{
	shared_ptr<Script> if_s, else_s;

	string item_name;
	infd >> item_name; // item name to question about

	string script_name;

	infd >> script_name; // read if script
	if_s = (this->*_scriptFactoryMap.at(script_name))(infd);
	infd >> script_name; // read else script
	else_s = (this->*_scriptFactoryMap.at(script_name))(infd);

	// return IFQItem script
	return shared_ptr<Script>(new IFQItem(item_name, if_s, else_s));
}

// read IF Script: IFLevel
shared_ptr<Script> Parser::readIFLevel(istream& infd)
{
	shared_ptr<Script> if_s, else_s;
	unsigned level;
	try {
		infd >> level;
	} catch (...) { throw std::exception("couldn't read level on iflevel script"); }

	string script_name;
	// read if and else scripts
	infd >> script_name;
	if_s = (this->*_scriptFactoryMap[script_name])(infd);
	infd >> script_name;
	else_s = (this->*_scriptFactoryMap[script_name])(infd);

	// return iflevel script.
	return shared_ptr<Script>(new IFLevel(level, if_s, else_s));
}

// read multiple scripts
shared_ptr<Script> Parser::readScripts(istream& infd)
{
	string script_name;
	infd >> script_name;
	vector<shared_ptr<Script>> scripts; // vector of scripts
	while (script_name != "END") // end condition
	{
		// add script
		scripts.push_back(((this->*_scriptFactoryMap.at(script_name))(infd)));
		infd >> script_name; // read new script name
	}
	// make Scripts object from the scripts vector we read and return it
	return shared_ptr<Script>(new Scripts(scripts));
}

// No script.
shared_ptr<Script> Parser::readNoScript(istream& infd)
{
	return shared_ptr<Script>(new NoScript);
}

// change map script
shared_ptr<Script> Parser::readChangeMap(istream& infd)
{
	string map_name;
	infd >> map_name;

	unsigned s_pos; // starting pos on new map
	try {
		infd >> s_pos;
	} catch (...) { throw std::exception("bad pos on change map script"); }

	return shared_ptr<Script>(new ChangeMap(map_name, s_pos));
}




