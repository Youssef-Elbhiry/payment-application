#include<string.h>
#include"card.h"
EN_cardError_t getCardHolderName(ST_cardData_t *cardData){

    if(NULL==cardData)
    {
        printf("null pointer in card\n");

    }
    else
    {
         EN_cardError_t state=CARD_OK;
 printf("->enter cardholder name:");
 gets(cardData->cardHolderName);
 if(strlen(cardData->cardHolderName)==NULL||strlen(cardData->cardHolderName)<20||strlen(cardData->cardHolderName)>24)
    state=WRONG_NAME;
return state;
    }



}
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData){
    if(NULL==cardData)
    {
        printf("null pointer in card\n");
    }
    else
    {
     EN_cardError_t state=CARD_OK;
printf("->enter card expiry date: ");
gets(cardData->cardExpirationDate);
 if(strlen(cardData->cardExpirationDate)==NULL||strlen(cardData->cardExpirationDate)!=5)
 {
   state=WRONG_EXP_DATE;

 }
 else{
   for(int i=0;i<5;i++)
   {
      if(i==2)
       {
           if(cardData->cardExpirationDate[2]!='/')
           {
               state=WRONG_EXP_DATE;
         break;
           }

       }
       else if(!(cardData->cardExpirationDate[i]>='0'&&cardData->cardExpirationDate[i]<='9') )
       {

            state=WRONG_EXP_DATE;
         break;

       }
   }
 }
return state;
    }


}
EN_cardError_t getCardPAN(ST_cardData_t *cardData){
    if(NULL==cardData)
    {
        printf("null pointer in card\n");
    }
    else
    {
      EN_cardError_t state=CARD_OK;
  printf("->enter your PAN:");
   gets(cardData->primaryAccountNumber);
if(strlen(cardData->primaryAccountNumber)==NULL||strlen(cardData->primaryAccountNumber)<16||strlen(cardData->primaryAccountNumber)>19)
   state= WRONG_PAN;
return state;
    }


}
