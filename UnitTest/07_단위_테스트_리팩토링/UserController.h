#pragma once

#include "Component.h"
#include "User.h"
#include "Company.h"

class UserController
{
private:
	Database _database;
	MessageBus _messageBus;

public:
	void ChangeEmailV1(int userId, string newEmail);

	bool ChangeEmailV2(int userId, string newEmail);

	bool ChangeEmailV3(int userId, string newEmail);
};