#pragma once

#include <string>

enum class UserType {
	Employee,
	Customer
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

	int ChangeEmailV1(string newEmail, string companyDomainName, int numberOfEmployees);

	bool ChangeEmailV2(string newEmail, Company& company);

	bool ChangeEmailV3(string newEmail, Company& company);

	void AddDomainEvent(DomainEvent* domainEvent);
};