#include "pch.h"
#include "02_단위_테스트란\Customer.h"
#include "02_단위_테스트란\Store.h"
#include "MockEmailGateway.h"
#include "MockStore.h"
#include "MockDatabase.h"

class EmailController {
private:
	EmailGateway& _gateway;
public:
	EmailController(EmailGateway& gateway) : _gateway(gateway) {}

	void GreetUser(string emailAddress) {
		_gateway.SendGreetingEmail(emailAddress);
	}
};

TEST(TestEmailGateway, SendGreetingEmail) {
	// given
	MockEmailGateway mock = {};
	EmailController sut(mock);

	EXPECT_CALL(mock, SendGreetingEmail(_)).Times(1);

	// when
	sut.GreetUser("user@email.com");

	// then
}

class DatabaseController {
private:
	Database& _db;
public:
	DatabaseController(Database& db) : _db(db) {}

	int CreateReport() {
		return _db.GetNumberOfUsers();
	}
};

TEST(TestDatabase, CreateReportResultIsCorrect) {
	// given
	MockDatabase mock = {};
	DatabaseController sut(mock);

	ON_CALL(mock, GetNumberOfUsers()).WillByDefault(Return(10));

	// when
	int report = sut.CreateReport();

	// then
	EXPECT_EQ(report, 10);
}

class CustomerRepository {
public:
	Customer GetById(int id) {
		return Customer();
	}
};

class ProductRepository {
public:
	Product GetById(int id) {
		return (Product)(id);
	}
};

class CustomerController {
private:
	CustomerRepository _customerRepository;
	ProductRepository _productRepository;

	Store& _mainStore;
	EmailGateway& _emailGateway;
public:
	CustomerController(Store& store, EmailGateway& emailGateway) 
		: _mainStore(store), _emailGateway(emailGateway) {}

	bool Purchase(int customerId, int productId, int quantity) {
		Customer customer = _customerRepository.GetById(customerId);
		Product product = _productRepository.GetById(productId);

		bool isSuccess = customer.Purchase(_mainStore, product, quantity);
		if (isSuccess) {
			_emailGateway.SendReceipt(customer.emailAddress, GetProductName(product), quantity);
		}

		return isSuccess;
	}
};

TEST(TestCusotmerController, 충분한_인벤_구매_성공_그리고_영수증_발행) {
	// given
	Store store = {};
	store.AddInventory(Product::Shampoo, 5);

	MockEmailGateway gateway = {};
	CustomerController sut(store, gateway);
	
	EXPECT_CALL(gateway, SendReceipt("customer@email.com", "Shampoo", 5)).Times(1);

	// when
	bool isSuccess = sut.Purchase(1, (int)Product::Shampoo, 5);

	// then
	ASSERT_TRUE(isSuccess);
}
