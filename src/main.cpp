#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "Config.hpp"
#include "Vizualizer.hpp"
using namespace std;

int main (int argc, char** argv)
{
	//create a unique pointer to the game
    //we will add a new part where we go parse the data in the config file inside the config folder
    Config config;
    cout << "loading config" << endl;
    config.load("config/game.cfg");
    cout << "loaded config" << endl;
    config.print();
    config.set("player.name", "John");
    cout << "set config" << endl;
    config.save("config/game.json");
    cout << "saved config" << endl;
	Game game (argv, argc);
	//run the game
	game.run();
	std::cout << "vizualizer ran" << std::endl;
	return 0;
}
