
#include "card.h"
#include <string.h>



EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
	if (strlen(cardData->cardHolderName) < 24 && strlen(cardData->cardHolderName) > 20)
	{
		return OK;
	}
	else
		return WRONG_NAME;
}


EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
	if (strlen(cardData->cardExpirationDate) == 5 && (cardData->cardHolderName[2] == '/'))
	{
		if ((cardData->cardHolderName[0] == 0 && cardData->cardHolderName[1] <= '9') || (cardData->cardHolderName[0] == 1 && (cardData->cardHolderName[1] <= '2')))
		{
			if((cardData->cardHolderName[3]<'3' && cardData->cardHolderName[4] <= '9')|| (cardData->cardHolderName[3] == '3' && cardData->cardHolderName[4] <= '1'))
				return OK;
		}
		
	}
	else
		return WRONG_EXP_DATE;
}

EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
	if (strlen(cardData->primaryAccountNumber) < 20 && strlen(cardData->primaryAccountNumber) > 15)
	{
		return OK;
	}
	else
		return WRONG_PAN;
}