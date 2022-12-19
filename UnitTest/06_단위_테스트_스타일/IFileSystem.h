#pragma once

class IFileSystem
{
public:
	virtual vector<string> GetFiles(string dirPath) abstract;

	virtual vector<string> ReadLines(string filePath) abstract;

	virtual void WriteLine(string filePath, string content) abstract;
};