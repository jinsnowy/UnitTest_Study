#pragma once

class Company
{
public:
	string _domainName;
	int _numberOfEmployees;

public:
	Company(string domainName, int numberOfEmployees);

	static Company CreateCompany(string domainName, int numberOfEmployees);

	void ChangeNumberOfEmployees(int delta);

	bool IsEmailCorporate(string email);
};

