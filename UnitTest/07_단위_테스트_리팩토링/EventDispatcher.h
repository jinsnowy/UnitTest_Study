#pragma once

class DomainEvent;

class Reflection {
public:
	template<typename T>
	static const char* GetTypeName() {
		static const char* typeName = typeid(T).name();
		return typeName;
	}
};


class IEventDispatcher
{
public:
	virtual void Dispatch(vector<DomainEvent*>& domainEvents) abstract;
};

class NullEventDispatcher : public IEventDispatcher {
public:
	virtual void Dispatch(vector<DomainEvent*>& domainEvents) override;
};

class EventDispatcher : public IEventDispatcher
{
public:
	virtual void Dispatch(vector<DomainEvent*>& domainEvents) override;
};



class EventHandler {
public:
	static EventHandler& Get() { static EventHandler handler; return handler; }

	template<typename T>
	static void SetEventHandler(IEventDispatcher* owner, T* eventHandler) {
		const char* key = Reflection::GetTypeName<T>();
		Get().eventHandlers[owner][key] = eventHandler;
	}

	template<typename T>
	static T* GetEventHandler(IEventDispatcher* owner) {
		const char* key = Reflection::GetTypeName<T>();
		return (T*)(Get().eventHandlers[owner][key]);
	}

	static void Clear() {
		Get().eventHandlers.clear();
	}

private:
	unordered_map<IEventDispatcher*, unordered_map<const char*, void*>> eventHandlers;
};