
#ifndef GAMEENTITY_H
#define GAMEENTITY_H

class GameEntity {

public:
	GameEntity();
	GameEntity(float _x_position, float _y_position);
	~GameEntity();

	// getters
	float GetXPosition() { return x_position; }
	float GetYPosition() { return y_position; }

	float GetXRotation() { return x_rotation; }
	float GetYRotation() { return y_rotation; }

	float GetXScale() { return x_scale; }
	float GetYScale() { return y_scale; }

	// setters
	void SetXPosition(float _x_position) { x_position = _x_position; }
	void SetYPosition(float _y_position) { y_position = _y_position; }

	void SetXRotation(float _x_rotation) { x_rotation = _x_rotation; }
	void SetYRotation(float _y_rotation) { y_rotation = _y_rotation; }
	// update function is also required for all game objects
	virtual void Update(float _dt) = 0;
	virtual void Render(float _x_position, float _y_position) = 0;
protected:
	// transform information is required for all game objects
	// automatically available to all inherited classes
	float x_position;
	float y_position;
	float x_rotation;
	float y_rotation;
	float x_scale;
	float y_scale;

private:


};

#endif