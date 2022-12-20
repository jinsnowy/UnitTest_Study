#include "pch.h"
#include "UserController.h"
#include "Application.h"
#include "User.h"
#include "Company.h"
#include "DomainEvent.h"

UserController::UserController() {
	_database = new NullDatabase();
	_messageBus = new MessageBus();
}

UserController::UserController(IDatabase* database, IMessageBus* messageBus) {
	_database = database;
	_messageBus = messageBus;
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

	// Fast Fail Principle 빠른 실패 원칙
	User user = User::CreateUser(userId, email, type);
	if (user.isEmailEquals(newEmail) == true) {
		return false;
	}

	auto companyData = _database->GetCompany();

	string companyDomainName = std::get<0>(companyData);
	int numberOfEmployees = std::get<1>(companyData);

	Company company = Company::CreateCompany(companyDomainName, numberOfEmployees);

	bool isSuccess = user.ChangeEmailV3(newEmail, company, _messageBus);
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