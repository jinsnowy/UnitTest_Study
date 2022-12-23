#pragma once

#include <string>

enum class UserType {
	Employee,
	Customer
};

class UserEmailAddressIsSame : public std::exception {
private:
	std::string message;
public:
	UserEmailAddressIsSame(std::string emailAddress);
	virtual const char* what() const override { return message.c_str(); }
};

class IMessageBus;
class DomainEvent;
class Company;
class User
{
public:
	int _userId;
	string _email;
	UserType _type;

	vector<DomainEvent*> _domainEvents;

public:
	User(string email, UserType type);

	User(int userId, string email, UserType type);

	static User CreateUser(string email, UserType type);

	static User CreateUser(int userId, string email, UserType type);

	bool isEmailEquals(string email);

	void ChangeEmailV0(int userId, string newEmail) {}

	int ChangeEmailV1(string newEmail, string companyDomainName, int numberOfEmployees);

	bool ChangeEmailV2(string newEmail, Company& company);

	bool ChangeEmailV3(string newEmail, Company& company);

	void ChangeEmailIfValid(int userId, string newEmail);

	void ChangeEmailV4(string newEmail, Company& company, IMessageBus* messageBus);

	void AddDomainEvent(DomainEvent* domainEvent);
};