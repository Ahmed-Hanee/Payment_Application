#include <stdio.h>
#include "../Card/card.h"
#include "../Server/server.h"
#include "../Terminal/terminal.h"
#include "../Application/app.h"

EN_cardError_t Card_Holder_Name;
EN_cardError_t Card_Expiry_Date;
EN_cardError_t Card_PAN;
ST_cardData_t cardHolderData;
ST_cardData_t* cardData = &cardHolderData;

void appStart(void)
{


	if (Card_Holder_Name = getCardHolderName(cardData) == WRONG_NAME)
	{
		return 0;
	}

	if (Card_Expiry_Date = getCardExpiryDate(cardData) == WRONG_EXP_DATE)
	{
		return 0;
	}

	if (Card_PAN = getCardPAN(cardData) == WRONG_PAN)
	{
		return 0;
	}


	EN_terminalError_t vaild_PAN;
	EN_terminalError_t transaction_Date;
	EN_terminalError_t card_EXpired;
	EN_terminalError_t max_Amount;
	EN_terminalError_t transaction_Amount;
	EN_terminalError_t below_Max_Amount;
	ST_terminalData_t TerminalData;
	ST_terminalData_t* termData = &TerminalData;


	if (transaction_Date = getTransactionDate(termData) == WRONG_DATE)
	{

		return 0;
	}


	if (card_EXpired = isCardExpired(cardHolderData, TerminalData) == EXPIRED_CARD)
	{
		printf(" Card is Expired!");
		return 0;
	}


	if (max_Amount = setMaxAmount(termData) == INVALID_MAX_AMOUNT)
	{
		printf("Invalid Max Amount");
		return 0;
	}

	if (transaction_Amount = getTransactionAmount(termData) == INVALID_AMOUNT)
	{
		printf("Invalid Amount !");
		return 0;
	}

	if (below_Max_Amount = isBelowMaxAmount(termData) == EXCEED_MAX_AMOUNT)
	{
		printf("Exceeded Max Amount !");
		return 0;
	}

	EN_transStat_t recieveTransaction;
	ST_transaction transactonData;
	ST_transaction* transData = &transactonData;

	transData->cardHolderData = cardHolderData;
	transData->terminalData = TerminalData;
	recieveTransaction = recieveTransactionData(&transactonData);



	switch (recieveTransaction)
	{
	case APPROVED:
		printf("Transaction was successfull, Thank You !! \n");
		break;

	case DECLINED_INSUFFECIENT_FUND:
		saveTransaction(transData);
		printf("Transaction Declined Due To Insuffecient Fund");
		break;
	case FRAUD_CARD:
		saveTransaction(transData);
		printf("Account Does Not Exsists");
		break;
	case DECLINED_STOLEN_CARD:
		saveTransaction(transData);
		printf("Transaction Declined AS This Card Is Blocked\n");
		break;
	case INTERNAL_SERVER_ERROR:
		saveTransaction(transData);
		printf("Transaction Declined Due To Server Error, Please Try Again Later .. ");
		break;

	default:
		break;
	}
	return;
}