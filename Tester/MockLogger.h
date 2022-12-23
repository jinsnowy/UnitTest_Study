#pragma once
#include "07_단위_테스트_리팩토링\Application.h"

class MockLogger : public ILogger
{
public:
	MOCK_METHOD(void, Log, (string), (override));
};

