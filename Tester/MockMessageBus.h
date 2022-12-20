#pragma once

#include "07_단위_테스트_리팩토링\Application.h"

class MockMessageBus : public MessageBus
{
public:
	MOCK_METHOD(void, SendEmailChangedMessage, (int, string), (override));
};

