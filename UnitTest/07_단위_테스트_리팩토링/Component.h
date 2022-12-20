#pragma once
#include <string>
#include <tuple>

class User;
class Company;
class Database {
public:
	std::tuple<std::string, int> GetUserId(int userId) { return {}; }
	std::tuple<std::string, int> GetCompany() { return {}; }

	void SaveUser(User&) {};
	void SaveCompany(Company&) {}
	void SaveCompany(int) {}
};

class MessageBus {
public:
	void SendEmailChangedMessage(int, std::string) {}
};