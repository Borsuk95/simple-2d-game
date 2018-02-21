#pragma once
#include "Scene.h"
#include <map>
#include "Player.h"
#include <list>
#include "Asteroid.h"
#include <memory>
#include "Projectile.h"

class InGameScene : public Scene
{
	using AsteroidPtr = std::shared_ptr<Asteroid>;
	using ProjectilePtr = std::shared_ptr<Projectile>;

	sf::Font font;
	sf::Text showScore;

	int score;

	Player ship;

	std::list<AsteroidPtr> asteroidsList;
	std::list<ProjectilePtr> projectileList;

	std::map<std::string, bool> shipControl;

	long long elapsedTime;

	bool isOutOfScene(Entity* object, sf::Vector2u window) const;
	void updatePosition(Entity* object, sf::Vector2u window);

	void keyPressedEvent(sf::Keyboard::Key key);
	void keyReleasedEvent(sf::Keyboard::Key key);
	void handlingShipControl(long long deltaTime);
	void asteroidSpawner();
	bool checkColision() const;
	void shot();
	void fractureAsteroid(Asteroid* asteroid);
	void isAsteroidHit();
	void UpdateProjectile(const Game& game);

public:
	InGameScene();
	~InGameScene();

	void handleEvent(Game& game) override;
	void render(Game& game) override;
	void update(Game& game) override;
	void onCreate(Game& game) override;
	void onClose(Game& game) override;
};

