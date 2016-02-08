#pragma once
#include "BaseProperty.h"

template <typename type>
class Property :
	public BaseProperty
{
public:
	type value;


	Property()
	{
		// Do nothing
	}


	Property(const type& _value)
	{
		value = _value;
	}


	string Name()
	{
		return typeid(type).name();
	}
};

