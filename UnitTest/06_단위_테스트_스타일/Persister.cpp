#include "pch.h"
#include "Persister.h"
#include "FileSystem.h"

static string GetFileNameFromPath(string path) {
	size_t pos = path.rfind("/");
	if (pos != string::npos) {
		path = path.substr(pos + 1);
	}

	return path;
}

vector<FileContent> Persister::ReadDirectory(string directoryName)
{
	vector<FileContent> fileContents;

	FileSystem fs;
	vector<string> files = fs.GetFiles(directoryName);
	for (const auto& file : files) {
		string fileName = GetFileNameFromPath(file);
		vector<string> lines = fs.ReadLines(fileName);

		fileContents.emplace_back(fileName, lines);
	}

	return fileContents;
}

void Persister::ApplyUpdate(string directoryName, FileUpdate update)
{
	FileSystem fs;
	string filePath = format("{}/{}", directoryName.c_str(), update.fileName.c_str());
	fs.WriteLine(filePath, update.newContent);
}
