#pragma once
#include "07_����_�׽�Ʈ_�����丵\Application.h"

class MockLogger : public ILogger
{
public:
	MOCK_METHOD(void, Log, (string), (override));
};

