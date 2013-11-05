#include <SFML\Graphics\RectangleShape.hpp>
#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\Window\Event.hpp>
#include <SFML\System\Clock.hpp>
#include <SFML\System\Time.hpp>
#include "ParamLoader.h"
#include "Box2D\Box2D.h"
#include "Ground.h"
#include "Box.h"
#include "Map.h"
#include <iostream>
#include <conio.h>

#include <iostream>
#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>

using namespace std;

int main() {
	/*
    ////World setup
    b2Vec2 grav(0.0f, -10.0f);
    b2World* world = new b2World(grav);
	*/
	
	/*
    ////Bodies
    b2BodyDef groundDef;
    groundDef.position.Set(10.0f, -10.0f);
    b2PolygonShape groundShape;
    groundShape.SetAsBox(10.0f, 1.0f);
    b2Body* groundBody = world->CreateBody(&groundDef);
    groundBody->CreateFixture(&groundShape, 0.0f);

    sf::RectangleShape groundRect;
    groundRect.setSize(sf::Vector2f(20.0f, 2.0f));
    groundRect.setFillColor(sf::Color(100, 100, 100));

    ////----------------------------
    b2BodyDef boxDef;
    boxDef.position.Set(5, 0);
    boxDef.type = b2_dynamicBody;
    b2PolygonShape boxShape;
    boxShape.SetAsBox(0.1f, 0.1f);

    b2FixtureDef boxFixture;
    boxFixture.density = 1.0f;
    boxFixture.shape = &boxShape;
    boxFixture.friction = 0.3f;

    b2Body* boxBody = world->CreateBody(&boxDef);
    boxBody->CreateFixture(&boxFixture);

    sf::RectangleShape boxRect;
    boxRect.setSize(sf::Vector2f(1.f, 1.f));
    boxRect.setFillColor(sf::Color(150, 150, 150));
    boxRect.setOutlineColor(sf::Color(0, 0, 0));
    boxRect.setOutlineThickness(0.1);

    float32 timeStep = 1.0f/60.0f;
    int32 velIt = 6;
    int32 posIt = 2;
	*/

	sf::RenderWindow* App = new sf::RenderWindow(sf::VideoMode(800, 600, 32), "SFML and Box2D");
	sf::RenderTarget& target = *App;

	Map map;
	sf::Event ev;
	sf::Clock clock;
    while(App->isOpen()){
        while(App->pollEvent(ev)){
            if(ev.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                App->close();
			}
        }
		App->clear();
		sf::Time time=clock.getElapsedTime();
		float deltaTime=time.asSeconds()/1000;
		map.update(deltaTime);
		map.draw(target);
		App->display();

		/*
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            boxBody->ApplyForce(b2Vec2(1.f, 0.0f), boxBody->GetWorldCenter());
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            boxBody->ApplyForce(b2Vec2(-1.f, 0.0f), boxBody->GetWorldCenter());
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            boxBody->ApplyLinearImpulse(b2Vec2(0.f, 0.5f), boxBody->GetWorldCenter());
		*/
		/*
        world->Step(timeStep, velIt, posIt);
        b2Vec2 groundPosition = groundBody->GetPosition();
        b2Vec2 boxPos = boxBody->GetPosition();

        App->setView(gameView);

        App->clear(sf::Color(100, 175, 255));

        groundRect.setPosition(groundPosition.x - 10.0f, -(groundPosition.y + 1.0f));
        App->draw(groundRect);

        boxRect.setPosition(boxPos.x - 0.5f, -(boxPos.y + 0.5f));
        App->draw(boxRect);
		*/
    }

    //delete world;
	
    delete App;

    return 0;
}