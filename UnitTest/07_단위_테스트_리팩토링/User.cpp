#include "pch.h"
#include "User.h"
#include "Company.h"

User::User(int userId, std::string email, UserType type)
	:
	_userId(userId), _email(email), _type(type)
{}

bool User::isEmailEquals(string email)
{
	return _email == email;
}

User User::CreateUser(int userId, string email, UserType type)
{
	return User(userId, email, type);
}

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