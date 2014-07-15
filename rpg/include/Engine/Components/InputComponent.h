#include "ActorComponent.h"
#include "hge.h"
#include <map>

class Character;

//typedef void(AActor::*ActorActionFunc)();

template<typename FuncSignature>
class Callback;

template<typename R>
class Callback<R()> {
public:
	typedef R(*FuncType)(void*);

	Callback() : obj(0), func(0) {}
	Callback(void* o, FuncType f) : obj(o), func(f) {}

	R operator()() const {
		return (*func)(obj);
	}

	typedef void* Callback::*SafeBoolType;
	operator SafeBoolType() const {
		return func != 0 ? &Callback::obj : 0;
	}

	bool operator!() const {
		return func == 0;
	}

private:
	void* obj;
	FuncType func;
};

template<typename R> // Undefined on purpose
void operator==(const Callback<R()>&, const Callback<R()>&);
template<typename R>
void operator!=(const Callback<R()>&, const Callback<R()>&);

template<typename R, class T>
struct DeduceMemCallbackTag {
	template<R(T::*Func)()>
	static R Wrapper(void* o) {
		return (static_cast<T*>(o)->*Func)();
	}

	template<R(T::*Func)()>
	inline static Callback<R()> Bind(T* o) {
		return Callback<R()>(o, &DeduceMemCallbackTag::Wrapper<Func>);
	}
};

template<typename R, class T>
DeduceMemCallbackTag<R, T> DeduceMemCallback(R(T::*)()) {
	return DeduceMemCallbackTag<R, T>();
}

#define BIND_MEM_CB(memFuncPtr, instancePtr) \
	(DeduceMemCallback(memFuncPtr).Bind<(memFuncPtr)>(instancePtr))

class InputComponent : public IActorComponent {
public:
	InputComponent();

	InputComponent(Character* _owner);

	void addKeyBinding(hgeKeyCode_t _key, Callback<void()> _delegate);

	void executeKeyAction(HGE* _gameSession);

private:
	std::map<hgeKeyCode_t, Callback<void()> > m_keymapping;

};