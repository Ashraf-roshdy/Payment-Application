#pragma once
#ifndef server_h
#define server_h
#include "../Card/card.h"
#include "../terminal/terminal.h"
typedef enum EN_transState_t
{
	APPROVED, DECLINED_INSUFFECIENT_FUND, DECLINED_STOLEN_CARD, INTERNAL_SERVER_ERROR , DECLINED_INVALID_CARD
}EN_transState_t;
typedef struct ST_transaction_t
{
	ST_cardData_t cardHolderData;
	ST_terminalData_t terminalData;
	EN_transState_t transState;
	uint32_t transactionSequenceNumber;
}ST_transaction_t;
typedef enum EN_Status_t
{
	Active, Blocked
}EN_Status_t;
typedef struct ST_accountsDB_t
{
	float balance;
	uint8_t primaryAccountNumber[20];
	EN_Status_t status;
}ST_accountsDB_t;
typedef enum EN_serverError_t
{
	SERVER_OK, SAVING_FAILED, TRANSACTION_NOT_FOUND, ACCOUNT_NOT_FOUND, LOW_BALANCE , Blocked_Account
}EN_serverError_t;
EN_transState_t  recieveTransactionData(ST_transaction_t* transData);
EN_serverError_t isValidAccount(ST_cardData_t* cardData);
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData);
EN_serverError_t saveTransaction(ST_transaction_t* transData);
EN_serverError_t getTransaction(ST_transaction_t* transData);

#endif