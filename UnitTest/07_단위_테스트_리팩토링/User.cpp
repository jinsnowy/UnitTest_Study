#include "pch.h"
#include "User.h"
#include "Company.h"
#include "DomainEvent.h"

User::User(string email, UserType type)
	:
	_userId(-1), _email(email), _type(type)
{
}

User::User(int userId, std::string email, UserType type)
	:
	_userId(userId), _email(email), _type(type)
{}

bool User::isEmailEquals(string email)
{
	return _email == email;
}

User User::CreateUser(string email, UserType type)
{
	return User(email, type);
}

User User::CreateUser(int userId, string email, UserType type)
{
	return User(userId, email, type);
}
//
//void User::ChangeEmailV0(int userId, string newEmail)
//{
//	auto data = _database->GetUserById(userId);
//	string email = std::get<0>(data);
//	UserType type = (UserType)(std::get<1>(data));
//
//	User user = User(userId, email, type);
//
//	auto companyData = _database->GetCompany();
//	string companyDomainName = std::get<0>(companyData);
//	int numberOfEmployees = std::get<1>(companyData);
//
//	string emailDomain = Split(newEmail, "@")[1];
//	bool isEmailCorporate = emailDomain == companyDomainName;
//	UserType newType = isEmailCorporate ? UserType::Employee : UserType::Customer;
//
//	if (newType != _type) {
//		int delta = newType == UserType::Employee ? 1 : -1;
//		int newNumber = numberOfEmployees + delta;
//		numberOfEmployees = newNumber;
//	}
//
//	_email = newEmail;
//	_type = newType;
//
//	_database->SaveCompany(numberOfEmployees);
//	_database->SaveUser(user);
//	_messageBus->SendEmailChangedMessage(userId, newEmail);
//}

int User::ChangeEmailV1(string newEmail, string companyDomainName, int numberOfEmployees)
{
	if (newEmail == _email) {
		return numberOfEmployees;
	}

	string emailDomain = Split(newEmail, "@")[1];
	bool isEmailCorporate = emailDomain == companyDomainName;
	UserType newType = isEmailCorporate ? UserType::Employee : UserType::Customer;

	if (newType != _type) {
		int delta = newType == UserType::Employee ? 1 : -1;
		int newNumber = numberOfEmployees + delta;
		numberOfEmployees = newNumber;
	}

	_email = newEmail;
	_type = newType;

	return numberOfEmployees;
}

bool User::ChangeEmailV2(string newEmail, Company& company)
{
	if (newEmail == _email) {
		return false;
	}

	UserType newType = company.IsEmailCorporate(newEmail) ? UserType::Employee : UserType::Customer;

	if (newType != _type) {
		int delta = newType == UserType::Employee ? 1 : -1;
		company.ChangeNumberOfEmployees(delta);
	}

	_email = newEmail;
	_type = newType;

	return true;
}

bool User::ChangeEmailV3(string newEmail, Company& company, IMessageBus* messageBus)
{
	if (newEmail == _email) {
		return false;
	}

	UserType newType = company.IsEmailCorporate(newEmail) ? UserType::Employee : UserType::Customer;

	if (newType != _type) {
		int delta = newType == UserType::Employee ? 1 : -1;
		company.ChangeNumberOfEmployees(delta);
		AddDomainEvent(new UpdateUserTypeEvent(_userId, _type, newType));
	}

	_email = newEmail;
	_type = newType;

	// AddDomainEvent(new UpdateUserEmailEvent(messageBus, _userId, _email));

	return true;
}

void User::ChangeEmailIfValid(int userId, string newEmail)
{
	if (newEmail == _email) {
		throw UserEmailAddressIsSame(newEmail);
	}

	// 나머지 코드 부분
}

void User::ChangeEmailV4(string newEmail, Company& company, IMessageBus* messageBus)
{
	if (newEmail == _email) {
		throw UserEmailAddressIsSame(newEmail);
	}

	UserType newType = company.IsEmailCorporate(newEmail) ? UserType::Employee : UserType::Customer;

	if (newType != _type) {
		int delta = newType == UserType::Employee ? 1 : -1;
		company.ChangeNumberOfEmployees(delta);
		AddDomainEvent(new UpdateUserTypeEvent(_userId, _type, newType));
	}

	_email = newEmail;
	_type = newType;

	AddDomainEvent(new UpdateUserEmailEvent(messageBus, _userId, _email));
}

void User::AddDomainEvent(DomainEvent* domainEvent)
{
	_domainEvents.push_back(domainEvent);
}

UserEmailAddressIsSame::UserEmailAddressIsSame(std::string emailAddress)
	:
	message(Format("UserEmailAddress is Same : %s", emailAddress.c_str()))
{
}
