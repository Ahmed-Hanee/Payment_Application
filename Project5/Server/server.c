#include <stdio.h>
#include <string.h>
#include "../Server/server.h"

ST_accountsDB_t accountsDB[255] = {
{ 2000.0, RUNNING, "01234567891234567890" },
{ 2000.0, BLOCKED, "01234567891234567891" },
{ 2000.0, RUNNING, "01234567891234567820" },
{ 20000.0, RUNNING, "01233567891234567891" },
 {25000.0,BLOCKED,"0123456789123456789"},
{ 32000.0, BLOCKED, "01234567891234567895" },
{ 22000.0, RUNNING, "01234567891134567820" },
{ 12000.0, BLOCKED, "8989374665437432" } 
};
ST_transaction Transaction_Data;
ST_transaction* Transaction_Data_Ptr = &Transaction_Data;
ST_transaction Transactions[255] = { 0 };
EN_serverError_t ServerError = 0;
uint32_t transactionSequenceNumber = 0;
ST_accountsDB_t* valid_account_ptr = 0;
uint16_t Valid_Counter = 0;
EN_serverError_t Is_Validated =0;
EN_serverError_t Is_Amount_available=0;
EN_serverError_t Trans_saving=0;
EN_serverError_t blOCKED_ACC = 0;



EN_transStat_t recieveTransactionData(ST_transaction* transData)
{

	if (Is_Validated = isValidAccount(&transData->cardHolderData, &accountsDB) == ACCOUNT_NOT_FOUND)
	{
		ServerError = FRAUD_CARD;
		return ServerError;
	}
	if (Is_Amount_available = isAmountAvailable(&transData->terminalData, &accountsDB) == LOW_BALANCE)
	{
		ServerError = DECLINED_INSUFFECIENT_FUND;
		return ServerError;
	}
	if (blOCKED_ACC = isBlockedAccount(&transData->cardHolderData) == BLOCKED_ACCOUNT)
	{
		ServerError = DECLINED_STOLEN_CARD;
		return ServerError;
	}

	if (Trans_saving = saveTransaction(transData) == SAVING_FAILED)
	{
		 ServerError=INTERNAL_SERVER_ERROR;
		 return ServerError;
	}

	accountsDB[Valid_Counter].balance = (accountsDB[Valid_Counter].balance - transData->terminalData.transAmount);
	printf("Your Balance After The Transaction Procsses : %.2f\n", accountsDB[Valid_Counter].balance);

	return APPROVED;
}
EN_serverError_t isValidAccount(ST_cardData_t* Card_Data)
{
	for (Valid_Counter = (0 + Valid_Counter); Valid_Counter < 255; Valid_Counter++)
	{
		if (strcmp(Card_Data->primaryAccountNumber, accountsDB[Valid_Counter].primaryAccountNumber) == 0)
		{
			
			if (accountsDB)
				return SERVER_OK;
		}
		
		
	}
	ServerError = ACCOUNT_NOT_FOUND;
	return ServerError;
}
EN_serverError_t isBlockedAccount(ST_cardData_t* Card_Data)
{
	for (Valid_Counter = (0 + Valid_Counter); Valid_Counter < 255; Valid_Counter++)
	{
		if (strcmp(Card_Data->primaryAccountNumber, accountsDB[Valid_Counter].primaryAccountNumber) == 0)
		{
			if (accountsDB[Valid_Counter].state == BLOCKED)
			{
				ServerError = BLOCKED_ACCOUNT;
				return ServerError;
			}
			else
			{
				return SERVER_OK;

			}
		

		}


	}
}
EN_serverError_t isAmountAvailable(ST_terminalData_t* Term_Data, ST_accountsDB_t* Db_Ref)
{

	if (Term_Data->transAmount <= Db_Ref->balance)
	{
		return SERVER_OK;
	}
	return LOW_BALANCE;
}
EN_serverError_t saveTransaction(ST_transaction* Trans_Data)
{
    if (transactionSequenceNumber < 255) {
      

		Transactions[transactionSequenceNumber].cardHolderData = Trans_Data->cardHolderData;
		Transactions[transactionSequenceNumber].terminalData = Trans_Data->terminalData;
		Transactions[transactionSequenceNumber].transState = Trans_Data->transState;
		Transactions[transactionSequenceNumber].transactionSequenceNumber = transactionSequenceNumber;
		transactionSequenceNumber++;
        return SERVER_OK;
    }
    else {
        printf("\nMAX TRANSACTION SEQUENCE NUMBER\n");
        return SAVING_FAILED;
    }
}
void listSavedTransactions(void) {
	for (int i = 1; i < transactionSequenceNumber; i++) {
		printf("\n#########################\n");
		printf("Transaction Sequence Number: %d\n", Transactions[i].transactionSequenceNumber);
		printf("Transaction Date: %s\n", Transactions[i].terminalData.transactionDate);
		printf("Transaction Amount: %.2f\n", Transactions[i].terminalData.transAmount);

		printf("Transaction State: %d\n", Transactions->transState);

		printf("Terminal Max Amount: %.1f\n", Transactions[i].terminalData.maxTransAmount);
		printf("Cardholder Name: %s\n", Transactions[i].cardHolderData.cardHolderName);
		printf("PAN: %s\n", Transactions[i].cardHolderData.primaryAccountNumber);
		printf("Card Expiration Date: %s\n", Transactions[i].cardHolderData.cardExpirationDate);
		printf("#########################\n");

	}
}

