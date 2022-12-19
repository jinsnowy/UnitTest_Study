#pragma once

#include "04_목과_테스트_취약성\Database.h"

class MockDatabase : public Database
{
public:
	MOCK_METHOD(int, GetNumberOfUsers, (), (override));
};
