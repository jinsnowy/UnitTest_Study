#include "pch.h"
#include "Store.h"

Store::Store()
{
}

Store::~Store()
{
}

void Store::AddInventory(Product product, int count)
{
	InventoryCount[(int)product] += count;
}

bool Store::HasEnoughInventory(Product product, int count)
{
	return InventoryCount[(int)product] >= count;
}

void Store::RemoveInventory(Product product, int count)
{
	InventoryCount[(int)product] -= count;
}

int Store::GetInventory(Product product)
{
	return InventoryCount[(int)product];
}