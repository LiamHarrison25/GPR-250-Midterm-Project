#pragma once
#include <Trackable.h>
#include <Vector2D.h>
#include "GraphicsBuffer.h"

class GraphicsBuffer; //forward declaration

class Sprite :public Trackable
{
	friend class GraphicsSystem;
public:

	//---constructors/destructor---
	Sprite();
	Sprite(Vector2D sourceLoc, float height, float width, GraphicsBuffer* graphicsBuffer);
	~Sprite();

	//---getters and setters---

	void setSourceLoc(Vector2D sourceLoc);
	Vector2D getSourceLoc();

	void setWidth(float width);
	float getWidth();

	void setHeight(float height);
	float getHeight();

	void setGraphicsBuffer(GraphicsBuffer* graphicsBuffer);
	GraphicsBuffer* getGraphicsBuffer();

	void cleanup();

private:

	Vector2D mSourceLoc; //upper left-hand corner of where the sprite begins
	float mHeight;
	float mWidth;
	GraphicsBuffer* mGraphicsBuffer;
	bool mOwnsBuffer;
};
