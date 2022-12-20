#include "pch.h"
#include "Company.h"

Company::Company(string domainName, int numberOfEmployees)
	:
	_domainName(domainName),
	_numberOfEmployees(numberOfEmployees)
{
}

Company Company::CreateCompany(string domainName, int numberOfEmployees)
{
	return Company(domainName, numberOfEmployees);
}

void Company::ChangeNumberOfEmployees(int delta)
{
	_numberOfEmployees += delta;
}

bool Company::IsEmailCorporate(string email)
{
	string emailDomain = Split(email, "@")[1];
	return emailDomain == _domainName;
}