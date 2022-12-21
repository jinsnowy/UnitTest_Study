#include "pch.h"
#include "EventDispatcher.h"
#include "DomainEvent.h"

void EventDispatcher::Dispatch(vector<DomainEvent*>& domainEvents)
{
	for (const auto& domainEvent : domainEvents) {
		domainEvent->Execute(this);
		delete domainEvent;
	}
	
	domainEvents.clear();
}

void NullEventDispatcher::Dispatch(vector<DomainEvent*>& domainEvents)
{
	for (const auto& domainEvent : domainEvents) {
		delete domainEvent;
	}

	domainEvents.clear();
}
