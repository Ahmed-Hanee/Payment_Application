#include <stdio.h>
#include <string.h>
#include "../Terminal/terminal.h"
float Max_Amount =4000	;

EN_terminalError_t  TerminalError =0;

ST_terminalData_t Termial_Data;
ST_terminalData_t* Terminal_Data_Ptr = &Termial_Data;
 ST_cardData_t Card_Data;
 ST_cardData_t* Card_Ptr1 = &Card_Data;
EN_terminalError_t getTransactionDate(ST_terminalData_t* Terminal_Data)
{
	printf("4)Please Enter The Your Transaction Date (DD/MM/YY) \n");
	printf("****************************************************************************************\n");
	gets(Terminal_Data->transactionDate);
	if (strlen(Terminal_Data->transactionDate) != 10|| (Terminal_Data->transactionDate) == NULL|| (Terminal_Data->transactionDate[2] != '/') || (Terminal_Data->transactionDate[5] != '/'))
	{
		printf("Please Make Sure Typing The Correct Transaction Date In This Form (DD/MM/YYYY) \n");
		TerminalError = WRONG_DATE;
		return  TerminalError;
	}
	else
	{
	
		printf("Please Wait While Transaction Date Is Checked \n");
		printf("****************************************************************************************\n");

		return TERMINAL_OK;
	}
}

EN_terminalError_t isCardExpired(ST_cardData_t Card_Data,ST_terminalData_t Terminal_Data)
{

		printf("Loading Expiration Date Data ..... \n");
		printf("****************************************************************************************\n");

		if (Card_Data.cardExpirationDate[4] < Terminal_Data.transactionDate[9]|| Card_Data.cardExpirationDate[3] < Terminal_Data.transactionDate[8])
		{
			printf("Sorry Your Card Is Expired\n");
			TerminalError = EXPIRED_CARD;
			return  TerminalError;
	
		
			 if (Card_Data.cardExpirationDate[1] < Terminal_Data.transactionDate[4])
			{
				printf("Sorry Your Card Is Expired\n");
				TerminalError = EXPIRED_CARD;
				return  TerminalError;
			}
			else if (&Card_Data.cardExpirationDate[0] < Terminal_Data.transactionDate[3])
			{
				printf("Sorry Your Card Is Expired\n");
				TerminalError = EXPIRED_CARD;
				return  TerminalError;
			}
		}
		else
		{
	
			return TERMINAL_OK;
		}

}

 EN_terminalError_t getTransactionAmount(ST_terminalData_t * termData) {
    	printf("5)Please Enter Your Transaction Amount:\n");
		printf("****************************************************************************************\n");

    	scanf_s("%f", &termData->transAmount);
		printf("****************************************************************************************\n");

		if (termData->transAmount <= 0 ) {
			TerminalError = INVALID_AMOUNT;
			return  TerminalError;
		}
    	else
    		return TERMINAL_OK;
    }

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{

	if ((termData->transAmount) > (termData->maxTransAmount)) {
		TerminalError = EXCEED_MAX_AMOUNT;
		return  TerminalError;
	}
	else
	{
		return TERMINAL_OK;


	}
}

EN_terminalError_t setMaxAmount(ST_terminalData_t* termData)
{
    termData->maxTransAmount = Max_Amount;
    if ((termData->maxTransAmount) <= 0)
		TerminalError = INVALID_MAX_AMOUNT;
	     return  TerminalError;
    return TERMINAL_OK;
}

