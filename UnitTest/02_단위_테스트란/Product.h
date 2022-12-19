#pragma once

enum class Product {
	Shampoo,
	Book,
	End
};

static string GetProductName(Product product) {
	switch (product)
	{
	case Product::Shampoo:
		return "Shampoo";
	case Product::Book:
		return "Book";
	default:
		return "None";
	}
}