#include "pch.h"
#include "Application.h"

#include "User.h"
#include "Company.h"

static int userIdGen = 0;

void MemoryDatabase::SaveUser(User& user)
{
	if (userData.find(user._userId) == userData.end()) {
		user._userId = ++userIdGen;
	}

	userData[user._userId] = make_tuple(user._email, (int)user._type);
}

void MemoryDatabase::SaveCompany(Company& company)
{
	companyData = make_tuple(company._domainName, company._numberOfEmployees);
}

string Format(const char* fmt, ...)
{
	char buff[1024];
	memset(buff, 0, sizeof(buff));
	va_list args;
	va_start(args, fmt);
	vsnprintf_s(buff, _countof(buff), _TRUNCATE, fmt, args);
	va_end(args);

	return string(buff);
}

void Logger::Log(string msg)
{
	std::cout << msg << endl;
}
