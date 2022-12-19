#include "pch.h"
#include "AuditManager2.h"

AuditManager2::AuditManager2(int maxEntriesPerFile)
	:
	_maxEntriesPerFile(maxEntriesPerFile)
{
}

FileUpdate AuditManager2::AddRecord(vector<FileContent> files, string visitorName, string timeOfVisit)
{

	string newRecord = format("{};{}", visitorName.c_str(), timeOfVisit.c_str());

	if (files.empty()) {
		return FileUpdate{"audit_1.txt", newRecord};
	}

	sort(files.begin(), files.end());

	auto& lastFileContent = files.back();
	if (lastFileContent.lines.size() < _maxEntriesPerFile) {
		return FileUpdate{ lastFileContent.fileName, newRecord };
	}
	else {
		int nextIndex = (int)files.size() + 1;
		string fileName = format("audit_{}.txt", nextIndex);
		return FileUpdate{ fileName, newRecord };
	}
}
