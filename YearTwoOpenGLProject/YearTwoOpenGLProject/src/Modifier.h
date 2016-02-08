#pragma once
#include <exception>
#include "Property.h"
#include "BaseModifier.h"

template <typename type>
class Modifier
	: public BaseModifier
{
public:
	void BaseUpdate(BaseProperty& property)
	{
		Property<type> * typed_property = (Property<type>*)(&property);

		Update(typed_property->value);
	}

	void Add(const Modifier<type>& other)
	{
		if (other.Name() == Name())
		{
			weight += other.weight;
		}
		else
		{
			throw std::invalid_argument("Cannot add different modifier types together");
		}
	}

#pragma region Operator Overloads
	
	public void operator+=(const Modifier<type>& other)
	{
		Add(other);
	}

	public Modifier<type> operator+(const Modifier<type>& other)
	{
		Modifier<type> result = *this;
		result.Add(other);

		return result;
	}

#pragma endregion

private:
	virtual void Update(type& value) = NULL;
};