#include "pch.h"

#include "07_단위_테스트_리팩토링\User.h"
#include "07_단위_테스트_리팩토링\Company.h"
#include "07_단위_테스트_리팩토링\UserController.h"
#include "07_단위_테스트_리팩토링\Application.h"
#include "07_단위_테스트_리팩토링\EventDispatcher.h"
#include "07_단위_테스트_리팩토링\Transaction.h"
#include "07_단위_테스트_리팩토링\Repository.h"

#include "MockLogger.h"
#include "MockMessageBus.h"

#include "CorePch.h"

TEST(TestUserControllerWithDatabase, 통합_테스트_이메일_변경_사내도메인에서_외부도메인으로) {
	// given
	auto db = new Database(string("connection"));
	auto conn = db->GetConnection();
	auto transaction = conn->CreateTransaction();

	auto messageBusMock = new MockMessageBus();
	auto eventDispacther = new EventDispatcher();
	auto sut = new UserController(transaction, messageBusMock, eventDispacther);

	auto insertUser = User::CreateUser("user@mycorp.com", UserType::Employee);
	auto insertCompany = Company::CreateCompany("mycorp.com", 1);

	auto userRepository = sut->GetUserRepository();
	auto companyRepository = sut->GetCompanyRepository();

	// create test data
	{
		auto trGuard = transaction->Start();
		userRepository->SaveUser(insertUser);
		companyRepository->SaveCompany(insertCompany);
		trGuard.Commit();
	}

	EXPECT_CALL(*messageBusMock, SendEmailChangedMessage(insertUser._userId, "new@gmail.com")).Times(1);

	// when
	sut->ChangeEmailV5(insertUser._userId, "new@gmail.com");

	// then
	auto userData = userRepository->GetUserById(insertUser._userId);
	User userFromDB = User::CreateUser(insertUser._userId, std::get<0>(userData), (UserType)std::get<1>(userData));
	ASSERT_EQ("new@gmail.com", userFromDB._email);
	ASSERT_EQ(UserType::Customer, userFromDB._type);

	auto companyData = companyRepository->GetCompany();
	Company companyFromDB = Company::CreateCompany(std::get<0>(companyData), std::get<1>(companyData));
	ASSERT_EQ(0, companyFromDB._numberOfEmployees);
}

class UserControllerIntegrateTest : public ::testing::Test
{
protected:
	Database* db;
	DBConnection* conn;
	Transaction* transaction;

	MockMessageBus* messageBusMock;
	EventDispatcher* eventDispacther;

	UserController* sut;

public:
	UserControllerIntegrateTest()
		:
		::testing::Test() {
		db = new Database(string("connection"));
		conn = db->GetConnection();
		transaction = conn->CreateTransaction();
		messageBusMock = new MockMessageBus();
		eventDispacther = new EventDispatcher();
		sut = new UserController(transaction, messageBusMock, eventDispacther);
	}

	virtual void SetUp() override {
		ClearDatabase();
	}

	virtual void TearDown() override {
		conn->Close();
	}

	void CreateUser(User& user) {
		sut->GetUserRepository()->SaveUser(user);
		transaction->Commit();
	}

	void CreateCompany(Company& company) {
		sut->GetCompanyRepository()->SaveCompany(company);
		transaction->Commit();
	}

	User SelectUser(int userId) {
		auto userData = sut->GetUserRepository()->GetUserById(userId);
		return User::CreateUser(userId, std::get<0>(userData), (UserType)std::get<1>(userData));
	}

	Company SelectCompany() {
		auto companyData = sut->GetCompanyRepository()->GetCompany();
		return Company::CreateCompany(std::get<0>(companyData), std::get<1>(companyData));
	}

	template<typename R, typename ...FArgs, typename ...Args>
	R Execute(R(UserController::* memFunc)(FArgs...), Args&&... args) {
		return std::invoke(memFunc, sut, std::forward<Args>(args)...);
	}

private:
	void ClearDatabase() {
		string query = "DELETE FROM dbo.[User];"\
					  "DELETE FROM dbo.Company;";

		conn->ExecuteNonQuery(query);
	}
};

TEST_F(UserControllerIntegrateTest, 통합_테스트_이메일_변경_사내도메인에서_외부도메인으로) {
	// given
	auto insertUser = User::CreateUser("user@mycorp.com", UserType::Employee);
	auto insertCompany = Company::CreateCompany("mycorp.com", 1);

	// create test data
	CreateUser(insertUser);
	CreateCompany(insertCompany);

	EXPECT_CALL(*messageBusMock, SendEmailChangedMessage(insertUser._userId, "new@gmail.com")).Times(1);

	// when
	Execute(&UserController::ChangeEmailV5, insertUser._userId, "new@gmail.com");

	// then
	User userFromDB = SelectUser(insertUser._userId);
	ASSERT_EQ("new@gmail.com", userFromDB._email);
	ASSERT_EQ(UserType::Customer, userFromDB._type);

	Company companyFromDB = SelectCompany();
	ASSERT_EQ(0, companyFromDB._numberOfEmployees);
}