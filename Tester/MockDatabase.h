#pragma once

#include "04_���_�׽�Ʈ_��༺\Database.h"

class MockDatabase : public Database
{
public:
	MOCK_METHOD(int, GetNumberOfUsers, (), (override));
};
