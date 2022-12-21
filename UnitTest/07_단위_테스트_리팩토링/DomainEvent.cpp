#include "pch.h"
#include "DomainEvent.h"
#include "Application.h"
#include "EventDispatcher.h"

void DomainEvent::Execute(IEventDispatcher* dispatcher)
{
	action(dispatcher);
}

UpdateUserEmailEvent::UpdateUserEmailEvent(int userId, string email)
{
	action = [=](IEventDispatcher* dispatcher) {
		auto _messageBus = EventHandler::GetEventHandler<IMessageBus>(dispatcher);
		if (_messageBus) {
			_messageBus->SendEmailChangedMessage(userId, email);
		}
	};
}

UpdateUserTypeEvent::UpdateUserTypeEvent(int userId, UserType prev, UserType next)
	:
	logger(Logger::GetInstance())
{
	action = [=](IEventDispatcher* dispatcher) {
		auto _logger = EventHandler::GetEventHandler<ILogger>(dispatcher);
		if (_logger) {
			_logger->Log(Format("UserId(%d) changed type from %d to %d", userId, (int)prev, (int)next));
		}
	};
}
