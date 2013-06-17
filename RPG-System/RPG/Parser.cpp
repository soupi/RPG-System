#include "Parser.h"

#include "Map.h"
// include game object types
#include "GameObject.h"
#include "HeroCharacter.h"
#include "LocalObject.h"
#include "QuestItem.h"
#include "Chest.h"
#include "Door.h"
#include "NPC.h"
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

Parser::Parser(istream& infd) : _infd(infd)
{
	_gameObjFactoryMap["NPC"] = &Parser::makeNPC;
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

	_movementFactoryMap["NOMOVEMENT"] = &Parser::readNoMovement;
	_movementFactoryMap["RANDMOVEMENT"] = &Parser::readRandMovement;
	_movementFactoryMap["USERMOVEMENT"] = &Parser::readUserMovement;
	_movementFactoryMap["FOLLOWIDMOVEMENT"] = &Parser::readFollowIdMovement;
}

void Parser::Read(Map& map)
{
	while (true)
	{
		std::string temp;
		_infd >> temp;
		if (temp == "END") // end condition
			break;
		else if (temp == "#") // documentation
		{
			getline(_infd, temp);
			continue;
		}

		shared_ptr<GameObject> obj = (this->*_gameObjFactoryMap[temp])(_infd);

		unsigned pos;
		try { _infd >> pos; }
		catch (...) { std::cerr << "bad position"; break; }

		map.addGameObject(obj, pos);
	} 
}


Graphics* Parser::readGraphics(istream& infd)
{
	string type;
	infd >> type;
	if (type == "NOGRAPHICS")
		return new NoGraphics;
	string filename;
	sf::Vector2i loc_on_file;
	sf::Vector2u size;
	//try
	infd >> filename >> loc_on_file.x >> loc_on_file.y >> size.x >> size.y;
	//catch
	if (type == "STATICGRAPHICS")
		return new StaticGraphics(&(Bank<sf::Texture>::getInstance().get(filename)), loc_on_file, size);
	else return new Graphics(&(Bank<sf::Texture>::getInstance().get(filename)), loc_on_file, size);

	return new NoGraphics;
}
Movement* Parser::readMovement(istream& infd)
{
	string movement;
	infd >> movement;

	return  (this->*_movementFactoryMap[movement])(_infd);
}

Movement* Parser::readUserMovement(istream& infd)
{
	return new UserMovement;
}
Movement* Parser::readRandMovement(istream& infd)
{
	float time_between_moves;
	infd >> time_between_moves;
	return new RandMovement(time_between_moves);
}
Movement* Parser::readFollowIdMovement(istream& infd)
{
	int id;
	float radius;
	infd >> id >> radius;
	return new FollowIdMovement(id, radius);
}

Movement* Parser::readNoMovement(istream& infd)
{
	return new NoMovement;
}



shared_ptr<GameObject> Parser::makeNPC(istream& infd)
{
	string script_name;
	infd >> script_name;

	shared_ptr<Script> (Parser::*readscript)(istream& infd) = _scriptFactoryMap[script_name];
	shared_ptr<Script> script = (this->*readscript)(infd);
	return shared_ptr<GameObject>(new NPC( script, readGraphics(infd), readMovement(infd), false));
}

shared_ptr<GameObject> Parser::makeEnemy(istream& infd)
{
	unsigned atk, def, lck, hp;
	infd >> atk >> def >> lck >> hp;

	Stats stats(atk, def, lck);

	return shared_ptr<GameObject>(new Enemy(readGraphics(infd), readMovement(infd), stats, hp));
}

shared_ptr<GameObject> Parser::makeDoor(istream& infd)
{
	return shared_ptr<GameObject>(new Door(readChangeMap(infd)));
}
shared_ptr<GameObject> Parser::makeChest(istream& infd)
{
	string item;
	infd >> item;
	return shared_ptr<GameObject>(new  Chest(item));
}

shared_ptr<GameObject> Parser::makeStepOnScriptObj(istream& infd)
{
	string script_name;
	infd >> script_name;

	shared_ptr<Script> (Parser::*readscript)(istream& infd) = _scriptFactoryMap[script_name];
	shared_ptr<Script> script = (this->*readscript)(infd);
	return shared_ptr<GameObject>(new StepOnScriptObj(script));
}
shared_ptr<Script> Parser::readDialog(istream& infd)
{
	string str;
	getline(infd, str);
	return shared_ptr<Script>(new Dialog(str));
}
shared_ptr<Script> Parser::readGiveItem(istream& infd)
{
	string item_name;
	infd >> item_name;
	return shared_ptr<Script>(new GiveItem(item_name));
}
shared_ptr<Script> Parser::readIFQItem(istream& infd)
{
	shared_ptr<Script> if_s, else_s;
	string item_name;
	infd >> item_name;

	string script_name;
	infd >> script_name;
	if_s = (this->*_scriptFactoryMap[script_name])(infd);
	infd >> script_name;
	else_s = (this->*_scriptFactoryMap[script_name])(infd);
	return shared_ptr<Script>(new IFQItem(item_name, if_s, else_s));
}
shared_ptr<Script> Parser::readIFLevel(istream& infd)
{
	shared_ptr<Script> if_s, else_s;
	unsigned level;
	infd >> level;

	string script_name;
	infd >> script_name;
	if_s = (this->*_scriptFactoryMap[script_name])(infd);
	infd >> script_name;
	else_s = (this->*_scriptFactoryMap[script_name])(infd);
	return shared_ptr<Script>(new IFLevel(level, if_s, else_s));
}
shared_ptr<Script> Parser::readScripts(istream& infd)
{
	string script_name;
	infd >> script_name;
	vector<shared_ptr<Script>> scripts;
	while (script_name != "END")
	{
		scripts.push_back(((this->*_scriptFactoryMap[script_name])(infd)));
		infd >> script_name;
	}
	return shared_ptr<Script>(new Scripts(scripts));
}
shared_ptr<Script> Parser::readNoScript(istream& infd)
{
	return shared_ptr<Script>(new NoScript);
}

shared_ptr<Script> Parser::readChangeMap(istream& infd)
{
	string map_name;
	infd >> map_name;

	unsigned s_pos;
	infd >> s_pos;

	return shared_ptr<Script>(new ChangeMap(map_name, s_pos));
}




