#include <vector>
#include <string>

using std::string;
using std::vector;

class DynamicEnum
{
private:
	std::vector<std::string> raw;

public:
	typedef int index_t;

	index_t Get(string name)
	{
		for (index_t index = 0; index < raw.size; index++)
		{
			if (raw[index] == name)
			{
				return (int)index;
			}
		}

		return -1;
	}

	
	string Get(index_t enumeration)
	{
		return raw[enumeration];
	}


	void Set(string name, index_t enumeration)
	{
		if (enumeration < raw.size)
		{
			raw[enumeration] = name;
		}
		else
		{
			raw.resize(enumeration + 1);
			raw[enumeration] = name;
		}
	}


	index_t Add(string name)
	{
		auto enumeration = raw.size;

		raw.push_back(name);

		return enumeration;
	}


	index_t 
};