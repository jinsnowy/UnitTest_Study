#pragma once

#include "04_���_�׽�Ʈ_��༺\EmailGateway.h"

class MockEmailGateway : public EmailGateway
{
public:
	MOCK_METHOD(void, SendGreetingEmail, (string), (override));

	MOCK_METHOD(void, SendReceipt, (string, string, int), (override));
};
