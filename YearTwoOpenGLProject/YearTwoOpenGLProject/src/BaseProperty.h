#pragma once
#include <vector>
#include "BaseModifier.h"

class BaseProperty : public Node
{
public:
	std::vector<BaseModifier*> modifiers;

	virtual string Name()
	{
		return "BaseProperty";
	}
};

