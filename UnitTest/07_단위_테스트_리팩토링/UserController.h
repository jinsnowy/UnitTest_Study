#pragma once

class Database;
class MessageBus;
class UserController
{
private:
	Database* _database;
	MessageBus* _messageBus;

public:
	UserController();

	UserController(Database* database, MessageBus* messageBus);

	void ChangeEmailV1(int userId, string newEmail);

	bool ChangeEmailV2(int userId, string newEmail);

	bool ChangeEmailV3(int userId, string newEmail);
};