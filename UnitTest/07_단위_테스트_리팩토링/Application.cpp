#include "pch.h"
#include "Application.h"

#include "User.h"
#include "Company.h"

static int userIdGen = 0;

void Database::SaveUser(User& user)
{
	if (userData.find(user._userId) == userData.end()) {
		user._userId = ++userIdGen;
	}

	userData[user._userId] = make_tuple(user._email, (int)user._type);
}

void Database::SaveCompany(Company& company)
{
	companyData = make_tuple(company._domainName, company._numberOfEmployees);
}

void Database::SaveCompany(int)
{
}

void Logger::Log(string msg)
{
	std::cout << msg << endl;
}

void MessageBus::SendEmailChangedMessage(int userId, std::string emailAddress)
{
	_bus->Send(Format("user id %d changed email address to %s", userId, emailAddress.c_str()));
}
