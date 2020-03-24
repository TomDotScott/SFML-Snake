#pragma once

//StateManager will come later
class StateManager;

class BaseState
{
	friend class StateManager;
public:
	BaseState(StateManager* _stateManager) : m_stateManager(_stateManager), m_transparent(false), m_transcendent(false)	{ }
	
	virtual ~BaseState();

	//Force methods through all states. Make them abstract 
	virtual void OnCreate() = 0;
	virtual void OnDestroy() = 0;

	virtual void Activate() = 0;
	virtual void Deactivate() = 0;

	virtual void Update() = 0;
	virtual void Render() = 0;

	//if it needs to render the state before
	void SetTransparent(const bool& _transparent) { m_transparent = _transparent; }
	bool IsTransparent() const { return m_transparent; }

	//if it needs to render the state after
	void SetTranscendent(const bool& _transcendence) { m_transcendent = _transcendence; }
	bool IsTranscendent() const { return m_transcendent; }

	StateManager* GetStateManager() const { return m_stateManager; }
protected:
	StateManager* m_stateManager;
	bool m_transparent;
	bool m_transcendent;
};
