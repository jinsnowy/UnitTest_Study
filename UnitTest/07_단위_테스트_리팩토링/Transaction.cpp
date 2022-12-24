#include "pch.h"
#include "Transaction.h"
#include "Application.h"

TransactionGuard::TransactionGuard(Transaction* transaction)
	:
	_committed(false),
	_transaction(transaction)
{
}

TransactionGuard::~TransactionGuard()
{
	if (_committed == false) {
		_transaction->Rollback();
	}
}

void TransactionGuard::Commit()
{
	_transaction->Commit();
	_committed = true;
}

Transaction::Transaction(DBConnection* conn)
	:
	_conn(conn)
{
}

TransactionGuard Transaction::Start()
{
	return TransactionGuard(this);
}

DBConnection* Transaction::GetConnection()
{
	return _conn;
}

void Transaction::Commit()
{
}

void Transaction::Rollback()
{
}
