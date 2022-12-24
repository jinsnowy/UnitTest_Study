#include "pch.h"
#include "EventDispatcher.h"
#include "DomainEvent.h"

void EventDispatcher::Dispatch(vector<DomainEvent*>& domainEvents)
{
	for (const auto& domainEvent : domainEvents) {
		domainEvent->Execute();
		delete domainEvent;
	}
	
	domainEvents.clear();
}