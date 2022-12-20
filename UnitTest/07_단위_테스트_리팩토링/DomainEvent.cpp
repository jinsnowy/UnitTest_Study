#include "pch.h"
#include "DomainEvent.h"
#include "Application.h"

void DomainEvent::Execute()
{
	action();
}

UpdateUserEmailEvent::UpdateUserEmailEvent(IMessageBus* messageBus, int userId, string email)
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
