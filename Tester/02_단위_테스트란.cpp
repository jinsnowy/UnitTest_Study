#include "pch.h"
#include "02_����_�׽�Ʈ��/Customer.h"
#include "02_����_�׽�Ʈ��/Store.h"
#include "MockStore.h"

TEST(����_�ó�����_������, �����ִ�_�κ�_����_����) {
	// given
	Store store = {};
	store.AddInventory(Product::Shampoo, 10);
	Customer customer = {};

	// when
	bool success = customer.Purchase(store, Product::Shampoo, 5);

	// then
	ASSERT_TRUE(success);
	ASSERT_EQ(5, store.GetInventory(Product::Shampoo));
}

TEST(����_�ó�����_������, �����_�κ�_����_����) {
	// given
	Store store = {};
	store.AddInventory(Product::Shampoo, 10);
	Customer customer = {};

	// when
	bool success = customer.Purchase(store, Product::Shampoo, 15);

	// then
	ASSERT_FALSE(success);
	ASSERT_EQ(10, store.GetInventory(Product::Shampoo));
}

using ::testing::Return;

TEST(����_�ó�����_������, �����ִ�_�κ�_����_����) {
	// given
	MockStore store;
	ON_CALL(store, HasEnoughInventory(Product::Shampoo, 5))
			.WillByDefault(Return(true));
	Customer customer = {};

	EXPECT_CALL(store, RemoveInventory(Product::Shampoo, 5))
		.Times(1).WillOnce(Return());

	// when
	bool success = customer.Purchase(store, Product::Shampoo, 5);

	// then
	ASSERT_TRUE(success);
}

TEST(����_�ó�����_������, �����_�κ�_����_����) {
	// given
	MockStore store = {};
	ON_CALL(store, HasEnoughInventory(Product::Shampoo, 15))
		.WillByDefault(Return(false));
	Customer customer = {};

	EXPECT_CALL(store, RemoveInventory(Product::Shampoo, 15))
		.Times(0);

	// when
	bool success = customer.Purchase(store, Product::Shampoo, 15);

	// then
	ASSERT_FALSE(success);
}