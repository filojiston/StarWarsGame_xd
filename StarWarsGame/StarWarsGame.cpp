#include "StarWarsGame.h"



StarWarsGame::StarWarsGame()
{
	loadAssets();
	turn = "Player";
}

void StarWarsGame::play()
{
	createWindow();		// create the window as init private window variable
	readDataFromText();

	selectedPlayer = selectPlayer();	// select a player (master yoda - luke skywalker)

	if (selectedPlayer->getName() == "Master Yoda")
		mYoda = (MasterYoda*)selectedPlayer;
	else
		lSkywalker = (LukeSkywalker*)selectedPlayer;

	clearShortestPaths();
	calculateShortestPaths();

	while (window.isOpen())
	{
		sf::Event e;
		while (window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
			{
				window.close();
				exit(EXIT_SUCCESS);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				printOnlyOnce = true;
			}
		}

		if (printOnlyOnce)		// for printing current distances when user press spacebar, only once
		{
			printDistances();
			std::cout << std::endl;
			for (int i = 0; i < 72; i++)
				std::cout << "-";
			std::cout << std::endl << std::endl << std::endl;
			printOnlyOnce = false;
		}

		clearShortestPaths();
		calculateShortestPaths();

		if (turn == "Player")
		{
			movePlayer();
			if (isWon())
			{
				printHealth();
				draw();
				window.display();
				window.clear(sf::Color(0, 150, 170, 255));
				printWon();
				window.display();
				sf::sleep(sf::seconds(7));
				exit(EXIT_SUCCESS);
			}
		}
		else
		{
			moveBadBoys();
			turn = "Player";
		}

		if (caught)
		{
			if (selectedPlayer->getName() == "Master Yoda")
				mYoda->setHealth(mYoda->getHealth() - 1);
			else
				lSkywalker->setHealth(lSkywalker->getHealth() - 1);

			window.clear(sf::Color(0, 150, 170, 255));	// clear the screen a bluish color
			printCaught();
			window.display();
			sf::sleep(sf::seconds(3));

			if (isGameOver())
			{
				window.clear(sf::Color(0, 150, 170, 255));
				printGameOver();
				window.display();
				sf::sleep(sf::seconds(7));
				exit(EXIT_SUCCESS);
			}
			reset();	// reset the game to the starting pos.
			caught = false;
		}

		window.clear(sf::Color(0, 150, 170, 255));	// clear the screen a bluish color
		printHealth();
		draw();
		window.display();
	}


}

Character* StarWarsGame::selectPlayer()
{
	Character *selectedPlayer;

	// texture and sprite for master yoda
	sf::Texture MasterYodaT;
	if (!MasterYodaT.loadFromFile("images/masteryoda.png"))
		exit(EXIT_FAILURE);

	sf::Sprite MasterYodaS(MasterYodaT);
	MasterYodaS.setPosition(sf::Vector2f(100.0f, 200.0f));

	// texture and sprite for luke skywalker
	sf::Texture LukeSkywalkerT;
	if (!LukeSkywalkerT.loadFromFile("images/lukeskywalker.png"))
		exit(EXIT_FAILURE);

	sf::Sprite LukeSkywalkerS(LukeSkywalkerT);
	LukeSkywalkerS.setPosition(sf::Vector2f(500.0f, 200.0f));

	// all text settings for display "Select your player!" string
	sf::Text text;
	text.setFont(anonymousFont);
	text.setString("Select your player!");
	text.setFillColor(sf::Color::Black);
	text.setPosition(sf::Vector2f(SCREEN_WIDTH / 2.0f - text.getLocalBounds().width / 2.0f, 50.0f));

	// all text settings for display hero names up the select line
	sf::Text heroNames;
	heroNames.setFont(anonymousFont);
	heroNames.setCharacterSize(24);
	heroNames.setString("master yoda");
	heroNames.setPosition(sf::Vector2f(120.0f, 470.0f));
	heroNames.setFillColor(sf::Color::Black);

	// draw an underline on images
	sf::RectangleShape line(sf::Vector2f(200.0f, 5.0f));
	line.setFillColor(sf::Color::Black);
	line.setPosition(sf::Vector2f(100.0f, 500.0f));

	bool onRight = false;

	while (window.isOpen())
	{
		sf::Event e;
		while (window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
			{
				window.close();
				exit(EXIT_SUCCESS);
			}
			// go right with right arrow key, display the underline and hero name
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !onRight)
			{
				line.setPosition(sf::Vector2f(500.0f, 500.0f));
				heroNames.setPosition(sf::Vector2f(510.0f, 470.0f));
				heroNames.setString("luke skywalker");
				onRight = true;
			}

			// go left with left arrow key, display the underline and hero name
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && onRight)
			{
				line.setPosition(sf::Vector2f(100.0f, 500.0f));
				heroNames.setPosition(sf::Vector2f(130.0f, 470.0f));
				heroNames.setString("master yoda");
				onRight = false;
			}

			// if user presses enter, then he/she selected him/her hero, so return selected hero
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			{
				if (onRight)
					selectedPlayer = new LukeSkywalker();

				else
					selectedPlayer = new MasterYoda();

				selectedPlayer->setLocation(6, 5);
				selectedPlayer->setStartLocation(6, 5);
				return selectedPlayer;
			}
		}

		window.clear(sf::Color::White);
		window.draw(MasterYodaS);
		window.draw(LukeSkywalkerS);
		window.draw(text);
		window.draw(heroNames);
		window.draw(line);
		window.display();
	}
}

