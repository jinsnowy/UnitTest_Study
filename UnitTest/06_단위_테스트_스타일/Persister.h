#pragma once

#include "FileStruct.h"

class Persister
{
public:
	vector<FileContent> ReadDirectory(string directoryName);

	void ApplyUpdate(string directoryName, FileUpdate update);
};

