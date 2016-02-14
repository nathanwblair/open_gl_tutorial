#pragma once
#include <map>
#include <string>

using std::string;

class Node
{
public:
	std::map<string, Node*> children;


	Node()
	{

	}

	virtual Node& Add(Node * node)
	{
		children[node->Name()] = node;
		return *node;
	}


	virtual Node& Get(string name)
	{
		return *(children[name]);
	}


	virtual string Name()
	{
		return "Node";
	}
};