void StarWarsGame::createWindow()
{
	auto desktop = sf::VideoMode::getDesktopMode();

	window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), SCREEN_TITLE);
	window.setPosition(sf::Vector2i(desktop.width / 2, desktop.height / 2 - window.getSize().y / 2));
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(30);
}

void StarWarsGame::printHealth()
{
	// text settings for print "Health"
	sf::Text healthText;
	healthText.setFont(arialFont);
	healthText.setString("Health: ");
	healthText.setPosition(sf::Vector2f(240.0f, 14.0f));
	healthText.setFillColor(sf::Color::Black);
	healthText.setCharacterSize(36);

	window.draw(healthText);
	float x = 370.0f;

	if (selectedPlayer->getName() == "Master Yoda")
	{
		for (int i = 0; i < mYoda->getHealth() / 2; i++)
		{
			fullHealthSprite.setPosition(sf::Vector2f(x, 14.0f));
			window.draw(fullHealthSprite);
			x += 60.0f;
		}

		if (mYoda->getHealth() % 2 != 0)
		{
			halfHealthSprite.setPosition(sf::Vector2f(x - 10.0f, 12.0f));
			window.draw(halfHealthSprite);
		}
	}
	else
	{
		for (int i = 0; i < lSkywalker->getHealth(); i++)
		{
			fullHealthSprite.setPosition(sf::Vector2f(x, 14.0f));
			window.draw(fullHealthSprite);
			x += 60.0f;
		}
	}

}

void StarWarsGame::printCaught()
{
	sf::Text caughtText;
	caughtText.setFont(anonymousFont);
	caughtText.setFillColor(sf::Color::Black);
	caughtText.setCharacterSize(72);
	caughtText.setString("You caught!");

	sf::FloatRect textRect = caughtText.getLocalBounds();
	caughtText.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	caughtText.setPosition(sf::Vector2f(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f));

	window.draw(caughtText);
}

void StarWarsGame::printWon()
{
	sf::Text wonText;
	wonText.setFont(anonymousFont);
	wonText.setFillColor(sf::Color::Black);
	wonText.setCharacterSize(72);
	wonText.setString("You won!");

	sf::FloatRect textRect = wonText.getLocalBounds();
	wonText.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	wonText.setPosition(sf::Vector2f(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f));

	window.draw(wonText);
}

void StarWarsGame::printGameOver()
{
	sf::Text gameOverText;
	gameOverText.setFont(anonymousFont);
	gameOverText.setFillColor(sf::Color::Black);
	gameOverText.setCharacterSize(72);
	gameOverText.setString("Game over!");

	sf::FloatRect textRect = gameOverText.getLocalBounds();
	gameOverText.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	gameOverText.setPosition(sf::Vector2f(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f));

	window.draw(gameOverText);
}