void getTransactionDateTest(void) {
	printf("-----------------------------------------Test Case 1:---------------------------------------\n");
	printf("Tester Date: No Tester Date\n");
	printf("Function Name: getTransactionDate\n");
	printf("Expected Result: WRONG_DATE\n");
	printf("---------------------------------------------------------------\n");
	uint8_t Test1 = getTransactionDate(Terminal_Data_Ptr);
	if (Test1 == TERMINAL_OK)
		printf("Actual Result: TERMINAL_OK\n");
	else
		printf("Actual Result: WRONG_DATE\n");

	printf("-----------------------------------------Test Case 1 END:---------------------------------------\n");
	printf("-----------------------------------------Test Case 2:---------------------------------------\n");

	printf("Tester Date:20/02/20221\n");
	printf("Function Name: getTransactionDate\n");
	printf("Expected Result: WRONG_DATE\n");
	printf("---------------------------------------------------------------\n");
	uint8_t Test2 = getTransactionDate(Terminal_Data_Ptr);
	if (Test2 == TERMINAL_OK)
		printf("Actual Result: TERMINAL_OK\n");
	else
		printf("Actual Result: WRONG_DATE\n");
	printf("-----------------------------------------Test Case 2 END:---------------------------------------\n");

	printf("-----------------------------------------Test Case 3 :---------------------------------------\n");
	printf("Tester Date: 20/2020\n");
	printf("Function Name: getTransactionDate\n");
	printf("Expected Result: WRONG_DATE\n");
	printf("---------------------------------------------------------------\n");
	uint8_t Test3 = getTransactionDate(Terminal_Data_Ptr);
	if (Test3 == TERMINAL_OK)
		printf("Actual Result: TERMINAL_OK\n");
	else
		printf("Actual Result: WRONG_DATE\n");
	printf("-----------------------------------------Test Case 3 END:---------------------------------------\n");
	printf("-----------------------------------------Test Case 4 :---------------------------------------\n");
	printf("Tester Date: 20-02-2020 \n");
	printf("Function Name: getTransactionDate\n");
	printf("Expected Result: WRONG_DATE\n");
	printf("---------------------------------------------------------------\n");
	uint8_t Test4 = getTransactionDate(Terminal_Data_Ptr);
	if (Test4 == TERMINAL_OK)
		printf("Actual Result: TERMINAL_OK\n");
	else
		printf("Actual Result: WRONG_DATE\n");
	printf("-----------------------------------------Test Case 4 END:---------------------------------------\n");
	printf("-----------------------------------------Test Case 5 :---------------------------------------\n");
	printf("Tester Date: 20/02/2020 \n");
	printf("Function Name: getTransactionDate\n");
	printf("Expected Result: TERMINAL_OK\n");
	printf("---------------------------------------------------------------\n");
	uint8_t Test5 = getTransactionDate(Terminal_Data_Ptr);
	if (Test5 == TERMINAL_OK)
		printf("Actual Result: TERMINAL_OK\n");
	else
		printf("Actual Result: WRONG_DATE\n");
	printf("-----------------------------------------Test Case 5 END:---------------------------------------\n");
}
void isCardExpriedTest(void) {
	/*This Test Case Expected Not To Write Expiry Date*/
	printf("-----------------------------------------Test Case 1:---------------------------------------\n");
	printf("Tester Date: No Expiry Tester Date\n");
	printf("Function Name: isCardExpriedTest\n");
	printf("Expected Result: EXPIRED_CARD\n");
	printf("---------------------------------------------------------------\n");
	getCardExpiryDate(Card_Ptr1);
	getTransactionDate(Terminal_Data_Ptr);
	uint8_t Test1 = isCardExpired(Card_Data,Termial_Data);
	if (Test1 == TERMINAL_OK)
		printf("Actual Result: TERMINAL_OK\n");
	else
		printf("Actual Result: EXPIRED_CARD\n");
	printf("-----------------------------------------Test Case 1 END:---------------------------------------\n");
	/*This Test Case Expected To Write	 Date > Expiry Date*/
	printf("-----------------------------------------Test Case 2:--------------------------------------------\n");
	printf("Tester Date: 08/29\n");
	printf("Function Name: isCardExpriedTest\n");
	printf("Expected Result: EXPIRED_CARD\n");
	printf("---------------------------------------------------------------\n");
	getCardExpiryDate(Card_Ptr1);
	getTransactionDate(Terminal_Data_Ptr);
	uint8_t Test2 = isCardExpired(Card_Data, Termial_Data);
	if (Test2 == TERMINAL_OK)
		printf("Actual Result: TERMINAL_OK\n");
	else
		printf("Actual Result: EXPIRED_CARD\n");
	printf("-----------------------------------------Test Case 2 END:---------------------------------------\n");
	/*This Test Case Expected To Write Transaction Date < Expiry Date*/

	printf("-----------------------------------------Test Case 3:--------------------------------------------\n");
	printf("Tester Date: 08/29\n");
	printf("Function Name: isCardExpriedTest\n");
	printf("Expected Result: TERMINAL_OK\n");
	printf("---------------------------------------------------------------\n");
	getCardExpiryDate(Card_Ptr1);
	getTransactionDate(Terminal_Data_Ptr);
	uint8_t Test3 = isCardExpired(Card_Data, Termial_Data);
	if (Test3 == TERMINAL_OK)
		printf("Actual Result: TERMINAL_OK\n");
	else
		printf("Actual Result: EXPIRED_CARD\n");
	printf("-----------------------------------------Test Case 3 END:---------------------------------------\n");

}
void getTransactionAmountTest(void) {
	printf("-----------------------------------------Test Case 1:---------------------------------------\n");
	printf("Tester Amount: -150\n");
	printf("Function Name: getTransactionAmount\n");
	printf("Expected Result: INVALID_AMOUNT\n");
	printf("---------------------------------------------------------------\n");
	uint8_t Test1 = getTransactionAmount(Terminal_Data_Ptr);
	if (Test1 == TERMINAL_OK)
		printf("Actual Result: TERMINAL_OK\n");
	else
		printf("Actual Result: INVALID_AMOUNT\n");
	printf("-----------------------------------------Test Case 1 END:---------------------------------------\n");	
	printf("-----------------------------------------Test Case 2:---------------------------------------\n");
	printf("Tester Amount: 150\n");
	printf("Function Name: getTransactionAmount\n");
	printf("Expected Result: TERMINAL_OK\n");
	printf("---------------------------------------------------------------\n");
	uint8_t Test2 = getTransactionAmount(Terminal_Data_Ptr);
	if (Test2 == TERMINAL_OK)
		printf("Actual Result: TERMINAL_OK\n");
	else
		printf("Actual Result: INVALID_AMOUNT\n");
	printf("-----------------------------------------Test Case 2 END:---------------------------------------\n");
}
void setMaxAmountTest(void)
{
	printf("-----------------------------------------Test Case 1:---------------------------------------\n");
	printf("Tester Max Amount:  Adding Max Amount Tester \n");
	printf("Function Name: setMaxAmount\n");
	printf("Expected Result: TERMINAL_OK\n");
	printf("---------------------------------------------------------------\n");
	uint8_t Test1 = setMaxAmount(Terminal_Data_Ptr);
	if (Test1 == TERMINAL_OK)
		printf("Actual Result: TERMINAL_OK\n");
	else
		printf("Actual Result: INVALID_MAX_AMOUNT\n");
	printf("-----------------------------------------Test Case 1 END:---------------------------------------\n");
}
void isBelowMaxAmountTest(void)
{
	printf("-----------------------------------------Test Case 1:---------------------------------------\n");
	printf("Tester Amount: 850\n");
	printf("Function Name: isBelowMaxAmount\n");
	printf("Expected Result: EXCEED_MAX_AMOUNT\\n");
	printf("-------------------------------------------------------------------------------\n");
	getTransactionAmount(Terminal_Data_Ptr);
	uint8_t Test1 = isBelowMaxAmount(Terminal_Data_Ptr);
	if (Test1 == TERMINAL_OK)
		printf("Actual Result: TERMINAL_OK\n");
	else
		printf("Actual Result: EXCEED_MAX_AMOUNT\n");
	printf("-----------------------------------------Test Case 1 END:---------------------------------------\n");
	printf("-----------------------------------------Test Case 2:---------------------------------------\n");
	printf("Tester Amount: 90\n");
	printf("Function Name: isBelowMaxAmount\n");
	printf("Expected Result: Terminal_OK\\n");
	printf("-------------------------------------------------------------------------------\n");
	getTransactionAmount(Terminal_Data_Ptr);
	uint8_t Test2 = isBelowMaxAmount(Terminal_Data_Ptr);
	if (Test2 == TERMINAL_OK)
		printf("Actual Result: TERMINAL_OK\n");
	else
		printf("Actual Result: EXCEED_MAX_AMOUNT\n");
	printf("-----------------------------------------Test Case 2 END:---------------------------------------\n");

}
//int main()
//{
//getTransactionDateTest();
// printf("*********************************************************************************************************************\n");
// isCardExpriedTest();
// printf("*********************************************************************************************************************\n");
//
// getTransactionAmountTest(); 
// printf("*********************************************************************************************************************\n");
//
// setMaxAmountTest();
// printf("*********************************************************************************************************************\n");
//
// isBelowMaxAmountTest();
//
// system("pause");
//

//}