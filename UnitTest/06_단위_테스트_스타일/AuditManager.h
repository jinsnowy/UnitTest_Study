#pragma once

class IFileSystem;
class AuditManager
{
private:
	IFileSystem& _fileSystem;

	int _maxEntriesPerFile;
	string _directoryName;

public:
	AuditManager(IFileSystem& fileSystem, int maxEntriesPerFile, string directoryName);

	void AddRecord(string visitorName, string timeOfVisit);

private:
	vector<string> ReadLines(string filePath);

	string GetFilePath(string fileName);

	void WriteToFile(string filePath, string record);
};