void StarWarsGame::draw()
{
	std::string selectedPlayerName = selectedPlayer->getName();

	bool darthVaderFound = (darthVaders.size() >= 1) ? true : false;
	bool kyloRenFound = (kyloRens.size() >= 1) ? true : false;
	bool stormtrooperFound = (stormTroopers.size() >= 1) ? true : false;

	bool yodaFound = (selectedPlayerName == "Master Yoda") ? true : false;
	bool lukeSkywalkerFound = (selectedPlayerName == "Luke Skywalker") ? true : false;

	// text settings for map 
	sf::Text mapText;
	mapText.setFont(arialFont);
	mapText.setFillColor(sf::Color::Black);
	mapText.setCharacterSize(20);

	// text settings for door letters
	sf::Text doorText;
	doorText.setFont(arialFont);
	doorText.setFillColor(sf::Color::White);
	doorText.setCharacterSize(32);

	bool isDoor = false;

	float xPos = 120.0f;
	float yPos = 110.0f;

	for (int j = 0; j < 11; j++)
	{
		for (int i = 0; i < 14; i++)
		{
			if (map[i][j] == 1)
			{
				mapText.setString("1");
				mapRect.setFillColor(sf::Color(0, 150, 170, 255));
			}
			else
			{
				mapText.setString("0");
				mapRect.setFillColor(sf::Color::White);
			}
			mapText.setPosition(xPos + 12, yPos + 10);

			mapRect.setPosition(sf::Vector2f(xPos, yPos));
			if (i == 0 && j == 5)		// door A
			{
				mapRect.setFillColor(sf::Color(0, 0, 120, 255));
				doorText.setString("A");
				doorText.setPosition(xPos + 8, yPos);
				arrowRightSprite.setPosition(xPos - 50, yPos + 4);
				isDoor = true;
			}
			if (i == 4 && j == 0)	// door B
			{
				mapRect.setFillColor(sf::Color(0, 0, 120, 255));
				doorText.setString("B");
				doorText.setPosition(xPos + 8, yPos);
				arrowDownSprite.setPosition(xPos + 2, yPos - 50);
				isDoor = true;
			}
			if (i == 12 && j == 0)	// door C
			{
				mapRect.setFillColor(sf::Color(0, 0, 120, 255));
				doorText.setString("C");
				doorText.setPosition(xPos + 8, yPos);
				arrowDownSprite.setPosition(xPos + 2, yPos - 50);
				isDoor = true;
			}
			if (i == 13 && j == 5)	// door D
			{
				mapRect.setFillColor(sf::Color(0, 0, 120, 255));
				doorText.setString("D");
				doorText.setPosition(xPos + 8, yPos);
				arrowLeftSprite.setPosition(xPos + 50, yPos + 1);
				isDoor = true;
			}
			if (i == 4 && j == 10)	// door E
			{
				mapRect.setFillColor(sf::Color(0, 0, 120, 255));
				doorText.setString("E");
				doorText.setPosition(xPos + 8, yPos);
				arrowUpSprite.setPosition(xPos + 4, yPos + 50);
				isDoor = true;
			}
			// player's current location at every turn
			if (i == selectedPlayer->getLocation().getX() && j == selectedPlayer->getLocation().getY())
			{
				if (selectedPlayerName == "Master Yoda")
					mYodaSprite.setPosition(xPos, yPos);
				else
					mLukeSkywalkerSprite.setPosition(xPos, yPos);
				mapRect.setFillColor(sf::Color::Yellow);
			}

			for (int k = 0; k < darthVaders.size(); k++)
			{
				if (i == darthVaders[k].getLocation().getX() && j == darthVaders[k].getLocation().getY())
				{
					mDarthVaderSprite.setPosition(xPos, yPos);
					mapRect.setFillColor(sf::Color::Red);
					doorText.setString("");
				}

				// color the shortest path to red
				for (int z = 0; z < darthVadersShortestPaths.size(); z++)
				{
					for (int zz = 0; zz < darthVadersShortestPaths[z].size(); zz++)
					{
						if (i == darthVadersShortestPaths[z][zz].getX() &&
							j == darthVadersShortestPaths[z][zz].getY())
						{
							mapRect.setFillColor(sf::Color::Red);
							doorText.setString("");
						}
					}
				}
			}

			for (int k = 0; k < kyloRens.size(); k++)
			{
				if (i == kyloRens[k].getLocation().getX() && j == kyloRens[k].getLocation().getY())
				{
					mKyloRenSprite.setPosition(xPos, yPos);
					mapRect.setFillColor(sf::Color::Red);
					doorText.setString("");
				}

				// color the shortest path to red
				for (int z = 0; z < kyloRensShortestPaths.size(); z++)
				{
					for (int zz = 0; zz < kyloRensShortestPaths[z].size(); zz++)
					{
						if (i == kyloRensShortestPaths[z][zz].getX() &&
							j == kyloRensShortestPaths[z][zz].getY())
						{
							mapRect.setFillColor(sf::Color::Red);
							doorText.setString("");
						}
					}
				}
			}

			for (int k = 0; k < stormTroopers.size(); k++)
			{
				if (i == stormTroopers[k].getLocation().getX() && j == stormTroopers[k].getLocation().getY())
				{
					mStormTrooperSprite.setPosition(xPos, yPos);
					mapRect.setFillColor(sf::Color::Red);
					doorText.setString("");
				}

				// color the shortest path to red
				for (int z = 0; z < stormtroopersShortestPaths.size(); z++)
				{
					for (int zz = 0; zz < stormtroopersShortestPaths[z].size(); zz++)
					{
						if (i == stormtroopersShortestPaths[z][zz].getX() &&
							j == stormtroopersShortestPaths[z][zz].getY())
						{
							mapRect.setFillColor(sf::Color::Red);
							doorText.setString("");
						}
					}
				}
			}

			cupSprite.setPosition(sf::Vector2f(700.0f, 440.0f));

			window.draw(mapRect);
			window.draw(doorText);
			window.draw(cupSprite);
			window.draw(arrowUpSprite);
			window.draw(arrowDownSprite);
			window.draw(arrowLeftSprite);
			window.draw(arrowRightSprite);
			if (darthVaderFound)
				window.draw(mDarthVaderSprite);
			if (kyloRenFound)
				window.draw(mKyloRenSprite);
			if (stormtrooperFound)
				window.draw(mStormTrooperSprite);
			if (yodaFound)
				window.draw(mYodaSprite);
			if (lukeSkywalkerFound)
				window.draw(mLukeSkywalkerSprite);
			if (!isDoor)
				window.draw(mapText);
			xPos += 40.0f;
			isDoor = false;
		}
		xPos = 120.0f;
		yPos += 40.0f;
	}
}

