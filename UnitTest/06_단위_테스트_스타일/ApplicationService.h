#pragma once

#include "AuditManager2.h"
#include "Persister.h"

class ApplicationService
{
private:
	string _dirName;
	AuditManager2 _auditManager;
	Persister _persister;

public:
	ApplicationService(string dirName, int maxEntriesPerFile);

	void AddRecord(string visitorName, string tiemOfVisit);
};

