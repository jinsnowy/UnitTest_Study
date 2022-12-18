#include "pch.h"
#include "02_����_�׽�Ʈ��/Customer.h"
#include "02_����_�׽�Ʈ��/Store.h"

class CustomerTests : public ::testing::Test
{
protected:
	//Store _store;
	//Customer _sut;

public:
	virtual void SetUp() override {
		//_store.AddInventory(Product::Shampoo, 10);
	}

	virtual void TearDown() override {
	}
};

//TEST_F(CustomerTests, �����ִ�_�κ�_����_����) {
//	bool success = _sut.Purchase(_store, Product::Shampoo, 5);
//	ASSERT_TRUE(success);
//	ASSERT_EQ(5, _store.GetInventory(Product::Shampoo));
//}
//
//TEST_F(CustomerTests, �����_�κ�_����_����) {
//	bool success = _sut.Purchase(_store, Product::Shampoo, 15);
//	ASSERT_FALSE(success);
//	ASSERT_EQ(10, _store.GetInventory(Product::Shampoo));
//}

Store CreateStoreWithInventory(Product product, int count) {
	Store store;
	store.AddInventory(product, count);
	
	return store;
}

Customer CreateCustomer() {
	return Customer{};
}

TEST_F(CustomerTests, �����ִ�_�κ�_����_����) {
	Store store = CreateStoreWithInventory(Product::Shampoo, 10);
	Customer sut = CreateCustomer();

	bool success = sut.Purchase(store, Product::Shampoo, 5);
	ASSERT_TRUE(success);
	ASSERT_EQ(5, store.GetInventory(Product::Shampoo));
}

TEST_F(CustomerTests, �����_�κ�_����_����) {
	Store store = CreateStoreWithInventory(Product::Shampoo, 10);
	Customer sut = CreateCustomer();

	bool success = sut.Purchase(store, Product::Shampoo, 15);
	ASSERT_FALSE(success);
	ASSERT_EQ(10, store.GetInventory(Product::Shampoo));
}


/*
	�ʱ� ��ǰ / �ʱ� ��ǰ ���� / ���� ���� / ���
*/

class ParameterizedCustomerTests :
	public ::testing::TestWithParam<std::tuple<Product, int, int, bool>>
{
};

TEST_P(ParameterizedCustomerTests, CheckCustomerPurchase) {
	auto& param = GetParam();
	Product product = std::get<0>(param);
	int initCount = std::get<1>(param);
	int purchaseCount = std::get<2>(param);
	
	bool expected = std::get<3>(param);
	int expectedCount = expected ? initCount - purchaseCount : initCount;

	Store store = CreateStoreWithInventory(product, initCount);
	Customer sut = CreateCustomer();

	bool success = sut.Purchase(store, product, purchaseCount);
	ASSERT_EQ(success, expected);
	ASSERT_EQ(expectedCount, store.GetInventory(product));
}

INSTANTIATE_TEST_SUITE_P(
	CustomerTest,
	ParameterizedCustomerTests,
	::testing::Values(
		std::make_tuple(Product::Shampoo, 10, 15, false),
		std::make_tuple(Product::Shampoo, 10, 5, true),
		std::make_tuple(Product::Shampoo, 5, 5, true)));