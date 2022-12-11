
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../Card/card.h"

struct ST_cardData_t Card_Data;
struct ST_cardData_t* Card_Ptr = &Card_Data;

EN_cardError_t getCardHolderName(ST_cardData_t* Card_Data)
{
	printf("1)Please enter the Card Holder's Name:\n ");
	printf("****************************************************************************************\n");

	gets(&Card_Data->cardHolderName);
	if (strlen(Card_Data->cardHolderName) < 20 || (Card_Data->cardHolderName) == NULL || strlen(Card_Data->cardHolderName) > 24)
	{
		printf("Please Enter A Name between 20 And 24 Character\n");
		return WRONG_NAME;
	}
	else {
		uint8_t i = 0;
		for (i = 0; i < strlen(Card_Data->cardHolderName); i++) {
			if (!isalpha(Card_Data->cardHolderName[i]) && (Card_Data->cardHolderName[i] != ' ')) {
				printf("Card Holder Name Must Me Consists Only From 24 Alphapetics\n");
				return WRONG_NAME;

			}
			else {
				Card_Data->cardHolderName[i] = Card_Data->cardHolderName[i];
			}
		}
		Card_Data->cardHolderName[i] = '\0';
		printf("WELCOME Mr. %s\n", Card_Data->cardHolderName);
		printf("****************************************************************************************\n");


		return CARD_OK;
	}
}

EN_cardError_t getCardExpiryDate(ST_cardData_t* Card_Data)
{
	printf("2)Please Enter Card Expiry Date In Form(MM/YY):\n");
	gets(Card_Data->cardExpirationDate);

	if (
		(strlen(Card_Data->cardExpirationDate) != 5) || (Card_Data->cardExpirationDate) == NULL ||
		(!isdigit(Card_Data->cardExpirationDate[0])) || (!isdigit(Card_Data->cardExpirationDate[1])) ||
		(Card_Data->cardExpirationDate[2] != '/') || (!isdigit(Card_Data->cardExpirationDate[3]))
		|| (!isdigit(Card_Data->cardExpirationDate[4])))
	{
		printf("Please Make Sure Typing The Correct Expiration Date With This Format (MM/YY)\n");
		return WRONG_EXP_DATE;
	}
	else
	{
		printf("-Your Card Expiry Date Added SucssesFully :%s\n", Card_Data->cardExpirationDate);
		return CARD_OK;
	}
}

EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
	printf("3)Please enter the Card PAN: \n");
	gets(cardData->primaryAccountNumber);

	if (strlen(cardData->primaryAccountNumber) < 16 || (cardData->cardHolderName) == NULL || strlen(cardData->primaryAccountNumber) > 20)
	{
		printf("Your Card PAN Must Be 20 Numeric Characters String\n");

		return WRONG_PAN;
	}
	printf("Your Card PAN is:%s\n", cardData->primaryAccountNumber);

	return CARD_OK;
}


