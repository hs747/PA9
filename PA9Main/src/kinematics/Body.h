/*
	file: Body.h
	desc: high level body class
*/
#pragma once

#include "SFML/Graphics.hpp"

#include "../math/Vec2.h" // Vector2f type and functions

enum class BodyType {
	Point	= 0,
	Circle	= 1 << 0,
	AABB	= 1 << 1,
};

class Body : public sf::Transformable {

private:
	int index; // index of the body in the list it resides in? (needs to be accessible from both the users and the body sytem)
	int id; // 'unique' identifier for the body (only to the body system it is currently in)
public:

	// moved these to public for ease of use
	Vector2f velocity;

	//Body object constructor
	Body(Vector2f pos) :
		velocity(Vec2::Zero)
	{
		setPosition(pos);
		index = -1;
		id = -1;
	}

	Body(float xPos, float yPos) :
		Body(Vector2f(xPos, yPos)) {}

	void resolveCollision(Vector2f offset) {
		setPosition(getPosition() - offset);
	}

	//Change the value of the velocity
	void setVelocity(Vector2f newVelocity) {
		velocity = newVelocity;
	}

	//Get the current Velocity of the object
	Vector2f getVelocity() { //might make virtual to make sure walls always return a value of 0
		return velocity;
	}

	// desc: get list index for body (internal to BodySystem)
	int getIndex() const {
		return index;
	}

	// desc: set list index for body (internal to BodySystem)
	void setIndex(int nIndex) {
		index = nIndex;
	}

	// desc: getter for id (intended to be used publically)
	int getId() const {
		return id;
	}
	
	// desc: setter for id (should only be used internally by BodySystem)
	void setId(int newId) {
		id = newId;
	}

	// desc: get the minimum(ish) bounding box of the the given body
	virtual sf::FloatRect getAABB() const {
		Vector2f position = getPosition();
		return sf::FloatRect(position.x, position.y, 0.f, 0.f);
	}

	// desc: identify the type of the body for the manager system (could consider using some kind of dynamic dispatch instead here)
	virtual BodyType getType() const { return BodyType::Point; }

	virtual void debug_draw(sf::RenderTarget& rt) const {
		sf::CircleShape circle(3.f, 16);
		circle.setOrigin(circle.getRadius(), circle.getRadius());
		circle.setFillColor(sf::Color::Transparent);
		circle.setOutlineColor(sf::Color::Red);
		circle.setOutlineThickness(2.f);
		rt.draw(circle, getTransform());
	}
};