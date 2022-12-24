#pragma once

class Database;
class IMessageBus;
class EventDispatcher;
class Transaction;
class UserRepository;
class CompanyRepository;

class UserController
{
private:
	Database* _database;
	IMessageBus* _messageBus;
	EventDispatcher* _eventDispatcher;

public:
	UserController();

	UserController(Database* database, IMessageBus* messageBus);

	UserController(Database* database, IMessageBus* messageBus, EventDispatcher* eventDispatcher);

	void ChangeEmailV1(int userId, string newEmail);

	bool ChangeEmailV2(int userId, string newEmail);

	bool ChangeEmailV3(int userId, string newEmail);

	void ChangeEmailV4(int userId, string newEmail);

private:
	Transaction* _transaction;
	UserRepository* _userRepository;
	CompanyRepository* _companyRepository;

public:
	UserController(Transaction* transaction, IMessageBus* messageBus, EventDispatcher* eventDispatcher);

	UserRepository* GetUserRepository();
	CompanyRepository* GetCompanyRepository();

	void ChangeEmailV5(int userId, string newEmail);
};