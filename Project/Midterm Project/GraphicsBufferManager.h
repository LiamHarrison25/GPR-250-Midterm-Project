#pragma once

#include <Trackable.h>
#include <vector>
#include <map>
#include "GraphicsBuffer.h"

//typedef template< const key, T> value_type;

class GraphicsBufferManager : public Trackable
{
public:

	GraphicsBufferManager();
	~GraphicsBufferManager();

	void addGraphicsBuffer(GraphicsBuffer *buffer, std::string key); 
	void deleteGraphicsBuffer(std::string key);
	GraphicsBuffer* getGraphicsBuffer(std::string key);
	void clear();

private:
	
	//map for the graphics buffers
	std::map<std::string, GraphicsBuffer*> mGraphicsBufferMap;

	//Used this for reference on std::maps: https://www.geeksforgeeks.org/map-associative-containers-the-c-standard-template-library-stl/ 

};
