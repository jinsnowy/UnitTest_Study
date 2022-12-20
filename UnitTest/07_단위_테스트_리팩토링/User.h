#pragma once

#include <string>

enum class UserType {
	Employee,
	Customer
};

class Company;
class User
{
public:
	int _userId;
	string _email;
	UserType _type;

public:
	User(string email, UserType type);

	User(int userId, string email, UserType type);

	bool isEmailEquals(string email);

	static User CreateUser(string email, UserType type);

	static User CreateUser(int userId, string email, UserType type);

	int ChangeEmailV1(string newEmail, string companyDomainName, int numberOfEmployees);

	bool ChangeEmailV2(string newEmail, Company& company);
};