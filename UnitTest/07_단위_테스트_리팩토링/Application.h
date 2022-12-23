#pragma once

using DataType = tuple<string, int>;

class User;
class Company;

class Database {
private:
	map<int, DataType> userData;
	DataType companyData;

public:
	Database() {}
	Database(string connString)  {}

	DataType GetUserById(int userId) { return userData[userId]; }
	DataType GetCompany() { return companyData; }

	void SaveUser(User& user);
	void SaveCompany(Company& company);
	void SaveCompany(int);
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
