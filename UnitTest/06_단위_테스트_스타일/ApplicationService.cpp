#include "pch.h"
#include "ApplicationService.h"

ApplicationService::ApplicationService(string dirName, int maxEntriesPerFile)
	:
	_dirName(dirName),
	_auditManager(maxEntriesPerFile),
	_persister{}
{
}

void ApplicationService::AddRecord(string visitorName, string timeOfVisit)
{
	vector<FileContent> fileContents = _persister.ReadDirectory(_dirName);
	FileUpdate update = _auditManager.AddRecord(fileContents, visitorName, timeOfVisit);
	_persister.ApplyUpdate(_dirName, update);
}