#pragma once

#include "Product.h"

class Store
{
public:
	Store();

	virtual ~Store();

	virtual void AddInventory(Product product, int count);

	virtual bool HasEnoughInventory(Product product, int count);

	virtual void RemoveInventory(Product product, int count);

	virtual int GetInventory(Product product);

private:
	int InventoryCount[(int)Product::End] = {};
};
