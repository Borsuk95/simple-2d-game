#include "InGameScene.h"
#include "Game.h"
#include "AsteroidSmall.h"
#include "AsteroidMedium.h"
#include "AsteroidBig.h"

#define M_PI 3.14159265358979323846

bool InGameScene::isOutOfScene(Entity* object, sf::Vector2u window) const
{
	const auto textureDiagonal = 90.f;
	sf::FloatRect rect(-textureDiagonal, -textureDiagonal, window.x+2*textureDiagonal, window.y+2*textureDiagonal);
	return !rect.contains(object->getPosition());
}

void InGameScene::updatePosition(Entity* object, sf::Vector2u window)
{
	const auto textureDiagonal = 90.f;
	auto objectPos =  object->getPosition();
	if(object->getPosition().x>window.x+textureDiagonal)
	{
		objectPos.x -= window.x + 2*textureDiagonal;
		object->setPosition(objectPos);
	}
	if(object->getPosition().x<-textureDiagonal)
	{
		objectPos.x += window.x + 2*textureDiagonal;
		object->setPosition(objectPos);
	}
	if(object->getPosition().y>window.y+textureDiagonal)
	{
		objectPos.y -= window.y + 2 * textureDiagonal;
		object->setPosition(objectPos);
	}
	if (object->getPosition().y<-textureDiagonal)
	{
		objectPos.y += window.y + 2 * textureDiagonal;
		object->setPosition(objectPos);
	}
}

void InGameScene::keyPressedEvent(sf::Keyboard::Key key)
{
	switch (key)
	{
	case sf::Keyboard::Left:
		shipControl["left"] = true;
		break;
	case sf::Keyboard::Right:
		shipControl["right"] = true;
		break;
	case sf::Keyboard::Up:
		shipControl["up"] = true;
		break;
	case sf::Keyboard::Down:
		shipControl["down"] = true;
		break;
	case sf::Keyboard::Space:
		shipControl["shot"] = true;
		break;
	default:;
	}
}

void InGameScene::keyReleasedEvent(sf::Keyboard::Key key)
{
	switch (key)
	{
	case sf::Keyboard::Left:
		shipControl["left"] = false;
		break;
	case sf::Keyboard::Right:
		shipControl["right"] = false;
		break;
	case sf::Keyboard::Up:
		shipControl["up"] = false;
		break;
	case sf::Keyboard::Down:
		shipControl["down"] = false;
		break;
	case sf::Keyboard::Space:
		shipControl["shot"] = false;
		break;
	default:;
	}
}

void InGameScene::handlingShipControl(long long deltaTime)
{
	const auto shipRotation = 0.1f;
	const auto shipAcceleration = 10.f;

	auto angle = static_cast<float>(ship.getAngle()*M_PI / 180);
	auto x = shipAcceleration*cos(angle);
	auto y = shipAcceleration*sin(angle);
	sf::Vector2f accelerationVector(x, y);

	if (shipControl["left"])
	{
		if(!shipControl["right"])
		{
			ship.setRotation(-shipRotation);
		}
	}
	if (shipControl["right"])
	{
		if (!shipControl["left"])
		{
			ship.setRotation(shipRotation);
		}
	}
	if (shipControl["up"])
	{
		if (!shipControl["down"])
		{
			ship.accelerate(accelerationVector, deltaTime);
		}
	}
	if (shipControl["down"])
	{
		if (!shipControl["up"])
		{
			accelerationVector = -accelerationVector;
			ship.accelerate(accelerationVector, deltaTime);
		}
	}
	if (shipControl["shot"])
	{
		if(elapsedTime>500000)
		{
   			shot();
			elapsedTime = 0;
		}
	}
}

void InGameScene::asteroidSpawner()
{
	const int asteroidSpawnRate = 100;
	const int maxAsteroidVelocity = 2000;
	const int maxAsteroidRotation = 10;

	if (rand() % 10000<asteroidSpawnRate)
	{
		float x = (rand() % maxAsteroidVelocity - 1000) / 10000.f;
		float y = (rand() % maxAsteroidVelocity - 1000) / 10000.f;
		float rotation = rand() % maxAsteroidRotation / 100.f;
		int asteroidType = rand() % 3;

		switch (asteroidType)
		{
		case 0:
			asteroidsList.push_back(std::make_shared<AsteroidSmall>(AsteroidSmall()));
			break;
		case 1:
			asteroidsList.push_back(std::make_shared<AsteroidMedium>(AsteroidMedium()));
			break;
		case 2:
			asteroidsList.push_back(std::make_shared<AsteroidBig>(AsteroidBig()));
			break;
		default: 
			throw std::string("wrong asteroid Type -> InGameScene::asteroidSpawner()");
		}
		sf::Vector2f asteroidVelocity(x, y);
		asteroidsList.back()->setVelocity(asteroidVelocity);
		asteroidsList.back()->setRotation(rotation);
		x = -64;
		y = rand() % 720;
		asteroidsList.back()->setPosition(sf::Vector2f(x, y));

	}
}

bool InGameScene::checkColision() const
{
	auto shipSize = ship.getGlobalBound();
	const auto sizeOffset = 30;
	shipSize.left += sizeOffset;
	shipSize.top += sizeOffset;
	shipSize.height -= sizeOffset;
	shipSize.width -= sizeOffset;

	for (auto& element : asteroidsList)
	{
		if (element->getGlobalBound().intersects(shipSize))
		{
			return true;
		}
	}
	return false;
}

