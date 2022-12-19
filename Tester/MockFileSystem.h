#pragma once

#include "06_단위_테스트_스타일\IFileSystem.h"

class MockFileSystem : public IFileSystem
{
public:
	MOCK_METHOD(vector<string>, GetFiles, (string), (override));

	MOCK_METHOD(vector<string>, ReadLines, (string), (override));

	MOCK_METHOD(void, WriteLine, (string, string), (override));
};

