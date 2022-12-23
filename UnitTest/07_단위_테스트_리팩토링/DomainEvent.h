#pragma once
#include "User.h"

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
	UpdateUserEmailEvent(IMessageBus* messageBus, int userId, string email);
};

class ILogger;
class UpdateUserTypeEvent : public DomainEvent {
private:
	ILogger* logger;
public:
	UpdateUserTypeEvent(int userId, UserType prev, UserType next);
};