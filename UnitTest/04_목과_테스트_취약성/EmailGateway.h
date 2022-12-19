#pragma once
class EmailGateway
{
public:
	virtual void SendGreetingEmail(string emailAddress);

	virtual void SendReceipt(string emailAddress, string name, int quantity);
};

