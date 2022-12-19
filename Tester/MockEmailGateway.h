#pragma once

#include "04_목과_테스트_취약성\EmailGateway.h"

class MockEmailGateway : public EmailGateway
{
public:
	MOCK_METHOD(void, SendGreetingEmail, (string), (override));

	MOCK_METHOD(void, SendReceipt, (string, string, int), (override));
};
