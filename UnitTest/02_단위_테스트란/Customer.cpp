#include "pch.h"
#include "Customer.h"
#include "Store.h"

Customer::Customer()
{
}

Customer::~Customer()
{
}

bool Customer::Purchase(Store& store, Product product, int count)
{
	if (store.HasEnoughInventory(product, count) == false)
		return false;

	store.RemoveInventory(product, count);

	return true;
}
