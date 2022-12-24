#include "pch.h"
#include "UserController.h"
#include "Application.h"
#include "User.h"
#include "Company.h"
#include "DomainEvent.h"
#include "EventDispatcher.h"

#include "Repository.h"
#include "Transaction.h"

UserController::UserController() {
	_database = new Database();
	_messageBus = new MessageBus();
	_eventDispatcher = new EventDispatcher();
}

UserController::UserController(Database* database, IMessageBus* messageBus)
{
	_database = database;
	_messageBus = messageBus;
	_eventDispatcher = new EventDispatcher();
}

UserController::UserController(Database* database, IMessageBus* messageBus, EventDispatcher* eventDispatcher) {
	_database = database;
	_messageBus = messageBus;
	_eventDispatcher = eventDispatcher;
}

void UserController::ChangeEmailV1(int userId, string newEmail)
{
	auto data = _database->GetUserById(userId);
	string email = std::get<0>(data);
	UserType type = (UserType)(std::get<1>(data));

	User user = User(userId, email, type);

	auto companyData = _database->GetCompany();
	string companyDomainName = std::get<0>(companyData);
	int numberOfEmployees = std::get<1>(companyData);

	int newNumberOfEmployees = user.ChangeEmailV1(newEmail, companyDomainName, numberOfEmployees);

	_database->SaveCompany(newNumberOfEmployees);
	_database->SaveUser(user);
	_messageBus->SendEmailChangedMessage(userId, newEmail);
}

bool UserController::ChangeEmailV2(int userId, string newEmail)
{
	auto data = _database->GetUserById(userId);
	auto companyData = _database->GetCompany();

	string email = std::get<0>(data);
	UserType type = (UserType)(std::get<1>(data));

	string companyDomainName = std::get<0>(companyData);
	int numberOfEmployees = std::get<1>(companyData);

	User user = User::CreateUser(userId, email, type);
	Company company = Company::CreateCompany(companyDomainName, numberOfEmployees);

	bool isSuccess = user.ChangeEmailV2(newEmail, company);
	if (isSuccess) {
		_database->SaveCompany(company);
		_database->SaveUser(user);
		_messageBus->SendEmailChangedMessage(userId, newEmail);
	}
	
	return isSuccess;
}

bool UserController::ChangeEmailV3(int userId, string newEmail)
{
	auto data = _database->GetUserById(userId);

	string email = std::get<0>(data);
	UserType type = (UserType)(std::get<1>(data));

	// Can Execute -> Execute ÆÐÅÏ
	User user = User::CreateUser(userId, email, type);
	if (user.isEmailEquals(newEmail) == true) {
		return false;
	}

	auto companyData = _database->GetCompany();

	string companyDomainName = std::get<0>(companyData);
	int numberOfEmployees = std::get<1>(companyData);

	Company company = Company::CreateCompany(companyDomainName, numberOfEmployees);

	bool isSuccess = user.ChangeEmailV3(newEmail, company);
	if (isSuccess) {
		_database->SaveCompany(company);
		_database->SaveUser(user);

		for (auto& domainEvent : user._domainEvents) {
			domainEvent->Execute();
			delete domainEvent;
		}
	}

	return isSuccess;
}

void UserController::ChangeEmailV4(int userId, string newEmail)
{
	auto data = _database->GetUserById(userId);

	string email = std::get<0>(data);
	UserType type = (UserType)(std::get<1>(data));

	User user = User::CreateUser(userId, email, type);
	auto companyData = _database->GetCompany();

	string companyDomainName = std::get<0>(companyData);
	int numberOfEmployees = std::get<1>(companyData);

	Company company = Company::CreateCompany(companyDomainName, numberOfEmployees);

	// Fast Failure Principle
	user.ChangeEmailV4(newEmail, company, _messageBus);

	_database->SaveCompany(company);
	_database->SaveUser(user);
	_eventDispatcher->Dispatch(user._domainEvents);
}

UserController::UserController(Transaction* transaction, IMessageBus* messageBus, EventDispatcher* eventDispatcher)
	:
	_transaction(transaction),
	_messageBus(messageBus),
	_eventDispatcher(eventDispatcher)
{
	_userRepository = new UserRepository(transaction);
	_companyRepository = new CompanyRepository(transaction);
}

void UserController::ChangeEmailV5(int userId, string newEmail)
{
	auto data = _userRepository->GetUserById(userId);

	string email = std::get<0>(data);
	UserType type = (UserType)(std::get<1>(data));

	User user = User::CreateUser(userId, email, type);
	auto companyData = _companyRepository->GetCompany();

	string companyDomainName = std::get<0>(companyData);
	int numberOfEmployees = std::get<1>(companyData);

	Company company = Company::CreateCompany(companyDomainName, numberOfEmployees);

	user.ChangeEmailV4(newEmail, company, _messageBus);

	// Sync to DB
	auto trGuard = _transaction->Start();
	_companyRepository->SaveCompany(company);
	_userRepository->SaveUser(user);
	trGuard.Commit();
	
	_eventDispatcher->Dispatch(user._domainEvents);
}

UserRepository* UserController::GetUserRepository()
{
	return _userRepository;
}

CompanyRepository* UserController::GetCompanyRepository()
{
	return _companyRepository;
}