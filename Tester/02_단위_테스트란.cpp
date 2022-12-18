#include "pch.h"
#include "02_단위_테스트란/Customer.h"
#include "02_단위_테스트란/Store.h"
#include "MockStore.h"

TEST(상점_시나리오_고전파, 여유있는_인벤_구매_성공) {
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

TEST(상점_시나리오_고전파, 빈약한_인벤_구매_실패) {
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

TEST(상점_시나리오_런던파, 여유있는_인벤_구매_성공) {
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

TEST(상점_시나리오_런던파, 빈약한_인벤_구매_실패) {
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