InGameScene::InGameScene():font(),showScore(),score(0),elapsedTime(0)
{


	shipControl["left"] = false;
	shipControl["right"] = false;
	shipControl["up"] = false;
	shipControl["down"] = false;
	shipControl["shot"] = false;

	std::srand(static_cast<int>(std::time(nullptr)));
}


InGameScene::~InGameScene()
{
}

void InGameScene::handleEvent(Game& game)
{
	switch (game.event.type)
	{
	case sf::Event::EventType::KeyPressed:
		if (game.event.key.code == sf::Keyboard::Escape)
		{
			game.changeScene(Game::GameScene::MenuMain);
		}
		keyPressedEvent(game.event.key.code);
		break;

	case sf::Event::EventType::KeyReleased:
		keyReleasedEvent(game.event.key.code);
		break;

	default:;
	}
}

void InGameScene::render(Game& game)
{
	game.window.draw(ship);

	for (auto& element : asteroidsList)
	{
		game.window.draw(*element);
	}
	for (auto& element : projectileList)
	{
		game.window.draw(*element);
	}

	game.window.draw(showScore);
}

void InGameScene::update(Game& game)
{
	elapsedTime += game.deltaTime;
	handlingShipControl(game.deltaTime);
	sf::Vector2u window = game.window.getSize();
	if (isOutOfScene(&ship, window))
	{
		updatePosition(&ship, window);
	}
	ship.update(game.deltaTime);

	for (auto& element : asteroidsList)
	{
		if (isOutOfScene(element.get(), window))
		{
			updatePosition(element.get(), window);
		}
		element->update(game.deltaTime);
	}

	isAsteroidHit();
	UpdateProjectile(game);

	asteroidSpawner();

	showScore.setString(std::to_string(score));

	if(checkColision())
	{
		game.changeScene(Game::GameScene::MenuMain);
	}

}

void InGameScene::onCreate(Game& game)
{
	font.loadFromFile("Resources/font/gameplay.ttf");
	showScore.setFont(font);
	showScore.setString(std::to_string(score));
	showScore.setCharacterSize(30);
}

void InGameScene::onClose(Game& game)
{
}

void InGameScene::shot()
{
	const auto projectileSpeed=0.5f;

	auto angle = static_cast<float>(ship.getAngle()*M_PI / 180);
	auto x = projectileSpeed*cos(angle);
	auto y = projectileSpeed*sin(angle);

	sf::Vector2f projectileVelocity(x, y);
	projectileVelocity += ship.getVelocity();

	projectileList.push_back(std::make_shared<Projectile>(Projectile()));
	projectileList.back()->setVelocity(projectileVelocity);
	projectileList.back()->setPosition(ship.getPosition());
	projectileList.back()->setAngle(ship.getAngle());

}

void InGameScene::fractureAsteroid(Asteroid* asteroid)
{
	const int maxAsteroidVelocity = 2000;

	float rotation = asteroid->getRotation()*2;

	for (int i = 0; i < 2; ++i)
	{
		switch (asteroid->Size)
		{
		case Asteroid::AsteroidSize::Big:
			asteroidsList.push_front(std::make_shared<AsteroidMedium>(AsteroidMedium()));
			break;
		case Asteroid::AsteroidSize::Medium:
			asteroidsList.push_front(std::make_shared<AsteroidSmall>(AsteroidSmall()));
			break;
		default:
			throw std::string("wrong asteroid Type -> InGameScene::fractureAsteroid()");
		}

		float x = (rand() % maxAsteroidVelocity - 1000) / 10000.f;
		float y = (rand() % maxAsteroidVelocity - 1000) / 10000.f;

		x += asteroid->getVelocity().x;
		y += asteroid->getVelocity().y;

		sf::Vector2f asteroidVelocity(x, y);
		asteroidsList.front()->setVelocity(asteroidVelocity);
		asteroidsList.front()->setRotation(rotation);
		asteroidsList.front()->setPosition(asteroid->getPosition());
	}
}

void InGameScene::isAsteroidHit()
{
	std::list<AsteroidPtr>::iterator asteroidIter;
	std::list<AsteroidPtr>::iterator asteroidItertoErease;
	std::list<ProjectilePtr>::iterator projectileIter;
	std::list<ProjectilePtr>::iterator projectileItertoErease;
	auto erase = false;

	for(projectileIter=projectileList.begin();projectileIter!=projectileList.end();++projectileIter)
	{
		for (asteroidIter = asteroidsList.begin(); asteroidIter != asteroidsList.end(); ++asteroidIter)
		{
			if(projectileIter->get()->getGlobalBound().intersects(asteroidIter->get()->getGlobalBound()))
			{
				score += 5;
				asteroidItertoErease = asteroidIter;
				projectileItertoErease = projectileIter;
				erase = true;
				if (asteroidIter->get()->Size != Asteroid::AsteroidSize::Small)
					fractureAsteroid(asteroidIter->get());
				break;
			}
		}
	}
	if (erase)
	{
		projectileList.erase(projectileItertoErease);
		asteroidsList.erase(asteroidItertoErease);
	}
}

void InGameScene::UpdateProjectile(const Game& game)
{
	std::list<ProjectilePtr>::iterator projectileIter;
	std::list<ProjectilePtr>::iterator projectileIterToErase;
	auto erase = false;

	for (projectileIter = projectileList.begin(); projectileIter != projectileList.end(); ++projectileIter)
	{
		if (isOutOfScene(projectileIter->get(), game.window.getSize()))
		{
			projectileIterToErase = projectileIter;
			erase = true;
		}
		else
		{
			projectileIter->get()->update(game.deltaTime);
		}
	}
	if(erase)
	{
		projectileList.erase(projectileIterToErase);
	}
}
