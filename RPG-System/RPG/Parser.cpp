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
// include scripts
#include "Script.h"
#include "Scripts.h"
#include "IFScript.h"
#include "Dialog.h"
#include "GiveItem.h"
#include "NoScript.h"

#include <iostream>
#include <fstream>



void Parser::Read(Map& map)
{
	while (true)
	{
		std::string temp;
		*_infd >> temp;
		if (temp == "END") // end condition
			break;

		shared_ptr<GameObject> obj = (this->*_gameObjFactoryMap[temp])(_infd);

		unsigned pos;
		try { *_infd >> pos; }
		catch (...) { std::cerr << "bad position"; break; }

		map.addGameObject(obj, pos);
	} 
}


Graphics* Parser::readGraphics()
{
	return NULL;
}
Movement* Parser::readMovement()
{
	return NULL;
}


shared_ptr<GameObject> Parser::makeNPC(shared_ptr<istream>& infd)
{
	string script_name;
	*infd >> script_name;
	return shared_ptr<GameObject>(new NPC( (this->*_scriptFactoryMap[script_name])(infd), readGraphics(), readMovement(), false));
}
shared_ptr<GameObject> Parser::makeDoor(shared_ptr<istream>& infd)
{
	string map_name;
	*infd >> map_name;

	unsigned s_pos;
	*infd >> s_pos;

	return shared_ptr<GameObject>(new Door(map_name, s_pos));
}
shared_ptr<GameObject> Parser::makeChest(shared_ptr<istream>& infd)
{
	string item;
	*infd >> item;
	return shared_ptr<GameObject>(new  Chest(item));
}
	
shared_ptr<Script> Parser::readDialog(shared_ptr<istream>& infd)
{
	string str;
	getline(*infd, str);
	return shared_ptr<Script>(new Dialog(str));
}
shared_ptr<Script> Parser::readGiveItem(shared_ptr<istream>& infd)
{
	string item_name;
	*infd >> item_name;
	return shared_ptr<Script>(new GiveItem(item_name));
}
shared_ptr<Script> Parser::readIFQItem(shared_ptr<istream>& infd)
{
	shared_ptr<Script> if_s, else_s;
	string item_name;
	*infd >> item_name;

	string script_name;
	*infd >> script_name;
	if_s = (this->*_scriptFactoryMap[script_name])(infd);
	*infd >> script_name;
	else_s = (this->*_scriptFactoryMap[script_name])(infd);
	return shared_ptr<Script>(new IFQItem(item_name, if_s, else_s));
}
shared_ptr<Script> Parser::readIFLevel(shared_ptr<istream>& infd)
{
	shared_ptr<Script> if_s, else_s;
	unsigned level;
	*infd >> level;

	string script_name;
	*infd >> script_name;
	if_s = (this->*_scriptFactoryMap[script_name])(infd);
	*infd >> script_name;
	else_s = (this->*_scriptFactoryMap[script_name])(infd);
	return shared_ptr<Script>(new IFLevel(level, if_s, else_s));
}
shared_ptr<Script> Parser::readScripts(shared_ptr<istream>& infd)
{
	string script_name;
	*infd >> script_name;
	vector<shared_ptr<Script>> scripts;
	while (script_name != "END")
	{
		scripts.push_back((this->*_scriptFactoryMap[script_name])(infd));
		*infd >> script_name;
	}
	return shared_ptr<Script>(new Scripts(scripts));
}
shared_ptr<Script> Parser::readNoScript(shared_ptr<istream>& infd)
{
	return shared_ptr<Script>(new NoScript);
}














/*

shared_ptr<GameObject> Parser::readObject(const string& obj_name)
{
	if (obj_name == "NPC")
	{
		string script_name;
		*_infd >> script_name;
		return shared_ptr<GameObject>(new NPC(readScript(script_name), readGraphics(), readMovement(), false));
	}
	if (obj_name == "DOOR")
	{
		string map_name;
		*_infd >> map_name;

		unsigned s_pos;
		*_infd >> s_pos;

		return shared_ptr<GameObject>(new Door(map_name, s_pos));
	}
	else if (obj_name == "CHEST")
	{
		string item;
		*_infd >> item;
		return shared_ptr<GameObject>(new  Chest(item));
	}
	string script_name;
	*_infd >> script_name;
	return shared_ptr<GameObject>(new LocalObject(readScript(script_name), readGraphics(), readMovement(), true));
}
shared_ptr<Script> Parser::readScript(string temp)
{
	if (temp == "DIALOG")
	{
		getline(*_infd, temp);
		return shared_ptr<Script>(new Dialog(temp));
	}
	else if (temp == "GIVEITEM")
	{
		*_infd >> temp;
		return shared_ptr<Script>(new GiveItem(temp));
	}
	else if (temp == "SCRIPTS")
	{
		*_infd >> temp;
		vector<shared_ptr<Script>> scripts;
		while (temp != "END")
		{
			scripts.push_back(readScript(temp));
			*_infd >> temp;
		}
		return shared_ptr<Script>(new Scripts(scripts));
	}
	else if (temp == "IFQITEM")
	{
		shared_ptr<Script> if_s, else_s;
		string item_name;
		*_infd >> item_name;
		*_infd >> temp;
		if_s = readScript(temp);
		*_infd >> temp;
		else_s = readScript(temp);
		return shared_ptr<Script>(new IFQItem(item_name, if_s, else_s));
	}
	else if (temp == "IFLevel")
	{
		shared_ptr<Script> if_s, else_s;
		unsigned level;
		*_infd >> level;
		*_infd >> temp;
		if_s = readScript(temp);
		*_infd >> temp;
		else_s = readScript(temp);
		return shared_ptr<Script>(new IFLevel(level, if_s, else_s));
	}
	return shared_ptr<Script>(new NoScript);
}

*/