void getCardHolderNameTest(void)
{

	printf("-----------------------------------------Test Case 1:---------------------------------------\n");
	printf("Tester Name: No Tester Name\n");
	printf("Function Name: getCardHolderName\n");
	printf("Expected Result: WRONG_NAME\n");
	printf("---------------------------------------------------------------\n");
	uint8_t Test1 = getCardHolderName(Card_Ptr);
	if (Test1 == CARD_OK)
		printf("Actual Result: CARD_OK\n");
	else
		printf("Actual Result: WRONG_NAME\n");

	printf("-----------------------------------------Test Case 1 END:---------------------------------------\n");
	printf("-----------------------------------------Test Case 2:---------------------------------------\n");

	printf("Tester Name: Ahmed Hany \n");
	printf("Function Name: getCardHolderName\n");
	printf("Expected Result: WRONG_NAME\n");
	printf("---------------------------------------------------------------\n");
	uint8_t Test2 = getCardHolderName(Card_Ptr);
	if (Test2 == CARD_OK)
		printf("Actual Result: CARD_OK\n");
	else
		printf("Actual Result: WRONG_NAME\n");
	printf("-----------------------------------------Test Case 2 END:---------------------------------------\n");

	printf("-----------------------------------------Test Case 3 :---------------------------------------\n");
	printf("Tester Name: Ahmed Ha1ny Mohamed negm \n");
	printf("Function Name: getCardHolderName\n");
	printf("Expected Result: WRONG_NAME\n");
	printf("---------------------------------------------------------------\n");
	uint8_t Test3 = getCardHolderName(Card_Ptr);
	if (Test3 == CARD_OK)
		printf("Actual Result: CARD_OK\n");
	else
		printf("Actual Result: WRONG_NAME\n");
	printf("-----------------------------------------Test Case 3 END:---------------------------------------\n");
	printf("-----------------------------------------Test Case 4 :---------------------------------------\n");
	printf("Tester Name: Ahmed Hany Mohamed negm \n");
	printf("Function Name: getCardHolderName\n");
	printf("Expected Result: CARD_OK\n");
	printf("---------------------------------------------------------------\n");
	uint8_t Test4 = getCardHolderName(Card_Ptr);
	if (Test4 == CARD_OK)
		printf("Actual Result: CARD_OK\n");
	else
		printf("Actual Result: WRONG_NAME\n");
	printf("-----------------------------------------Test Case 4 END:---------------------------------------\n");

}
void getCardExpiryDateTest(void)
{
	printf("-----------------------------------------Test Case 1:---------------------------------------\n");
	printf("Tester ExpiryDate: No Tester ExpiryDate\n");
	printf("Function Name: getCardExpiryDate\n");
	printf("Expected Result: WRONG_EXP_DATE\n");
	printf("---------------------------------------------------------------------------------------------\n");
	uint8_t Test1 = getCardExpiryDate(Card_Ptr);
	if (Test1 == CARD_OK)
		printf("Actual Result: CARD_OK\n");
	else
		printf("Actual Result: WRONG_EXP_DATE\n");
	printf("-----------------------------------------Test Case 1 END:---------------------------------------\n");
	printf("-----------------------------------------Test Case 2:---------------------------------------\n");
	printf("Tester ExpiryDate:08/2020\n");
	printf("Function Name: getCardExpiryDate\n");
	printf("Expected Result: WRONG_EXP_DATE\n");
	printf("-------------------------------------------------------------------------------------------\n");
	uint8_t Test2 = getCardExpiryDate(Card_Ptr);
	if (Test2 == CARD_OK)
		printf("Actual Result: CARD_OK\n");
	else
		printf("Actual Result: WRONG_EXP_DATE\n");
	printf("-----------------------------------------Test Case 2 END:---------------------------------------\n");

	printf("-----------------------------------------Test Case 3:---------------------------------------\n");
	printf("Tester ExpiryDate: 0827\n");
	printf("Function Name: getCardExpiryDate\n");
	printf("Expected Result: WRONG_EXP_DATE\n");
	printf("-------------------------------------------------------------------------------------------\n");
	uint8_t Test3 = getCardExpiryDate(Card_Ptr);
	if (Test3 == CARD_OK)
		printf("Actual Result: CARD_OK\n");
	else
		printf("Actual Result: WRONG_EXP_DATE\n");
	printf("-----------------------------------------Test Case 3 END:---------------------------------------\n");
	printf("-----------------------------------------Test Case 4 :---------------------------------------\n");
	printf("Tester ExpiryDate: 08/27 \n");
	printf("Function Name: getCardExpiryDate\n");
	printf("Expected Result: CARD_OK\n");
	printf("-------------------------------------------------------------------------------------------\n");
	uint8_t Test4 = getCardExpiryDate(Card_Ptr);
	if (Test4 == CARD_OK)
		printf("Actual Result: CARD_OK\n");
	else
		printf("Actual Result: WRONG_EXP_DATE\n");
	printf("-----------------------------------------Test Case 4 END:---------------------------------------\n");

}
void getCardPANTest(void)
{
	printf("-----------------------------------------Test Case 1 :---------------------------------------\n");
	printf("Tester PAN: No Tester PAN\n");
	printf("Function Name: getCardPAN\n");
	printf("Expected Result: WRONG_PAN\n");
	printf("---------------------------------------------------------------------------------------------\n");
	uint8_t Test1 = getCardPAN(Card_Ptr);
	if (Test1 == CARD_OK)
		printf("Actual Result: CARD_OK\n");
	else
		printf("Actual Result: WRONG_PAN\n");
	printf("-----------------------------------------Test Case 1 END:---------------------------------------\n");

	printf("-----------------------------------------Test Case 2 :---------------------------------------\n");
	printf("Tester PAN:012345678900 \n");
	printf("Function Name: getCardPAN\n");
	printf("Expected Result: WRONG_PAN\n");
	printf("-------------------------------------------------------------------------------------------\n");
	uint8_t Test2 = getCardPAN(Card_Ptr);
	if (Test2 == CARD_OK)
		printf("Actual Result: CARD_OK\n");
	else
		printf("Actual Result: WRONG_PAN\n");
	printf("-----------------------------------------Test Case 2 END:---------------------------------------\n");

	printf("-----------------------------------------Test Case 3:---------------------------------------\n");
	printf("Tester PAN: 012345678901234678900 \n");
	printf("Function Name: getCardPAN\n");
	printf("Expected Result: WRONG_PAN\n");
	printf("-------------------------------------------------------------------------------------------\n");
	uint8_t Test3 = getCardPAN(Card_Ptr);
	if (Test3 == CARD_OK)
		printf("Actual Result: CARD_OK\n");
	else
		printf("Actual Result: WRONGPAN\n");
	printf("-----------------------------------------Test Case 3 END:---------------------------------------\n");
	printf("-----------------------------------------Test Case 4    :---------------------------------------\n");
	printf("Tester PAN:  123456789123456789 \n");
	printf("Function Name: getCardPAN\n");
	printf("Expected Result: CARD_OK\n");
	printf("-------------------------------------------------------------------------------------------\n");
	uint8_t Test4 = getCardPAN(Card_Ptr);
	if (Test4 == CARD_OK)
		printf("Actual Result: CARD_OK\n");
	else
		printf("Actual Result: WRONG_PAN\n");
	printf("-----------------------------------------Test Case 4 END:---------------------------------------\n");

}

//int main() {
//	getCardHolderNameTest();
//	printf("*********************************************************************************************************************\n");
//	getCardPANTest();
//	printf("*********************************************************************************************************************\n");
//	getCardExpiryDateTest();
//	system("pause");
//	return 0;
//	
//}