void recieveTransactionDataTest(void) 
{
	printf("-----------------------------------------Test Case 1:---------------------------------------\n");
	ST_transaction Test_1 = { {"","01234567891234567890","" }, {0, 0, ""},APPROVED,0 };
	ST_transaction* Trans_Test_1 = &Test_1;

	printf("Tester Account: 01234567891234567890\n");
	printf("Function Name: recieveTransactionData\n");
	printf("Expected Result: Approved\n");

	uint8_t Test1 = recieveTransactionData(Trans_Test_1);
	if (Test1 == APPROVED)
		printf("Actual Result: APPROVED\n");
	else
		printf("Actual Result: FRAUD_CARD\n");
	printf("-----------------------------------------Test Case 1 END:---------------------------------------\n");

	printf("-----------------------------------------Test Case 2:---------------------------------------\n");
	ST_transaction Test_2= { {"","01234567891234567891","" }, {0, 0, ""},APPROVED,0 };
	ST_transaction* Trans_Test_2 = &Test_2;
	printf("Tester Account: 01234567891234567891\n");
	printf("Function Name: recieveTransactionData\n");
	printf("Expected Result: DECLINED_STOLEN_CARD\n");
	uint8_t Test2 = recieveTransactionData(Trans_Test_2);
	if (Test2 == APPROVED)
		printf("Actual Result: Server_OK\n");
	else
		printf("Actual Result: DECLINED_STOLEN_CARD\n");
	printf("-----------------------------------------Test Case 2 END:---------------------------------------\n");
	}
