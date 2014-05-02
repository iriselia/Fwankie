#include "TriggerRegion.h"

template <class Entity_Type>
class Trigger : public GameEntity {
private:

	TriggerRegion* m_pRegionOfInfluence;

	bool m_bRemoveFromGame;

	bool m_bActive;

	int m_iGraphNodeIndex;

protected:

	void SetGraphNodeIndex(int _index) { m_iGraphNodeIndex = _index; }
	void SetToBeRemovedFromGame() { m_bRemoveFromGame = true; }
	void SetInactive() { m_bActive = false; }
	void SetActive() { m_bActive = true; }
	bool isTouchingTrigger(float _x, float _y, float _entityRadius)const;
	void AddCircularTriggerRegion(float _x, float _y, float _radius);

public:

	Trigger(unsigned int id);
	virtual ~Trigger();

	virtual void Try(Entity_Type*) = 0;

	virtual void Update() = 0;

	int getGraphNodeIndex()const { return m_iGraphNodeIndex; }
	bool isToBeRemoved()const { return m_bRemoveFromGame; }
	bool isActive() { return m_bActive; }
};
