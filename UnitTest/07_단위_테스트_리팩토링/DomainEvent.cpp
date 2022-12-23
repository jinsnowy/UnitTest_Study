#include "pch.h"
#include "DomainEvent.h"
#include "Application.h"
#include "EventDispatcher.h"

void DomainEvent::Execute()
{
	action();
}

UpdateUserEmailEvent::UpdateUserEmailEvent(int userId, string email, IMessageBus* messageBus)
{
	action = [=]() {
		messageBus->SendEmailChangedMessage(userId, email);
	};
}

UpdateUserTypeEvent::UpdateUserTypeEvent(int userId, UserType prev, UserType next)
	:
	logger(Logger::GetInstance())
{
	action = [=]() {
		logger->Log(Format("UserId(%d) changed type from %d to %d", userId, (int)prev, (int)next));
	};
}
