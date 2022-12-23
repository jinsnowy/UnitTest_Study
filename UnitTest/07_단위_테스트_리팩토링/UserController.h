#pragma once

class Database;
class IMessageBus;
class UserController
{
private:
	Database* _database;
	IMessageBus* _messageBus;

public:
	UserController();

	UserController(Database* database, IMessageBus* messageBus);

	void ChangeEmailV1(int userId, string newEmail);

	bool ChangeEmailV2(int userId, string newEmail);

	bool ChangeEmailV3(int userId, string newEmail);

	void ChangeEmailV4(int userId, string newEmail);
};