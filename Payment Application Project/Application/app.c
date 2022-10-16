#include "app.h"
#include "../Card/card.h"
#include "../server/server.h"
#include "../terminal/terminal.h"
#include <stdio.h>
#include <string.h>


int main()
{
	appStart();
}

	void appStart()
	{
		ST_cardData_t card_data;
		ST_cardData_t* cardData = &card_data;

		if (getCardHolderName(cardData) == WRONG_NAME)
		{
			printf("WRONG NAME");
			return 0;
	    }
		if (getCardExpiryDate(cardData) == WRONG_EXP_DATE)
		{
			printf("WRONG EXP DATE");
			return 0;
		}
		if (getCardPAN(cardData) == WRONG_PAN)
		{
			printf("WRONG PAN");
			return 0;
		}
	//----------------------------------------------------------------------------------//	
		ST_terminalData_t term_data;
		ST_terminalData_t* termData = &term_data;

		if (getTransactionDate(termData) == WRONG_DATE)
		{
			printf("WRONG DATE");
			return 0;
		}
		if (isCardExpired(card_data, term_data) == EXPIRED_CARD)
		{
			printf("EXPIRED CARD");
			return 0;
		}
		if (setMaxAmount(termData) == INVALID_MAX_AMOUNT)
		{
			printf("INVALID MAX AMOUNT");
			return 0;
		}
		if (getTransactionAmount(termData) == INVALID_AMOUNT)
		{
			printf("INVALID AMOUNT");
			return 0;
		}
		if (isBelowMaxAmount(termData) == EXCEED_MAX_AMOUNT)
		{
			printf("EXCEED MAX AMOUNT");
			return 0;
		}
	//----------------------------------------------------------------------------------//

		ST_transaction_t trans_Data;
		ST_transaction_t* transData = &trans_Data;
		
		transData->cardHolderData = card_data;
		transData->terminalData = term_data;	
	
		EN_transState_t recieveData;

		recieveData= recieveTransactionData(transData);
		
			if (recieveData == DECLINED_STOLEN_CARD)
			{
				printf("DECLINED STOLEN CARD");
				return 0;
			}

			else if (recieveData == DECLINED_INVALID_CARD)
			{
				saveTransaction(transData);
				printf("DECLINED INVALID CARD");
				return 0;
			}

			else if (recieveData == DECLINED_INSUFFECIENT_FUND)
			{
				saveTransaction(transData);
				printf("DECLINED INSUFFECIENT FUND");
				return 0;
			}

			else if (recieveData == INTERNAL_SERVER_ERROR)
			{
				saveTransaction(transData);
				printf("INTERNAL SERVER ERROR");
				return 0;
			}

			else (recieveData == APPROVED);
			{
					printf("Successfull Transaction\n");
					getTransaction(transData);
					return 0;
			}
	}
