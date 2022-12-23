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

class EventDispatcher
{
public:
	void Dispatch(vector<DomainEvent*>& domainEvents);
};

class EventHandler {
public:
	static EventHandler& Get() { static EventHandler handler; return handler; }

	template<typename T>
	static void SetEventHandler(EventDispatcher* owner, T* eventHandler) {
		const char* key = Reflection::GetTypeName<T>();
		Get().eventHandlers[owner][key] = eventHandler;
	}

	template<typename T>
	static T* GetEventHandler(EventDispatcher* owner) {
		const char* key = Reflection::GetTypeName<T>();
		return (T*)(Get().eventHandlers[owner][key]);
	}

	static void Clear() {
		Get().eventHandlers.clear();
	}

private:
	unordered_map<EventDispatcher*, unordered_map<const char*, void*>> eventHandlers;
};