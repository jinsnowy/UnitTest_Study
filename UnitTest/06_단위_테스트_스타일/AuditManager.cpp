#include "pch.h"
#include "AuditManager.h"
#include "IFileSystem.h"

AuditManager::AuditManager(IFileSystem& fileSystem, int maxEntriesPerFile, string directoryName) 
	:
	_fileSystem(fileSystem),
	_maxEntriesPerFile(maxEntriesPerFile),
	_directoryName(directoryName)
{
}

void AuditManager::AddRecord(string visitorName, string timeOfVisit) {
	vector<string> filePaths = _fileSystem.GetFiles(_directoryName);
	sort(filePaths.begin(), filePaths.end());

	string newRecord = format("{};{}", visitorName.c_str(), timeOfVisit.c_str());

	if (filePaths.size() == 0) {
		string newFilePath = GetFilePath("audit_1.txt");
		WriteToFile(newFilePath, newRecord);
		return;
	}

	string lastFilePath = filePaths.back();

	vector<string> lines = ReadLines(lastFilePath);

	if (lines.size() < _maxEntriesPerFile) {
		WriteToFile(lastFilePath, newRecord);
	}
	else {
		int newIndex = (int)filePaths.size() + 1;
		string newFileName = format("audit_{}.txt", newIndex);
		string newFilePath = GetFilePath(newFileName);
		WriteToFile(newFilePath, newRecord);
	}
}

vector<string> AuditManager::ReadLines(string filePath) {
	return _fileSystem.ReadLines(filePath);
}

string AuditManager::GetFilePath(string fileName) {
	return format("{}/{}", _directoryName.c_str(), fileName.c_str());
}

void AuditManager::WriteToFile(string filePath, string record) {
	return _fileSystem.WriteLine(filePath, record);
}