bool StarWarsGame::isWon()
{
	Location loc = selectedPlayer->getLocation();

	if (selectedPlayer->getName() == "Master Yoda")
	{
		if (mYoda->getHealth() != 0 && (loc.getX() == 13 && loc.getY() == 9))
			return true;
	}
	else
	{
		if (lSkywalker->getHealth() != 0 && (loc.getX() == 13 && loc.getY() == 9))
			return true;
	}

	return false;
}

bool StarWarsGame::isGameOver()
{
	if (selectedPlayer->getName() == "Master Yoda")
	{
		if (mYoda->getHealth() <= 0)
			return true;
	}
	else
	{
		if (lSkywalker->getHealth() <= 0)
			return true;
	}
	return false;
}

void StarWarsGame::reset()
{
	selectedPlayer->setLocation(selectedPlayer->getStartLocation());

	for (int i = 0; i < darthVaders.size(); i++)
	{
		darthVaders[i].setLocation(darthVaders[i].getStartLocation());
	}

	for (int i = 0; i < kyloRens.size(); i++)
	{
		kyloRens[i].setLocation(kyloRens[i].getStartLocation());
	}

	for (int i = 0; i < stormTroopers.size(); i++)
	{
		stormTroopers[i].setLocation(stormTroopers[i].getStartLocation());
	}
}

