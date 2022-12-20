#include "pch.h"

#include "07_����_�׽�Ʈ_�����丵\User.h"
#include "07_����_�׽�Ʈ_�����丵\Company.h"
#include "07_����_�׽�Ʈ_�����丵\UserController.h"
#include "07_����_�׽�Ʈ_�����丵\Application.h"

#include "MockMessageBus.h"

TEST(TestUserController, ����_�׽�Ʈ_�̸���_����_�系�����ο���_�ܺε���������) {
	// given
	auto db = new MemoryDatabase(string("connection"));
	auto insertUser = User::CreateUser("user@mycorp.com", UserType::Employee);
	auto insertCompany = Company::CreateCompany("mycorp.com", 1);

	db->SaveUser(insertUser);
	db->SaveCompany(insertCompany);

	auto messageBusMock = new MockMessageBus();
	auto sut = UserController(db, messageBusMock);

	EXPECT_CALL(*messageBusMock, SendEmailChangedMessage(insertUser._userId, "new@gmail.com")).Times(1);

	// when
	bool isSuccess = sut.ChangeEmailV3(insertUser._userId, "new@gmail.com");

	// then
	ASSERT_TRUE(isSuccess);

	auto userData = db->GetUserById(insertUser._userId);
	User userFromDB = User::CreateUser(insertUser._userId, std::get<0>(userData), (UserType)std::get<1>(userData));
	ASSERT_EQ("new@gmail.com", userFromDB._email);
	ASSERT_EQ(UserType::Customer, userFromDB._type);

	auto companyData = db->GetCompany();
	Company companyFromDB = Company::CreateCompany(std::get<0>(companyData), std::get<1>(companyData));
	ASSERT_EQ(0, companyFromDB._numberOfEmployees);
}