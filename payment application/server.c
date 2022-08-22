#include "server.h"
#include "string.h"

ST_accountsDB_t account_database[255] = { {30000,1234567890qwerty},{40000,1324567890qwertyu},{50000,1243567890qwertyu},{60000,1235467890qwertyu},{70000,1234576890qwertyui} };

ST_transaction_t transaction_database[255] = { {0,0,0,0} };



EN_transStat_t recieveTransactionData(ST_transaction_t* transData)
{
	unsigned char card_here = 0;
	unsigned char check_amount;
	for (int i = 0; i < 255; i++)
	{
		if ((transData->cardHolderData.primaryAccountNumber) == account_database[i].primaryAccountNumber)
		{
			card_here = 1;
		}
	}
	if (card_here == 0)
	{
		return DECLINED_STOLEN_CARD;
	}
	else
	{
		check_amount = isBelowMaxAmount(transData->terminalData);
		if (check_amount == EXCEED_MAX_AMOUNT)
		{
			return DECLINED_INSUFFECIENT_FUND;
		}
		else
		{
			int j = 0;
			while (transaction_database[j].transactionSequenceNumber != OK)
			{
				j++;
			}
			strcpy(transaction_database[j].cardHolderData.primaryAccountNumber ,transData->cardHolderData.primaryAccountNumber);
			account_database[j].balance = account_database[j].balance - transaction_database[j].terminalData.transAmount;
			transaction_database[j].terminalData.maxTransAmount = account_database[j].balance;
			return APPROVED;

		}
	}
}


EN_serverError_t isValidAccount(ST_cardData_t* cardData)
{
	unsigned char card_here = 0;
	
	for (int i = 0; i < 255; i++)
	{
		if (strcomp(cardData->primaryAccountNumber , account_database[i].primaryAccountNumber)==0)
		{
			card_here = 1;
		}
	}
	if (card_here == 0)
	{
		return DECLINED_STOLEN_CARD;
	}
	else
		return OK;
}

EN_serverError_t isAmountAvailable(ST_terminalData_t* termData)
{
	if (termData->maxTransAmount >= termData->transAmount)
	{
		return OK;
	}
	else
		return LOW_BALANCE;
}

EN_serverError_t saveTransaction(ST_transaction_t* transData)
{

}