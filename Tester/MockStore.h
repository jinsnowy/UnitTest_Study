#pragma once
#include "02_����_�׽�Ʈ��/Store.h"

class MockStore : public Store
{
public:
	MOCK_METHOD(void, AddInventory, (Product, int), (override));

	MOCK_METHOD(int, GetInventory, (Product), (override));

	MOCK_METHOD(bool, HasEnoughInventory, (Product, int), (override));

	MOCK_METHOD(void, RemoveInventory, (Product, int), (override));
};
