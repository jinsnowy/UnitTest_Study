#pragma once

using DataType = tuple<string, int>;

class User;
class Company;

class Transaction;
class DBConnection{
private:
	string connString;

public:
	DBConnection(string _connString);

	Transaction* CreateTransaction();

	void ExecuteNonQuery(string) {}

	void Close() {}
	void Commit() {}
	void Rollback() {}
};

class Database {
private:
	map<int, DataType> userData;
	DataType companyData;

public:
	Database() {}
	Database(string connString);

	DataType GetUserById(int userId) { return userData[userId]; }
	DataType GetCompany() { return companyData; }

	void SaveUser(User& user);
	void SaveCompany(Company& company);
	void SaveCompany(int);

private:
	DBConnection* _conn;

public:
	DBConnection* GetConnection();
};

template<typename T>
class Singleton {
public:
	static T* GetInstance() {
		static T inst;
		return &inst;
	}
};

class IBus {
public:
	virtual void Send(string message) abstract;
};

class IMessageBus {
protected:
	IBus* _bus;

public:
	virtual void SendEmailChangedMessage(int, std::string) abstract;
};

class ILogger {
public:
	virtual void Log(string msg) abstract;
};

class MessageBus : public IMessageBus {
public:
	virtual void SendEmailChangedMessage(int userId, std::string emailAddress);
};

class Logger : public ILogger, public Singleton<Logger> {
public:
	virtual void Log(string msg) override;
};
