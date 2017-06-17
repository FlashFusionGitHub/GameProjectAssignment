#pragma once
#include "DynamicArray.h"
#include "IGameState.h"
#include <Renderer2D.h>
#include <vector>

class GameStateManager
{
public:
	GameStateManager(unsigned int stateCount) {
		m_registeredStates.resize(stateCount);
	};

	~GameStateManager() {
		for (auto state : m_registeredStates) delete state;
	};

	void registerState(int id, IGameState* state) {
		m_registeredStates[id] = state;
	}
	void pushState(int id) {
		m_pushedStates.push_back(m_registeredStates[id]);
	}
	void popState() {
		m_popState = true;
	}

	void update(float deltaTime) {
		while (m_popState) {
			m_popState = false;

			// deactive previous top
			m_stateStack.back()->exit();
			auto temp = m_stateStack.back();
			m_stateStack.pop_back();
			temp->onPopped();

			//activate tyhe one under the previous top if it exists
			if (m_stateStack.empty() == false)
				m_stateStack.back()->enter();
		}

		for (auto pushedState : m_pushedStates) {
			//deactivate previous top
			if (m_stateStack.empty() == false)
				m_stateStack.back()->exit();

			//activate new top
			pushedState->onPushed();
			m_stateStack.push_back(pushedState);
			m_stateStack.back()->enter();
		}
		m_pushedStates.clear();

		for (auto state : m_stateStack)
			state->onUpdate(deltaTime);
	}

	void draw() {
		for (auto state : m_stateStack)
			state->onDraw(renderer);
	}

	int activeStateCount() { return m_stateStack.size(); }
	IGameState* getTopState() { return m_stateStack.back(); }
	IGameState* getState(int id) { return m_registeredStates[id]; }

private:
	DynamicArray<IGameState*> m_pushedStates;
	bool m_popState = false;

	DynamicArray<IGameState*> m_stateStack;
	DynamicArray<IGameState*> m_registeredStates;
	aie::Renderer2D* renderer;
};

