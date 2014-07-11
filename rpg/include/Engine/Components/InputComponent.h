#include "ActorComponent.h"
#include "hge.h"
#include <map>

typedef void(*funcPtr)();

class InputComponent : public IActorComponent {
public:
	InputComponent();

	InputComponent(AActor* _owner);

	void addKeyBinding(hgeKeyCode_t _key, funcPtr _funcPtr);

	void executeKeyAction(HGE* _gameSession);

private:
	std::map<hgeKeyCode_t, funcPtr> m_keymapping;

};