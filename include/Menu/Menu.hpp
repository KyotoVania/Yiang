/*
** EPITECH PROJECT, 2023
** Yiang
** File description:
** Menu.hpp
*/
#ifndef MENU_HPP_
	#define MENU_HPP_

#include <SFML/Graphics.hpp>
#include <string>
//create a global map to associate a int with a note with is a string
#include <vector>
#include <tuple>
#include <vector>
#include <tuple>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;
#include "GraphicElement/Button.hpp"
#include "Database/Database.hpp"
#include "GraphicElement/BeatmapPanel.hpp"
#include "Visualizer/FFT.hpp"
//#include "GraphicElement/TriangleButton.hpp"
//TODO: BANNER

class Core;

class Menu {
public:
    Menu();
    ~Menu();
    void load(const std::pair<int, int>& res, Database& database,  std::vector<ButtonConfig>& buttonConfigs);
    void loadTextures(Database& database);
    void update(const sf::Event& event, const sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    void loadBeatmaps(Database& database);
    void slideLeft();
    void slideRight();
    struct ButtonConfig {
        std::string text;
        std::function<void()> onClick;
    };
protected:
    int selectedPanelIndex = 0; // Add this line
    map<string, Button> buttons;
    map<string, sf::Text> texts;
    map<string, sf::Texture> textures;
    map<string, sf::Sprite> sprites;
    //add the beatmap panel
    std::vector<BeatmapPanel> beatmapPanel;
    map<string, sf::Font> fonts;
    pair<int, int> _res = {0, 0};
    int theme = 0;
    std::vector<ButtonConfig> buttonConfigs;
    void onAnalyzeButtonClicked(Core& core, const std::string& beatmapPath);

private:
};

#endif /*MENU_HPP_*/