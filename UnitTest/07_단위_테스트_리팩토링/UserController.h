#pragma once

class IDatabase;
class IMessageBus;
class IEventDispatcher;
class UserController
{
private:
	IDatabase* _database;
	IMessageBus* _messageBus;
	IEventDispatcher* _eventDispatcher;

public:
	UserController();

	UserController(IDatabase* database, IMessageBus* messageBus);

	UserController(IDatabase* database, IMessageBus* messageBus, IEventDispatcher* eventDispatcher);

	void ChangeEmailV1(int userId, string newEmail);

	bool ChangeEmailV2(int userId, string newEmail);

	bool ChangeEmailV3(int userId, string newEmail);

	bool ChangeEmailV4(int userId, string newEmail);
};