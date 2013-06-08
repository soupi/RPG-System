#pragma once

// ######################################################################################
// #	The parser is a class that interpretes the file and creates Objects from it		#
// #	the one to call the parser is the map with the file stream it opened			#
// ######################################################################################

#include <fstream>
#include <memory>
#include <string>
#include <map>

using std::map;
using std::shared_ptr;
using std::istream;
using std::string;

class Map;
class GameObject;
class Script;
class Graphics;
class Movement;

class Parser
{
public:
	Parser(istream& infd);
	void Read(Map& map);
	Graphics* readGraphics(istream& infd);
	Movement* readMovement(istream& infd);


	// --------------------------------------------------------

	shared_ptr<GameObject> makeNPC(istream& infd);
	shared_ptr<GameObject> makeEnemy(istream& infd);
	shared_ptr<GameObject> makeDoor(istream& infd);
	shared_ptr<GameObject> makeChest(istream& infd);
	
	shared_ptr<Script> readDialog(istream& infd);
	shared_ptr<Script> readGiveItem(istream& infd);
	shared_ptr<Script> readIFQItem(istream& infd);
	shared_ptr<Script> readIFLevel(istream& infd);
	shared_ptr<Script> readScripts(istream& infd);
	shared_ptr<Script> readNoScript(istream& infd);

private:
	 istream& _infd;

	 map<string, shared_ptr<GameObject> (Parser::*)(istream& infd)> _gameObjFactoryMap;
	 map<string, shared_ptr<Script> (Parser::*)(istream& infd)> _scriptFactoryMap;
};
