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
	Parser(shared_ptr<istream>& infd) : _infd(infd) {}
	void Read(Map& map);
	shared_ptr<GameObject> readObject(const string& obj_name);
	shared_ptr<Script> readScript(string temp);
	Graphics* readGraphics();
	Movement* readMovement();


	// --------------------------------------------------------

	shared_ptr<GameObject> makeNPC(shared_ptr<istream>& infd);
	shared_ptr<GameObject> makeDoor(shared_ptr<istream>& infd);
	shared_ptr<GameObject> makeChest(shared_ptr<istream>& infd);
	
	shared_ptr<Script> readDialog(shared_ptr<istream>& infd);
	shared_ptr<Script> readGiveItem(shared_ptr<istream>& infd);
	shared_ptr<Script> readIFQItem(shared_ptr<istream>& infd);
	shared_ptr<Script> readIFLevel(shared_ptr<istream>& infd);
	shared_ptr<Script> readScripts(shared_ptr<istream>& infd);
	shared_ptr<Script> readNoScript(shared_ptr<istream>& infd);

private:
	 shared_ptr<istream> _infd;

//	 map<string, > _gameObjFactoryMap;
//	 map<string, > _ScriptFactoryMap;
};
