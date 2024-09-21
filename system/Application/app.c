#include"app.h"
list_t list;

  void getcard_data(ST_cardData_t *pc) {
fflush(stdin);

   while (getCardHolderName(pc) == WRONG_NAME)
   {
    printf("Wrong name enter correct one (from 20 to 24 characters)!\n");
   }
 while (getCardPAN(pc) == WRONG_PAN)
   {
    printf("Wrong PAN enter correct one (from 16 to 19 digits)!\n");
   }
    while (getCardExpiryDate(pc)== WRONG_EXP_DATE)
   {
     printf("Wrong expiry date enter correct one (MM/YY)!\n");
   }

}


 void Withdraw_money()
 {

     creat_list(&list);
     upload_accounts(&list);
     upload_transactions();
 ST_transaction_t st_transaction;
 EN_transState_t transst;
   getcard_data(&st_transaction.cardHolderData);
    getTransactionDate(&st_transaction.terminalData);
 if( EXPIRED_CARD==isCardExpired(&st_transaction.cardHolderData,&st_transaction.terminalData))
 {
    printf("Expired card!!\n") ;

 }
 else
 {
while (getTransactionAmount(&st_transaction.terminalData)==INVALID_AMOUNT)
   {
      printf("enter valid amount!\n");
   }
      setMaxAmount(&st_transaction.terminalData,MAXAMOUNT);

  if(EXCEED_MAX_AMOUNT==isBelowMaxAmount(&st_transaction.terminalData))
  {
      printf("The amount you need exceed max amount!\n");

  }
  else
  {

  transst=recieveTransactionData(&st_transaction);
      if (transst == APPROVED) {
    printf("Your transaction has been processed.\n");
} else if (transst == FRAUD_CARD) {
    printf("Your transaction has failed, account not found.\n");
} else if (transst == DECLINED_INSUFFECIENT_FUND) {
    printf("Your transaction has failed due to insufficient funds.\n");
} else if (transst == DECLINED_STOLEN_CARD) {
    printf("Your transaction has failed, the card is reported as stolen.\n");
} else {
    printf("Your transaction has failed due to an internal error.\n");
}
  printf("---------------------------------------------\n");
  }
  }
  destroy(&list);
}

extern ST_accountsDB_t *ptacc;
 void Deposit_money()
 {
     creat_list(&list);
     upload_accounts(&list);
     upload_transactions();
     ST_transaction_t st_transaction;
   EN_transState_t transst;
   getcard_data(&st_transaction.cardHolderData);
   getTransactionDate(&st_transaction.terminalData);
 if( EXPIRED_CARD==isCardExpired(&st_transaction.cardHolderData,&st_transaction.terminalData))
 {
    printf("Expired card!!\n") ;

 }
 else
 {
      l:
  if(getTransactionAmount(&st_transaction.terminalData)==INVALID_AMOUNT)
  {
      printf("enter valid amount!\n");
      goto l;
  }
  setMaxAmount(&st_transaction.terminalData,MAXAMOUNT);
 if(ACCOUNT_NOT_FOUND==isValidAccount(&st_transaction.cardHolderData,&ptacc))
 {
   transst=FRAUD_CARD;
 }
 else
 {

 if(BLOCKED_ACCOUNT==isBlockedAccount(ptacc))
 {
   transst=DECLINED_STOLEN_CARD;
 }
 else
 {
     ptacc->balance+=st_transaction.terminalData.transAmount;
            transst=APPROVED;

 }
 }
    update_accounts(&list);
 st_transaction.transState=transst;
 saveTransaction(&st_transaction);

 }
 if(transst==APPROVED)
       printf("your transaction has been processed.\n") ;
    else
   printf("your transaction has failed.\n") ;
   printf("---------------------------------------------\n");
   destroy(&list);
 }
  void Inquire_money()
 {
      creat_list(&list);
     upload_accounts(&list);
     upload_transactions();
     ST_transaction_t st_transaction;
   getcard_data(&st_transaction.cardHolderData);
   getTransactionDate(&st_transaction.terminalData);
 if( EXPIRED_CARD==isCardExpired(&st_transaction.cardHolderData,&st_transaction.terminalData))
 {
    printf("Expired card!!\n") ;
 }
 else
 {

 if(ACCOUNT_NOT_FOUND==isValidAccount(&st_transaction.cardHolderData,&ptacc))
 {
   printf("Account not found!\n");
 }
 else
 {

 if(BLOCKED_ACCOUNT==isBlockedAccount(ptacc))
 {
    printf(" Your account is blocked!\n");
 }
 else
 {
     printf("Your balance is:%.2f\n ",ptacc->balance);
 }
 }
 }
     printf("---------------------------------------------\n");
     destroy(&list);
 }

 ST_accountsDB_t *ptacc1;


  void Transfer_money()
 {
     creat_list(&list);
     upload_accounts(&list);
     upload_transactions();
     ST_transaction_t st_transaction_1;
     ST_transaction_t st_transaction_2;
     EN_terminalError_t state;
   EN_transState_t transst_1;
   printf("enter account data to transfer from:\n");
   getcard_data(&st_transaction_1.cardHolderData);
    printf("enter account data to transfer to:\n");
   getcard_data(&st_transaction_2.cardHolderData);

   getTransactionDate(&st_transaction_1.terminalData);
   getTransactionDate(&st_transaction_2.terminalData);
   if( EXPIRED_CARD==isCardExpired(&st_transaction_1.cardHolderData,&st_transaction_1.terminalData)||EXPIRED_CARD==isCardExpired(&st_transaction_2.cardHolderData,&st_transaction_2.terminalData))
 {
    printf("Expired card!!\n") ;

 }
 else
 {

   if(ACCOUNT_NOT_FOUND==isValidAccount(&st_transaction_1.cardHolderData,&ptacc)||ACCOUNT_NOT_FOUND==isValidAccount(&st_transaction_2.cardHolderData,&ptacc1))
 {
    transst_1=FRAUD_CARD;
   printf("Account not found!\n");
 }
 else
 {
          l:
  if(getTransactionAmount(&st_transaction_1.terminalData)==INVALID_AMOUNT)
  {
      printf("enter valid amount!\n");
      goto l;
  }

           if( isAmountAvailable(&st_transaction_1.terminalData,ptacc)==LOW_BALANCE)
        {
            printf("you don't have this amount in your account!\n");
            transst_1= DECLINED_INSUFFECIENT_FUND;

        }
        else{

            if(BLOCKED_ACCOUNT==isBlockedAccount(ptacc)||BLOCKED_ACCOUNT==isBlockedAccount(ptacc1))
             {
                transst_1=DECLINED_STOLEN_CARD;
                 printf(" Blocked account!\n");
             }
            else
             {
               st_transaction_2.terminalData.transAmount=st_transaction_1.terminalData.transAmount;
                ptacc->balance-=st_transaction_1.terminalData.transAmount;
                ptacc1->balance+=st_transaction_1.terminalData.transAmount;
                 update_accounts(&list);
                transst_1=APPROVED;
             }
        }


 }

 st_transaction_1.transState=transst_1;
 st_transaction_2.transState=transst_1;
  saveTransaction(&st_transaction_1);
  saveTransaction(&st_transaction_2);
   if(transst_1==APPROVED)
       printf("your transaction has been processed.\n") ;

    else
   printf("your transaction has failed.\n") ;
 }
printf("---------------------------------------------\n");
destroy(&list);
 }
