
#include "Assets/Asset.h"

Asset::Asset(string _path) : path(_path),
                             isInitialized(false),
                             isBound(false) 
{
}

bool Asset::BindIfNeeded() 
{
	if (!isBound)
	{
		SafeBind();
		return true;
	}

	return false;
}

void Asset::UnbindIfNeeded(bool check) 
{
	if (check)
		SafeUnbind();
}

void Asset::UnbindIfNeeded() 
{
	if (isBound)
		SafeUnbind();
}

void Asset::SafeBind() 
{
	isBound = true;

}

void Asset::SafeUnbind() 
{
	isBound = false;
}

string Asset::GetDirectory() 
{
	auto lastSlash = path.find_last_of("/");

	if (lastSlash == string::npos)
		return path;

	return path.substr(0, lastSlash + 1);
}

void Asset::Unbind() 
{

}

void Asset::Bind() 
{

}