#pragma once

#include "06_����_�׽�Ʈ_��Ÿ��\IFileSystem.h"

class MockFileSystem : public IFileSystem
{
public:
	MOCK_METHOD(vector<string>, GetFiles, (string), (override));

	MOCK_METHOD(vector<string>, ReadLines, (string), (override));

	MOCK_METHOD(void, WriteLine, (string, string), (override));
};

