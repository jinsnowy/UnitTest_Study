#pragma once

#include "07_����_�׽�Ʈ_�����丵\Application.h"

class MockMessageBus : public MessageBus
{
public:
	MOCK_METHOD(void, SendEmailChangedMessage, (int, string), (override));
};

