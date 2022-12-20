#pragma once

using DataType = tuple<string, int>;

class User;
class Company;
class Database {
public:
	Database() {}
	Database(string) {}

	virtual DataType GetUser(int userId) { return {}; }
	virtual DataType GetCompany() { return {}; }

	virtual void SaveUser(User&) {};
	virtual void SaveCompany(Company&) {}
	virtual void SaveCompany(int) {}
};

class MemoryDatabase : public Database {

private:
	map<int, DataType> userData;
	DataType companyData;

public:
	MemoryDatabase() {}
	MemoryDatabase(string connString) : Database(connString) {}

	virtual DataType GetUser(int userId) override { return userData[userId]; }
	virtual DataType GetCompany() override { return companyData; }

	virtual void SaveUser(User& user) override;
	virtual void SaveCompany(Company& company) override;
};


class MessageBus {
public:
	virtual void SendEmailChangedMessage(int, std::string) {}
};