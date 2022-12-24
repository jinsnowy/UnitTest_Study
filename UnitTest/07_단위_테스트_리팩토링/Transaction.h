#pragma once

class Transaction;
class TransactionGuard {
public:
	TransactionGuard(Transaction* transaction);
	~TransactionGuard();

	void Commit();
private:
	bool _committed;
	Transaction* _transaction;
};

class DBConnection;
class Transaction
{
private:
	DBConnection* _conn;

public:
	Transaction(DBConnection* conn);
	
	TransactionGuard Start();

	DBConnection* GetConnection();

	void Commit();

	void Rollback();
};