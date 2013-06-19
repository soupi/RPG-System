#include "Map.h"
#include <iostream>
#include "Utility.h"
#include "Controller.h"
#include <exception>
#include "Parser.h"

// compares the classes by y position struct
struct compare_obj_by_y
{
	bool operator() (const shared_ptr<GameObject> & lhs, const shared_ptr<GameObject> & rhs) { return lhs->getPos().y < rhs->getPos().y; }
};

// constructor gets filename to load the map from
Map::Map(string filename)
{
	loadMap(filename);
}

// update the map
void Map::Update(Controller& ctrl, LocalMap& localmap, float elapsedTime)
{
	// update game objects
	for (vector<shared_ptr<GameObject>>::iterator obj = _game_objects.begin(); obj != _game_objects.end(); ++obj)
			(*obj)->Update(ctrl, localmap, elapsedTime);

	// sort by y
	std::sort(_game_objects.begin(), _game_objects.end(), compare_obj_by_y());
}

// let every object handle it's events
void Map::handleEvents(const Control& controls)
{
	// game objects handle events
	for (vector<shared_ptr<GameObject>>::iterator obj = _game_objects.begin(); obj != _game_objects.end(); ++obj)
		(*obj)->handleEvents(controls);
}

// render background, foreground, objects and top in that order
void Map::Render(Controller& ctrl)
{
	// draw background
	for (vector<Tile>::iterator tile = _background.begin(); tile != _background.end(); ++tile)
		tile->draw(ctrl.getWindow());
	// draw foreground
	for (vector<Tile>::iterator tile = _foreground.begin(); tile != _foreground.end(); ++tile)
		tile->draw(ctrl.getWindow());
	// draw game objects
	for (vector<shared_ptr<GameObject>>::iterator obj = _game_objects.begin(); obj != _game_objects.end(); ++obj)
		(*obj)->Render(ctrl);

	// draw top
	for (vector<Tile>::iterator tile = _top.begin(); tile != _top.end(); ++tile)
		tile->draw(ctrl.getWindow());
}
// load map from file
void Map::loadMap(string& filename)
{
	// open file
	std::ifstream mapfile;
	mapfile.exceptions( std::ifstream::failbit | std::ifstream::badbit );
	mapfile.open("resources/maps/" + filename);

	if (!mapfile) 
		throw std::exception( "Failed to open file to load");

	// read size of map
	unsigned size_w, size_h;
	mapfile >> size_w >> size_h;
	_width = size_w;

	// init.. all tiles will be empty
	for (unsigned i = 0; i < size_w*size_h; i++)
	{
		_background.push_back(Tile());
		_foreground.push_back(Tile());
		_top.push_back(Tile());
	}

	// load all layers
	loadLayer(mapfile, _background);
	loadLayer(mapfile, _foreground);
	loadLayer(mapfile, _top);

	// read game objects on map
	Parser parser(mapfile);
	parser.Read(*this);

	mapfile.close();
}

// load tiles layer
void Map::loadLayer(std::ifstream& mapfile, vector<Tile>& layer)
{
	// read the size of the layer
	unsigned size_w, size_h;
	mapfile >> size_w >> size_h;


	mapfile.get(); // go to new line
	string tiles; 
	getline(mapfile, tiles); // read tileset name

	// read tileset 
	const sf::Texture& tileset = (Bank<sf::Texture>::getInstance().get("resources/" + tiles));

	// read tiles
	for (unsigned i = 0; i < size_w*size_h; i++)
	{
		int tile;
		try { // read a tile and add to layer at this position
			mapfile >> tile;
			if (tile)
			{
				layer[i] = Tile(tileset, tile);
				layer[i].setPos(sf::Vector2f((i%size_w)*float(SCRN_TILE_SIZE), (i/size_w)*float(SCRN_TILE_SIZE)));
			}
		}
		catch (...) { throw std::exception("can't read tiles"); }
	}
}

// add a game object to the map
// pos is the tile number
void Map::addGameObject(shared_ptr<GameObject>& obj, unsigned pos)
{
	// check if the position is in range
	if (pos > _background.size())
	{
		std::exception e("bad location for obj on map");
		throw(e);
	}

	// set ID for new object
	int max = 0; // find current maximum id on map
	for (vector<shared_ptr<GameObject>>::iterator it = _game_objects.begin(); it != _game_objects.end(); ++it)
		if (max < (*it)->getId())
			max = (*it)->getId();
	

	obj->setId(max+1); // set id as max + 1

	// set object position
	obj->setPos(sf::Vector2f((pos%_width)*float(SCRN_TILE_SIZE) + obj->getRadius(), (pos/_width)*float(SCRN_TILE_SIZE) + obj->getRadius()));

	_game_objects.push_back(obj);

	// insertion sort (by y)
	for (int i = _game_objects.size() -1; 0 < i && _game_objects[i]->getPos().y < _game_objects[i-1]->getPos().y; --i)
		std::swap(_game_objects[i], _game_objects[i-1]);
}

