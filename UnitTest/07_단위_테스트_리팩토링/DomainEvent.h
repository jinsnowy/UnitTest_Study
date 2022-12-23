#pragma once
#include "User.h"

class ILogger;
class IEventDispatcher;
class DomainEvent
{
protected:
	function<void()> action;

public:
	virtual void Execute() sealed;
};

class IMessageBus;

class UpdateUserEmailEvent : public DomainEvent {
public:
	UpdateUserEmailEvent(int userId, string email, IMessageBus* messageBus);
};

class UpdateUserTypeEvent : public DomainEvent {
private:
	ILogger* logger;

public:
	UpdateUserTypeEvent(int userId, UserType prev, UserType next);
};