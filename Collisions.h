#pragma once
#include "Commons.h"
#include "Character.h"
class Collisions
{
private:
	static Collisions* m_instance;
	Collisions();

public:
	~Collisions();

	static Collisions* Instance();

	bool Circle(Character* character1, Character* character2);
	bool Box(Rect2D rect1, Rect2D rect2);

};