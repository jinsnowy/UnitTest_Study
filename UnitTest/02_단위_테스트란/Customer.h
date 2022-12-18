#pragma once
#include "Product.h"

class Store;
class Customer
{
public:
	Customer();

	virtual ~Customer();

	virtual bool Purchase(Store& store, Product product, int count);
};

