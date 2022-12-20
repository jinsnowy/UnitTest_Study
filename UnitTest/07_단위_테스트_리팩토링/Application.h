#pragma once

using DataType = tuple<string, int>;

class User;
class Company;
class IDatabase {
public:
	IDatabase() {}
	IDatabase(string) {}

	virtual DataType GetUserById(int userId) { return {}; }
	virtual DataType GetCompany() { return {}; }

	virtual void SaveUser(User&) {};
	virtual void SaveCompany(Company&) {}
	virtual void SaveCompany(int) {}
};

class NullDatabase : public IDatabase {
public:
	NullDatabase() {}
	NullDatabase(string) {}

	virtual DataType GetUserById(int userId) override { return {}; }
	virtual DataType GetCompany() override { return {}; }

	virtual void SaveUser(User&) override {};
	virtual void SaveCompany(Company&) override {}
	virtual void SaveCompany(int) override {}
};

class MemoryDatabase : public IDatabase {
private:
	map<int, DataType> userData;
	DataType companyData;

public:
	MemoryDatabase() {}
	MemoryDatabase(string connString) : IDatabase(connString) {}

	virtual DataType GetUserById(int userId) override { return userData[userId]; }
	virtual DataType GetCompany() override { return companyData; }

	virtual void SaveUser(User& user) override;
	virtual void SaveCompany(Company& company) override;
};

template<typename T>
class Singleton {
public:
	static T* GetInstance() {
		static T inst;
		return &inst;
	}
};

class IMessageBus {
public:
	virtual void SendEmailChangedMessage(int, std::string) abstract;
};

class ILogger {
public:
	virtual void Log(string msg) abstract;
};

class MessageBus : public IMessageBus {
public:
	virtual void SendEmailChangedMessage(int, std::string) override {}
};

class Logger : public ILogger, public Singleton<Logger> {
public:
	virtual void Log(string msg) override;
};
