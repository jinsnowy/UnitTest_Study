#include "pch.h"

#include "07_����_�׽�Ʈ_�����丵\User.h"
#include "07_����_�׽�Ʈ_�����丵\Company.h"
#include "07_����_�׽�Ʈ_�����丵\UserController.h"

TEST(TestUserController, �̸���_����_�ܺε�����_����_�系����������) {
	auto company = Company("mycorp.com", 1);
	auto sut = User(1, "user@gmail.com", UserType::Customer);

	bool isSuccess = sut.ChangeEmailV2("new@mycorp.com", company);

	ASSERT_TRUE(isSuccess);
	ASSERT_EQ(2, company._numberOfEmployees);
	ASSERT_EQ("new@mycorp.com", sut._email);
	ASSERT_EQ(UserType::Employee, sut._type);
}

TEST(TestUserController, �̸���_����_�系������_����_�ܺε���������) {
	auto company = Company("mycorp.com", 2);
	auto sut = User(1, "user@mycorp.com", UserType::Employee);

	bool isSuccess = sut.ChangeEmailV2("new@gmail.com", company);

	ASSERT_TRUE(isSuccess);
	ASSERT_EQ(1, company._numberOfEmployees);
	ASSERT_EQ("new@gmail.com", sut._email);
	ASSERT_EQ(UserType::Customer, sut._type);
}

TEST(TestUserController, �̸���_����_�系������_����_�系����������) {
	auto company = Company("mycorp.com", 1);
	auto sut = User(1, "peter@mycorp.com", UserType::Employee);
		
	bool isSucess = sut.ChangeEmailV2("lance@mycorp.com", company);

	ASSERT_TRUE(isSucess);
	ASSERT_EQ(1, company._numberOfEmployees);
	ASSERT_EQ("lance@mycorp.com", sut._email);
	ASSERT_EQ(UserType::Employee, sut._type);
}

TEST(TestUserController, �̸���_����_����_����_����_��������) {
	auto company = Company("mycorp.com", 1);
	auto sut = User(1, "peter@gmail.com", UserType::Customer);

	bool isSuccess = sut.ChangeEmailV2("peter@gmail.com", company);

	ASSERT_FALSE(isSuccess);
	ASSERT_EQ(1, company._numberOfEmployees);
	ASSERT_EQ("peter@gmail.com", sut._email);
	ASSERT_EQ(UserType::Customer, sut._type);
}