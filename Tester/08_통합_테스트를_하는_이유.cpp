#include "pch.h"

#include "07_단위_테스트_리팩토링\User.h"
#include "07_단위_테스트_리팩토링\Company.h"
#include "07_단위_테스트_리팩토링\UserController.h"
#include "07_단위_테스트_리팩토링\Application.h"
#include "07_단위_테스트_리팩토링\EventDispatcher.h"

#include "MockLogger.h"
#include "MockMessageBus.h"
#include "CorePch.h"

TEST(TestUserController, 통합_테스트_이메일_변경_사내도메인에서_외부도메인으로) {
	// given
	auto db = new Database(string("connection"));
	auto insertUser = User::CreateUser("user@mycorp.com", UserType::Employee);
	auto insertCompany = Company::CreateCompany("mycorp.com", 1);

	db->SaveUser(insertUser);
	db->SaveCompany(insertCompany);

	auto messageBusMock = new MockMessageBus();
	auto sut = UserController(db, messageBusMock);

	EXPECT_CALL(*messageBusMock, SendEmailChangedMessage(insertUser._userId, "new@gmail.com")).Times(1);

	// when
	sut.ChangeEmailV4(insertUser._userId, "new@gmail.com");

	// then
	auto userData = db->GetUserById(insertUser._userId);
	User userFromDB = User::CreateUser(insertUser._userId, std::get<0>(userData), (UserType)std::get<1>(userData));
	ASSERT_EQ("new@gmail.com", userFromDB._email);
	ASSERT_EQ(UserType::Customer, userFromDB._type);

	auto companyData = db->GetCompany();
	Company companyFromDB = Company::CreateCompany(std::get<0>(companyData), std::get<1>(companyData));
	ASSERT_EQ(0, companyFromDB._numberOfEmployees);
}

class BusSpy : public IBus {
private:
	vector<string> _sentMessages;

public:
	void Send(string message) {
		_sentMessages.push_back(message);
	}

	BusSpy& ShouldSendNumberOfMessages(int number) {
		int msgCount = (int)_sentMessages.size();
		// ASSERT_EQ(msgCount, number)
		return *this;
	}

	BusSpy& WithEmailSendMessage(int userId, string newEmail) {
		// ASSERT_EQ("~", ); 메시지 검증
		return *this;
	}
};
