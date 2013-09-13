#pragma once

class BaseScene
{
public:
	enum STATE{ STATE_INIT = 0, STATE_LOOP, STATE_END, STATE_NUM };

private:
	STATE state;

public:
	BaseScene();
	void NextState();
	STATE GetState();

public:
	virtual void Initialize() = 0;
	virtual void Run(float dt) = 0;
	virtual void Destroy() = 0;
};

