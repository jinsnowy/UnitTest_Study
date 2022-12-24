#pragma once

using DataType = tuple<string, int>;

class User;
class Company;

class Transaction;
class Repository
{
private:
	Transaction* _transaction;

public:
	Repository(Transaction* transaction);
};

class UserRepository : public Repository
{
private:
	map<int, DataType> userData;

public:
	UserRepository(Transaction* transaction);

	void SaveUser(User& user);

	DataType GetUserById(int userId) { return userData[userId]; }
};

class CompanyRepository : public Repository
{
private:
	DataType companyData;

public:
	CompanyRepository(Transaction* transaction);

	void SaveCompany(Company& company);

	DataType GetCompany() { return companyData; }
};