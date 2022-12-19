#pragma once
#include "IFileSystem.h"

class FileSystem : public IFileSystem
{
public:
	virtual vector<string> GetFiles(string dirPath) override;

	virtual vector<string> ReadLines(string filePath) override;

	virtual void WriteLine(string filePath, string content) override;
};

