#include "hge.h"
#include "VarArgDelegate.h"
#include "ActorComponent.h"
#include <map>

class Character;

//typedef void(AActor::*ActorActionFunc)();

class InputComponent : public IActorComponent {
public:
	InputComponent();

	InputComponent(Character* _owner);

	void addKeyBinding(hgeKeyCode_t _key, Callback<void()> _delegate);

	void executeKeyAction(HGE* _gameSession);

private:
	std::map<hgeKeyCode_t, Callback<void()> > m_movementKeyMapping;

};