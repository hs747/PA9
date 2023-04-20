/*
	file: BodySystem.cpp
	desc: implements the BodySystem class
*/

#include "BodySystem.h"

// BODY SYSTEM IMPL

BodySystem::BodySystem() {}

void BodySystem::update(float dt) {
	// clear last step's collision records
	debug_collisions.clear();

	// integrate positions from velocity
	for (int i = 0; i < dynamicBodies.size(); ++i) {
		Body& b = *dynamicBodies[i];
		Vec2f p0 = b.getPosition();
		Vec2f v = b.velocity;
		Vec2f p1 = p0 + v * dt;
		b.setPosition(p1);
	}

	// detect and resolve dynamic-dynamic collisions O(n^2) approach
	CollisionResult result;
	for (int i = 0; i < dynamicBodies.size(); ++i) {
		Body& b1 = *dynamicBodies[i];
		BodyType type1 = b1.getType();
		if (type1 == BodyType::Point)
			continue;

		result.collided = false;
		for (int j = 0; j < dynamicBodies.size(); ++j) {
			if (j == i) // don't do check on current
				continue;
			Body& b2 = *dynamicBodies[j];
			BodyType type2 = b1.getType();
			if (type2 == BodyType::Point)
				continue;

			uint typeMask = (uint)type1 | (uint)type2;
			if (typeMask == (uint)BodyType::Circle) {
				result = checkCircleCircleCollide(static_cast<CircleBody&>(b1), static_cast<CircleBody&>(b2));
			}

			if (result.collided) {
				debug_collisions.push_back(result);
			}
		}
	}

	// detect and resolve dynamic-static(tiles) collisions
}

void BodySystem::addBody(Body& body)
{
	// this kind of enforces duplicate pointers to bodies not being in the system
	if (!invalidBodyIndex(body.getIndex()))
		return;

	uint index = dynamicBodies.size();
	body.setIndex(index);
	dynamicBodies.push_back(&body);
}

void BodySystem::removeBody(Body& body)
{
	uint index = body.getIndex();
	// make sure we aren't messing up due to a body not actually being in the list
	if (invalidBodyIndex(index))
		return; 
	// to keep the bodies vector contiguous, am swapping the last element with whatever we remove
	// then popping the back
	dynamicBodies[index] = dynamicBodies.back(); 
	dynamicBodies.pop_back();
	
	// mark the body as not being in a list just in case
	body.setIndex(-1);
}

bool BodySystem::invalidBodyIndex(uint index) {
	return index == -1;
	// todo: possible bounds checking
}

void BodySystem::debug_drawBodies(sf::RenderTarget& renderTarget) {
	for (int i = 0; i < dynamicBodies.size(); ++i) {
		Body& b = *dynamicBodies[i];
		b.debug_draw(renderTarget);
	}
}

void BodySystem::debug_drawCollisions(sf::RenderTarget& renderTarget) {
	CollisionResult result;
	while (!debug_collisions.empty()) {
		result = debug_collisions.back();
		debug_collisions.pop_back();
		result.debug_draw(renderTarget);
	}
	// jic:
	debug_collisions.clear();
}

CollisionResult BodySystem::checkCircleCircleCollide(const CircleBody& b1, const CircleBody& b2) {
	CollisionResult result;
	Vec2f r = b2.getPosition() - b1.getPosition();
	float d12 = b1.radius + b2.radius;
	if (r.dot(r) < d12 * d12) {
		result.collided = true;
		float d = r.mag();
		float o = d12 - d; // intersection depth between circle surface
		float m1 = b1.radius - o / 2; // distance from intersection midpoint and b1 surface
		result.offset = r / d * o;
		result.point = r / d * m1 + b1.getPosition();
	}
	else {
		result.collided = false;
	}

	return result;
}