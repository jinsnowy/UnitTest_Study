#include "pch.h"
#include "Repository.h"

#include "User.h"
#include "Company.h"

static int userIdGen = 0;

Repository::Repository(Transaction* transaction)
	:
	_transaction(transaction)
{
}

CompanyRepository::CompanyRepository(Transaction* transaction)
	:
	Repository(transaction)
{
}

void CompanyRepository::SaveCompany(Company& company)
{
	companyData = make_tuple(company._domainName, company._numberOfEmployees);
}

UserRepository::UserRepository(Transaction* transaction)
	:
	Repository(transaction)
{
}

void UserRepository::SaveUser(User& user)
{
	if (userData.find(user._userId) == userData.end()) {
		user._userId = ++userIdGen;
	}

	userData[user._userId] = make_tuple(user._email, (int)user._type);
}