void isValidAccountTest(void)
{
	printf("-----------------------------------------Test Case 1:---------------------------------------\n");
	ST_cardData_t Card_3 =  { "", "01234567891134567820", "" } ;
	ST_transaction* Card_Test_3 = &Card_3;
	printf("Tester Account: 01234567891134567820\n");
	printf("Function Name: isValidAccount\n");
	printf("Expected Result: SERVER_OK\n");


	uint8_t Test3 = isValidAccount(Card_Test_3);
	if (Test3 == SERVER_OK)
		printf("Actual Result: SERVER_OK\n");
	else
		printf("Actual Result: ACCOUNT_NOT_FOUND\n");

	printf("-----------------------------------------Test Case 1 END:---------------------------------------\n");

	printf("-----------------------------------------Test Case 2:---------------------------------------\n");
	ST_cardData_t Card_4 = { "", "01234567891234567896", "" };
	ST_transaction* Card_Test_4 = &Card_4;
	printf("Tester Account: 01234567891234567896\n");
	printf("Function Name: isValidAccount\n");
	printf("Expected Result: ACCOUNT_NOT_FOUND\n");
	uint8_t Test4 = isValidAccount(Card_Test_4);
	if (Test4 == SERVER_OK)
		printf("Actual Result: SERVER_OK\n");
	else
		printf("Actual Result: ACCOUNT_NOT_FOUND\n");
	printf("-----------------------------------------Test Case 2 END:---------------------------------------\n");
}
void isBlockedAccountTest(void)
{
	printf("-----------------------------------------Test Case 1:--------------------------------------\n");
	ST_cardData_t Card5 = { "", "01234567891234567820", "" };
	ST_transaction* Card_Test_5 = &Card5;

	printf("Tester Account: 01234567891234567820\n");
	printf("Function Name: isBlockedAccount\n");
	printf("Expected Result: SERVER_OK\n");

	uint8_t Test5 = isBlockedAccount(Card_Test_5);
	if (Test5== SERVER_OK)
		printf("Actual Result: SERVER_OK\n");
	else
		printf("Actual Result: BLOCKED_ACCOUNT\n");
	printf("-----------------------------------------Test Case 1 END:---------------------------------------\n");

	printf("-----------------------------------------Test Case 2:---------------------------------------\n");
	ST_cardData_t Card_6 = { "", "01234567891234567895", "" };
	ST_transaction* Card_Test_6 = &Card_6;

	printf("Tester Account: 01234567891234567895\n");
	printf("Function Name: isBlockedAccount\n");
	printf("Expected Result: BLOCKED_ACCOUNT\n");
	uint8_t Test6 = isBlockedAccount(Card_Test_6);
	if (Test6 == SERVER_OK)
		printf("Actual Result: SERVER_OK\n");
	else
		printf("Actual Result: BLOCKED_ACCOUNT\n");
	printf("-----------------------------------------Test Case 2 END:---------------------------------------\n");
}
void isAmountAvailableTest(void)
{
	printf("-----------------------------------------Test Case 1:---------------------------------------\n");

	 struct ST_accountsDB_t Account_Data = { 1000,RUNNING,"" };
	 struct ST_accountsDB_t* Account_Data_Ptr = &Account_Data;
	 struct ST_terminalData_t Terminal_Data = { 5000,10000,"" };
	 struct ST_terminalData_t* Terminal_Data_Ptr = &Terminal_Data;

	printf("Tester Amount: 1000\n");
	printf("Function Name: isAmountAvailable\n");
	printf("Expected Result: LOW_BALANCE\n");

	uint8_t Test5 = isAmountAvailable(Terminal_Data_Ptr,Account_Data_Ptr);
	if (Test5 == SERVER_OK)
		printf("Actual Result: SERVER_OK\n");
	else
		printf("Actual Result: LOW_BALANCE\n");
	printf("-----------------------------------------Test Case 1 END:---------------------------------------\n");

	printf("-----------------------------------------Test Case 2:---------------------------------------\n");
	struct ST_accountsDB_t Account_Data_1 = { 1000,RUNNING,"" };
	struct ST_accountsDB_t* Account_Data_Ptr_1 = &Account_Data_1;
	struct ST_terminalData_t Terminal_Data_1 = { 1000,6000,"" };
	struct ST_terminalData_t* Terminal_Data_Ptr_1 = &Terminal_Data_1;

	printf("Tester Amount: 10000\n");
	printf("Function Name: isAmountAvailable\n");
	printf("Expected Result: SERVER_OK\n");

	uint8_t Test6 = isAmountAvailable(Terminal_Data_Ptr_1,Account_Data_Ptr_1);
	if (Test6 == SERVER_OK)
		printf("Actual Result: SERVER_OK\n");
	else
		printf("Actual Result: LOW_BALANCE\n");
	printf("-----------------------------------------Test Case 2 END:---------------------------------------\n");
}
void saveTransactionTest(void)
{
	printf("-----------------------------------------Test Case 1:---------------------------------------\n");
	ST_transaction Card_Test7 = { { "Ahmed Hany Moahmed Negm","0123456789123456789","08/25"}
	, { 5000, 20000, "11/02/2021" }
	, APPROVED , 0 };
	ST_transaction * Card_Test_7 = &Card_Test7;
	printf("Function Name: saveTransaction\n");
	printf("Expected Result: SERVER_OK\n");
	printf("Actual Result: ");
	if (saveTransaction(Card_Test_7) == SERVER_OK)
		printf("SERVER_OK\n");
	else
		printf("SAVING_FAILED\n");
	printf("-----------------------------------------Test Case 1 END:---------------------------------------\n");

}
void listSavedTransactionsTest(void)
{
	printf("-----------------------------------------Test Case 1:---------------------------------------\n");
	printf("Function Name: listSavedTransactions\n");
	printf("Expected Result: Information Retrived\n");
	printf("Actual Result:\n");
	listSavedTransactions();
	printf("-----------------------------------------Test Case 1 END:-------------------------------------\n");

}

//int main()
//{
//	recieveTransactionDataTest();
//	isBlockedAccountTest();
//	isValidAccountTest();
//	isAmountAvailableTest();
//	saveTransactionTest();
//	listSavedTransactionsTest();
//	system("pause");
//}

