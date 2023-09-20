
#include "GraphicsBufferManager.h"

GraphicsBufferManager::GraphicsBufferManager() 
{

}

GraphicsBufferManager::~GraphicsBufferManager() 
{
	clear();
}

void GraphicsBufferManager::addGraphicsBuffer(GraphicsBuffer *buffer, std::string key) 
{
	
	if (mGraphicsBufferMap.count(key) == 0) //Checks to see if the key has already been added before
	{
		mGraphicsBufferMap[key] = buffer;
	}
	
}

void GraphicsBufferManager::deleteGraphicsBuffer(std::string key) 
{
	delete mGraphicsBufferMap[key];
	mGraphicsBufferMap.erase(key);
}

GraphicsBuffer* GraphicsBufferManager::getGraphicsBuffer(std::string key)
{
	return mGraphicsBufferMap[key];
}

void GraphicsBufferManager::clear() 
{
	//delete the buffers in the map 

	std::map<std::string, GraphicsBuffer*>::iterator it = mGraphicsBufferMap.begin();

	while (it != mGraphicsBufferMap.end())
	{
		delete it->second;
		it++;
	}
	
	//iterate through the map and delete each buffer. 
	mGraphicsBufferMap.clear(); //clear the map
}