void StarWarsGame::loadAssets()
{
	if (!anonymousFont.loadFromFile("fonts/anonymous_pro.ttf"))
		exit(EXIT_FAILURE);

	if (!arialFont.loadFromFile("fonts/arial.ttf"))
		exit(EXIT_FAILURE);

	if (!fullHealthTexture.loadFromFile("images/full_heart.png"))
		exit(EXIT_FAILURE);

	if (!halfHealthTexture.loadFromFile("images/half_heart.png"))
		exit(EXIT_FAILURE);

	if (!cupTexture.loadFromFile("images/cup.png"))
		exit(EXIT_FAILURE);

	if (!arrowUpTexture.loadFromFile("images/icon_up.png"))
		exit(EXIT_FAILURE);

	if (!arrowDownTexture.loadFromFile("images/icon_down.png"))
		exit(EXIT_FAILURE);

	if (!arrowLeftTexture.loadFromFile("images/icon_left.png"))
		exit(EXIT_FAILURE);

	if (!arrowRightTexture.loadFromFile("images/icon_right.png"))
		exit(EXIT_FAILURE);

	if (!mYodaTexture.loadFromFile("images/mYoda.png"))
		exit(EXIT_FAILURE);

	if (!mLukeSkywalkerTexture.loadFromFile("images/mLukeSkywalker.png"))
		exit(EXIT_FAILURE);

	if (!mDarthVaderTexture.loadFromFile("images/mDarthVader.png"))
		exit(EXIT_FAILURE);

	if (!mKyloRenTexture.loadFromFile("images/mKyloRen.png"))
		exit(EXIT_FAILURE);

	if (!mStormTrooperTexture.loadFromFile("images/mStormTrooper.png"))
		exit(EXIT_FAILURE);

	fullHealthSprite.setTexture(fullHealthTexture);
	halfHealthSprite.setTexture(halfHealthTexture);
	cupSprite.setTexture(cupTexture);
	arrowUpSprite.setTexture(arrowUpTexture);
	arrowDownSprite.setTexture(arrowDownTexture);
	arrowLeftSprite.setTexture(arrowLeftTexture);
	arrowRightSprite.setTexture(arrowRightTexture);
	mYodaSprite.setTexture(mYodaTexture);
	mLukeSkywalkerSprite.setTexture(mLukeSkywalkerTexture);
	mDarthVaderSprite.setTexture(mDarthVaderTexture);
	mKyloRenSprite.setTexture(mKyloRenTexture);
	mStormTrooperSprite.setTexture(mStormTrooperTexture);

	mapRect.setSize(sf::Vector2f(40.0f, 40.0f));
	mapRect.setOutlineColor(sf::Color::Black);
	mapRect.setOutlineThickness(2.0f);
}

void StarWarsGame::movePlayer()
{
	int x = selectedPlayer->getLocation().getX();
	int y = selectedPlayer->getLocation().getY();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && y - 1 >= 0 && map[x][y - 1] == 1)
	{
		selectedPlayer->setLocation(x, y - 1);
		turn = "BadBoys";
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && y + 1 < Map::MAPY && map[x][y + 1] == 1)
	{
		selectedPlayer->setLocation(x, y + 1);
		turn = "BadBoys";
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && x - 1 >= 0 && map[x - 1][y] == 1)
	{
		selectedPlayer->setLocation(x - 1, y);
		turn = "BadBoys";
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && x + 1 < Map::MAPX && map[x + 1][y] == 1)
	{
		selectedPlayer->setLocation(x + 1, y);
		turn = "BadBoys";
	}
}

void StarWarsGame::moveBadBoys()
{
	for (int i = 0; i < darthVaders.size(); i++)
	{
		std::vector<Location> path = darthVaders[i].findShortestPath(darthVaders[i].getLocation(),
			selectedPlayer->getLocation());
		if (path.size() > 1)
			darthVaders[i].setLocation(path[1]);
		else
		{
			darthVaders[i].setLocation(selectedPlayer->getLocation());
			caught = true;
		}
	}

	for (int i = 0; i < kyloRens.size(); i++)
	{
		std::vector<Location> path = kyloRens[i].findShortestPath(kyloRens[i].getLocation(),
			selectedPlayer->getLocation());
		if (path.size() > 2)
			kyloRens[i].setLocation(path[2]);
		else
		{
			kyloRens[i].setLocation(selectedPlayer->getLocation());
			caught = true;
		}

	}

	for (int i = 0; i < stormTroopers.size(); i++)
	{
		std::vector<Location> path = stormTroopers[i].findShortestPath(stormTroopers[i].getLocation(),
			selectedPlayer->getLocation());
		if (path.size() > 1)
			stormTroopers[i].setLocation(path[1]);
		else
		{
			stormTroopers[i].setLocation(selectedPlayer->getLocation());
			caught = true;
		}
	}
}

