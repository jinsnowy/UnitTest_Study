#include "pch.h"
#include "FileSystem.h"

vector<string> FileSystem::GetFiles(string dirPath)
{
	vector<string> filePaths;
	for (const auto& entry : fs::directory_iterator(dirPath)) {
		filePaths.emplace_back(entry.path().string());
	}

	return filePaths;
}

vector<string> FileSystem::ReadLines(string filePath)
{
	ifstream lastFile(filePath);
	if (lastFile.is_open() == false) {
		return vector<string>{};
	}

	vector<string> lines;
	std::string line;
	while (std::getline(lastFile, line)) {
		lines.push_back(std::move(line));
	}

	lastFile.close();

	return lines;
}

void FileSystem::WriteLine(string filePath, string content)
{
	ofstream file(filePath);
	file << content << endl;
	file.close();
}
