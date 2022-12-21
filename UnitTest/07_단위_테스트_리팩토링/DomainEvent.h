#pragma once
#include "User.h"

class ILogger;
class IEventDispatcher;
class DomainEvent
{
protected:
	function<void(IEventDispatcher*)> action;

public:
	virtual void Execute(IEventDispatcher*) sealed;
};

class UpdateUserEmailEvent : public DomainEvent {
public:
	UpdateUserEmailEvent(int userId, string email);
};

class UpdateUserTypeEvent : public DomainEvent {
private:
	// 생성자에서 보이지 않는 숨겨진 의존성 주입
	ILogger* logger;

public:
	UpdateUserTypeEvent(int userId, UserType prev, UserType next);
};