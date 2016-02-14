#pragma once
#include "Node.h"

class BaseModifier
	: public Node
{
	float weight;

	virtual void BaseUpdate() = NULL;
};