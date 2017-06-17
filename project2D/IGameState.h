#pragma once
#include <Renderer2D.h>

class IGameState
{
	friend class GameStateManager;
public:
	IGameState() {}
	virtual ~IGameState() {}
	bool isActive() const { return m_active; }

protected:

	virtual void onUpdate(float deltaTime) = 0;
	virtual void onDraw(aie::Renderer2D* renderer) = 0;

	void enter() { m_active = true; onEnter(); }
	void exit() { m_active = false; onExit(); }

	virtual void onEnter() {}
	virtual void onExit() {}
	virtual void onPushed() {}
	virtual void onPopped() {}

private:
	bool m_active = false;
};

