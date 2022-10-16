#include "terminal.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define DateOfTransaction 10

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{
	printf("Enter Transaction date DD/MM/YYYY: ");
	scanf_s("%s", &termData->transactionDate, DateOfTransaction + 1 );

	if ((strlen(termData->transactionDate) != DateOfTransaction)
		|| (strlen(termData->transactionDate) == NULL)
		|| ((termData->transactionDate[2]) != '/')
		|| ((termData->transactionDate[5]) != '/')
//DD Wrong Formats
		|| (termData->transactionDate[0]>'3')
		|| ((termData->transactionDate[0]=='0') && (termData->transactionDate[1]=='0'))
		|| ((termData->transactionDate[0]=='3') && (termData->transactionDate[1]>'1'))
//MM Wrong Formats
		|| (termData->transactionDate[3]>'1')
		|| ((termData->transactionDate[3]=='0') && (termData->transactionDate[4]=='0'))
		|| ((termData->transactionDate[3]=='1') && (termData->transactionDate[4]>'2'))
// dd/MM/yy Not numbers		
		|| (isdigit(termData->transactionDate[0]) == 0) || (isdigit(termData->transactionDate[1]) == 0)
		|| (isdigit(termData->transactionDate[3]) == 0) || (isdigit(termData->transactionDate[4]) == 0)
		|| (isdigit(termData->transactionDate[6]) == 0) || (isdigit(termData->transactionDate[7]) == 0)
		|| (isdigit(termData->transactionDate[8]) == 0) || (isdigit(termData->transactionDate[9]) == 0))
		{
		return WRONG_DATE;
		}
	else
	{
		return Terminal_OK;
	}		
}

EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData)
{
//Compare the transaction date DD/MM/YYYY With  card expiry date MM/YY
	if ((termData.transactionDate[8]) > (cardData.cardExpirationDate[3]))
	{
		return EXPIRED_CARD;
	}
	else if ((termData.transactionDate[8]) == (cardData.cardExpirationDate[3]))	
	{
		if ((termData.transactionDate[9]) > (cardData.cardExpirationDate[4]))
		{
			return EXPIRED_CARD;
		}
		else if ((termData.transactionDate[9]) == (cardData.cardExpirationDate[4]))		
		{
			if ((termData.transactionDate[3]) > (cardData.cardExpirationDate[1]))
			{
				return EXPIRED_CARD;
			}
			else if ((termData.transactionDate[3]) == (cardData.cardExpirationDate[0]))
			{
				if ((termData.transactionDate[4]) > (cardData.cardExpirationDate[1]))
				{
					return EXPIRED_CARD;
				}
			}
		}

	}
	return Terminal_OK;
}
		
EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData)
{
	return Terminal_OK;
}

EN_terminalError_t setMaxAmount(ST_terminalData_t* termData)
{
	printf("Enter The MAX Transaction Amount: ");
	scanf_s("%f", &termData->maxTransAmount);
	if (termData->maxTransAmount <= 0)
	{
		return INVALID_MAX_AMOUNT; 
	}
	else
	{
		return Terminal_OK;
	}
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
	printf("Enter Transaction Amount: ");
	scanf_s("%f", &termData->transAmount);
	if ((termData->transAmount) <= 0)
	{
		return INVALID_AMOUNT;
	}
	return Terminal_OK;
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
	if((termData->transAmount) > (termData->maxTransAmount))
	{
		return EXCEED_MAX_AMOUNT;
	}
	return Terminal_OK;
}