// add object to map with a specific position and not a tile
void Map::addGameObject(shared_ptr<GameObject>& obj, const sf::Vector2f& pos)
{
	// set position for object
	obj->setPos(pos);

	// set id
	int max = 0;
	for (vector<shared_ptr<GameObject>>::iterator it = _game_objects.begin(); it != _game_objects.end(); ++it)
		if (max < (*it)->getId())
			max = (*it)->getId();

	obj->setId(max+1);

	_game_objects.push_back(obj);
	

	// insertion sort (by y)
	for (int i = _game_objects.size() -1; 0 < i && _game_objects[i]->getPos().y < _game_objects[i-1]->getPos().y; --i)
		std::swap(_game_objects[i], _game_objects[i-1]);
}


// ---------------- INTERACTIONS ----------------

// can object step on foreground?
bool Map::canStepOnFG(sf::Vector2f& pos) const
{
	// get tile position
	sf::Vector2u my_pos(unsigned(pos.x)/SCRN_TILE_SIZE, unsigned(pos.y)/SCRN_TILE_SIZE);

	if (my_pos.x >= _width || my_pos.y >=  (_foreground.size() / _width)) // out of border
		return false;

	// check if position is on a foreground tile
	if (_foreground[my_pos.x + my_pos.y*_width].getNum())
		return false;

	return true;
}

// check four corners of the box (top left, bottom left and so on)
// all corners will be radius distance of the center (pos)

// this function is not currently in use
bool Map::canStepOnFG(sf::Vector2f& pos, float radius) const
{
	if (!(canStepOnFG(sf::Vector2f(pos.x - radius, pos.y - radius)) && canStepOnFG(sf::Vector2f(pos.x - radius, pos.y +radius)) &&
		canStepOnFG(sf::Vector2f(pos.x + radius, pos.y - radius)) && canStepOnFG(sf::Vector2f(pos.x + radius, pos.y +radius))))
		return false;

	return true;
}

// check if the four corners and the center of the box does not collide with the box
bool Map::canStepOnFG(sf::FloatRect& box) const
{
	
	if (!(canStepOnFG(sf::Vector2f(box.left + box.width/2, box.top + box.height/2)) && 
		canStepOnFG(sf::Vector2f(box.left, box.top)) && canStepOnFG(sf::Vector2f(box.left + box.width, box.top)) &&
		canStepOnFG(sf::Vector2f(box.left, box.top + box.height)) && canStepOnFG(sf::Vector2f(box.left + box.width, box.top + box.height))))
		return false;

	return true;
}

// check if game object can be in it's position
bool Map::canStepOn(GameObject& obj)
{
	sf::FloatRect box = obj.getCollisionBox();
	if (!canStepOnFG(box)) // can he step on foreground?
		return false;

	// if there's an object you can't step on, return false
	for (vector<shared_ptr<GameObject>>::iterator it = _game_objects.begin(); it != _game_objects.end(); ++it)
		if((it->get()) != &obj && (*it)->checkCollision(box) && !obj.canStepOn(*(it->get())))
			return false;
	
	return true;
}

// step on the map. 
void Map::Step(LocalMap& localmap, GameObject& obj)
{
	sf::FloatRect box = obj.getCollisionBox();
	// check if object stepped on someone
	for (vector<shared_ptr<GameObject>>::iterator it = _game_objects.begin(); it != _game_objects.end(); ++it)
		if((it->get()) != &obj && (*it)->checkCollision(box))
			obj.StepOn(localmap, *(it->get())); // dispatch
}

// try to interact with someone
// returns whether there was an interaction or not
bool Map::Act(LocalMap& localmap, GameObject& obj, sf::FloatRect& box)
{
	bool acted = false;
	for (vector<shared_ptr<GameObject>>::iterator it = _game_objects.begin(); it != _game_objects.end(); ++it)
		if((it->get()) != &obj && (*it)->checkCollision(box))
			acted = (*it)->act(localmap, obj);

		return acted;
}
// remove object from the map
void Map::remGameObject(GameObject* obj)
{
	for (vector<shared_ptr<GameObject>>::iterator it = _game_objects.begin(); it != _game_objects.end(); ++it)
	{
		// search for the object with the same address
		if ((*it).get() == obj)
		{
			_game_objects.erase(it); // and erase it
			break;
		}
	}
}

// get the position of the object with this id
const sf::Vector2f Map::getPosById(int id)
{
	for (vector<shared_ptr<GameObject>>::iterator it = _game_objects.begin(); it != _game_objects.end(); ++it)
	{
		if ((*it)->getId() == id)
			return (*it)->getPos();
	}
	return sf::Vector2f(0,0); // return 0,0 if there isn't an object with this id
}