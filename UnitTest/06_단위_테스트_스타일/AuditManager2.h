#pragma once

#include "FileStruct.h"

class AuditManager2
{
private:
	int _maxEntriesPerFile;

public:
	AuditManager2(int maxEntriesPerFile);

	FileUpdate AddRecord(vector<FileContent> files, string visitorName, string timeOfVisit);
};

