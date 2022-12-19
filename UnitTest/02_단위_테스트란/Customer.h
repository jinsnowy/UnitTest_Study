#pragma once
#include "Product.h"

class Store;
class Customer
{
public:
	string emailAddress = "customer@email.com";

public:
	Customer();

	virtual ~Customer();

	virtual bool Purchase(Store& store, Product product, int count);
};

