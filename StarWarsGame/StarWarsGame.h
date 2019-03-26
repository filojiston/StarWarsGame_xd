#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "Location.h"
#include "Map.h"
#include "DarthVader.h"
#include "KyloRen.h"
#include "Stormtrooper.h"
#include "MasterYoda.h"
#include "LukeSkywalker.h"

class StarWarsGame
{
public:
	StarWarsGame();

	void play();

private:		// constants
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;
	const std::string SCREEN_TITLE = "Star Wars Game!";
private:		// sf variables for drawings
	sf::RenderWindow window;
	sf::Texture fullHealthTexture;
	sf::Texture halfHealthTexture;
	sf::Texture cupTexture;
	sf::Texture arrowUpTexture;
	sf::Texture arrowDownTexture;
	sf::Texture arrowLeftTexture;
	sf::Texture arrowRightTexture;
	sf::Texture mYodaTexture;
	sf::Texture mLukeSkywalkerTexture;
	sf::Texture mDarthVaderTexture;
	sf::Texture mKyloRenTexture;
	sf::Texture mStormTrooperTexture;
	sf::Sprite fullHealthSprite;
	sf::Sprite halfHealthSprite;
	sf::Sprite cupSprite;
	sf::Sprite arrowUpSprite;
	sf::Sprite arrowDownSprite;
	sf::Sprite arrowLeftSprite;
	sf::Sprite arrowRightSprite;
	sf::Sprite mYodaSprite;
	sf::Sprite mLukeSkywalkerSprite;
	sf::Sprite mDarthVaderSprite;
	sf::Sprite mKyloRenSprite;
	sf::Sprite mStormTrooperSprite;
	sf::RectangleShape mapRect;
	sf::Font anonymousFont;
	sf::Font arialFont;
private:
	Character *selectedPlayer;
	MasterYoda *mYoda;
	LukeSkywalker *lSkywalker;
	std::vector<DarthVader> darthVaders;
	std::vector<KyloRen> kyloRens;
	std::vector<Stormtrooper> stormTroopers;
	std::vector<std::vector<Location>> darthVadersShortestPaths;
	std::vector<std::vector<Location>> kyloRensShortestPaths;
	std::vector<std::vector<Location>> stormtroopersShortestPaths;
	Map gameMap;
	int **map;
	std::string turn;
	bool caught;
	bool printOnlyOnce;
private:
	void createWindow();
	void loadAssets();

	void movePlayer();
	void moveBadBoys();
	void calculateShortestPaths();
	void clearShortestPaths();
	void printDistances();

	void printHealth();
	void printCaught();
	void printWon();
	void printGameOver();
	void draw();

	bool isWon();
	bool isGameOver();
	void reset();

public:
	void readDataFromText();
	Character* selectPlayer();
};