#pragma once

class PrimitiveSceneProxy
{
public:
	PrimitiveSceneProxy();
	~PrimitiveSceneProxy();

	virtual void Render(float x, float y) = 0;

private:

};