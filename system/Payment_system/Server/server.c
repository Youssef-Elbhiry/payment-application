#include"server.h"
#include"../../Data_Bases/File_Handling/file_handling.h"
ST_accountsDB_t *ptacc;
extern list_t list;
int transnumber;
EN_transState_t recieveTransactionData(ST_transaction_t *transData){
       if(transData==NULL)
        {
            printf("null pointer in server\n");
        }
        else
        {
        EN_transState_t state;
       EN_serverError_t s;

      s= isValidAccount(&transData->cardHolderData,&ptacc);
        if(s==ACCOUNT_NOT_FOUND)
        {
            state =FRAUD_CARD;
        }
        else
        {
           s=isAmountAvailable(&transData->terminalData,ptacc);
           if(s==LOW_BALANCE)
        {

            state= DECLINED_INSUFFECIENT_FUND;
        }
        else
        {
          s=isBlockedAccount(ptacc);
             if(s==BLOCKED_ACCOUNT)
        {
            state =DECLINED_STOLEN_CARD;
        }
        else
        {
            ptacc->balance-=transData->terminalData.transAmount;
            update_accounts(&list);
             state=APPROVED;

        }
        }
        }
        transData->transState=state;
         s= saveTransaction(transData);
          if(s==SAVING_FAILED)
        {
            state=INTERNAL_SERVER_ERROR;
        }

        return state;
        }
        }

EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t **accountRefrence){
    if(cardData==NULL||accountRefrence==NULL)
    {
          printf("null pointer in server\n");
    }
    else
    {
           listnode *temp;
    for(temp=list.listhead;temp;temp=temp->next)
    {
         if(!strcmp(cardData->primaryAccountNumber,temp->data.primaryAccountNumber))
         {
            *accountRefrence=&temp->data;
           return  SERVER_OK;

         }
    }

           *accountRefrence=temp;
           return  ACCOUNT_NOT_FOUND;
    }
}

EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountRefrence){
    if(accountRefrence==NULL)
    {
       printf("null pointer in server\n");
    }
    else
    {
    if(accountRefrence->state==RUNNING)
   return SERVER_OK;
   else
   return BLOCKED_ACCOUNT;
    }


}

EN_serverError_t isAmountAvailable(ST_terminalData_t *termData,ST_accountsDB_t* accountRefrence){
   if(accountRefrence==NULL||termData==NULL)
    {
       printf("null pointer in server\n");
    }
    else
    {
     if(termData->transAmount>accountRefrence->balance)
        return LOW_BALANCE;
     else
        return SERVER_OK;
  }
}


EN_serverError_t saveTransaction(ST_transaction_t *transData ){
    if(transData==NULL)
        {
          printf("null pointer in server\n");
        }
        else
        {

  transData->transactionSequenceNumber= (transactions[transnumber-1].transactionSequenceNumber)+1;
 transactions[transnumber]=*transData;
 update_transactions();
 return SERVER_OK;
        }

}