void StarWarsGame::calculateShortestPaths()
{
	for (int i = 0; i < darthVaders.size(); i++)
	{
		std::vector<Location> path = darthVaders[i].findShortestPath(darthVaders[i].getLocation(),
			selectedPlayer->getLocation());
		darthVadersShortestPaths.push_back(path);
	}

	for (int i = 0; i < kyloRens.size(); i++)
	{
		std::vector<Location> path = kyloRens[i].findShortestPath(kyloRens[i].getLocation(),
			selectedPlayer->getLocation());
		kyloRensShortestPaths.push_back(path);
	}

	for (int i = 0; i < stormTroopers.size(); i++)
	{
		std::vector<Location> path = stormTroopers[i].findShortestPath(stormTroopers[i].getLocation(),
			selectedPlayer->getLocation());
		stormtroopersShortestPaths.push_back(path);
	}
}

void StarWarsGame::clearShortestPaths()
{
	darthVadersShortestPaths.clear();
	kyloRensShortestPaths.clear();
	stormtroopersShortestPaths.clear();
}

void StarWarsGame::printDistances()
{
	for (int i = 0; i < darthVaders.size(); i++)
	{
		std::cout << "The distance between Darth Vader (" << darthVaders[i].getLocation().getX() <<
			"," << darthVaders[i].getLocation().getY() << ") and " << selectedPlayer->getName() << " (" <<
			selectedPlayer->getLocation().getX() << "," << selectedPlayer->getLocation().getY() <<
			") is ->  " << darthVaders[i].getDistance();
		std::cout << std::endl << std::endl;
	}

	for (int i = 0; i < kyloRens.size(); i++)
	{
		std::cout << "The distance between Kylo Ren (" << kyloRens[i].getLocation().getX() <<
			"," << kyloRens[i].getLocation().getY() << ") and " << selectedPlayer->getName() << " (" <<
			selectedPlayer->getLocation().getX() << "," << selectedPlayer->getLocation().getY() <<
			") is ->  " << kyloRens[i].getDistance();
		std::cout << std::endl << std::endl;
	}

	for (int i = 0; i < stormTroopers.size(); i++)
	{
		std::cout << "The distance between Stormtrooper (" << stormTroopers[i].getLocation().getX() <<
			"," << stormTroopers[i].getLocation().getY() << ") and " << selectedPlayer->getName() << " (" <<
			selectedPlayer->getLocation().getX() << "," << selectedPlayer->getLocation().getY() <<
			") is ->  " << stormTroopers[i].getDistance();
		std::cout << std::endl << std::endl;
	}
}

void StarWarsGame::readDataFromText()
{
	map = Map::getMap();
	std::string line;

	std::string darthVaderText = "Darth Vader";
	std::string kyloRenText = "Kylo Ren";
	std::string stormtrooperText = "Stormtrooper";

	std::ifstream inputText("Harita.txt");
	if (inputText.is_open())
	{
		while (std::getline(inputText, line))
		{
			if (line.find("Karakter") != std::string::npos)
			{
				Location loc;

				if (line.find("Kapi:A") != std::string::npos)		// evil character starts at A
				{
					loc.setX(0);
					loc.setY(5);
				}
				else if (line.find("Kapi:B") != std::string::npos)	// evil character starts at B
				{
					loc.setX(4);
					loc.setY(0);
				}
				else if (line.find("Kapi:C") != std::string::npos)	// evil character starts at C
				{
					loc.setX(12);
					loc.setY(0);
				}
				else if (line.find("Kapi:D") != std::string::npos)	// evil character starts at D
				{
					loc.setX(13);
					loc.setY(5);
				}
				else												// evil character starts at E
				{
					loc.setX(4);
					loc.setY(10);
				}


				if (line.find(darthVaderText) != std::string::npos)		// the enemy is a darth vader
				{
					DarthVader darthVader;
					darthVader.setLocation(loc);
					darthVader.setStartLocation(loc);
					darthVaders.push_back(darthVader);
				}
				else if (line.find(kyloRenText) != std::string::npos)	// the enemy is a kylo ren
				{
					KyloRen kyloRen;
					kyloRen.setLocation(loc);
					kyloRen.setStartLocation(loc);
					kyloRens.push_back(kyloRen);
				}
				else		// the enemy is a stormtrooper
				{
					Stormtrooper trooper;
					trooper.setLocation(loc);
					trooper.setStartLocation(loc);
					stormTroopers.push_back(trooper);
				}
			}
		}
		inputText.close();
	}
}