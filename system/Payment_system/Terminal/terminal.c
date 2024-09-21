#include "terminal.h"
EN_terminalError_t getTransactionDate(ST_terminalData_t *termData){
    if(NULL==termData)
    {
         printf("null pointer in terminal\n");

    }
    else
     {
       time_t t=time(NULL);
    struct tm *date=localtime(&t);
    strftime(termData->transactionDate,11,"%d/%m/20%y",date);
    return TERMINAL_OK;
     }



}

EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData){
     if(NULL==termData||NULL==cardData)
    {
        printf("null pointer in terminal\n");
    }
    else
    {
     EN_terminalError_t state=TERMINAL_OK;

     char exp_y[3];
     char exp_m[3];
     char tra_y[2];
     char tra_m[2];
     strcpy(exp_y,&cardData->cardExpirationDate[3]);
     strcpy(tra_y,&termData->transactionDate[8]);

     int check=strcmp(tra_y,exp_y);
      if(check<0)
        {
          state=TERMINAL_OK;
        }
      else if(check>0)
       {
        state=EXPIRED_CARD;
       }
       else
        {
           strncpy(exp_m,&cardData->cardExpirationDate[0],2);
           strncpy(tra_m,&termData->transactionDate[3],2);
           check=strcmp(tra_m,exp_m);
            if(check<0)
           {
          state=TERMINAL_OK;
          }
          else if(check>=0)
          {
          state=EXPIRED_CARD;
          }
        }
        return state;
    }



}

EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData){
     if(NULL==termData)
    {
        printf("null pointer in terminal\n");
    }
    else
    {
     EN_terminalError_t state=TERMINAL_OK;
printf("enter transAmount:");
scanf("%f",&termData->transAmount);
if(termData->transAmount<=0)
   state=INVALID_AMOUNT;
return state;
}
    }


EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData){
    if(NULL==termData)
    {
        printf("null pointer in terminal\n");
    }
    else
    {
EN_terminalError_t state=TERMINAL_OK;
if(termData->maxTransAmount<termData->transAmount)
    state=EXCEED_MAX_AMOUNT;

return state;

}
}

EN_terminalError_t setMaxAmount(ST_terminalData_t *termData, float maxAmount){
     if(NULL==termData)
    {
        printf("null pointer in terminal\n");
    }
    else
    {
      EN_terminalError_t state=TERMINAL_OK;
if(maxAmount<=0)
{
  state=INVALID_MAX_AMOUNT;

}
else{

  termData->maxTransAmount=  maxAmount;

}
return state;
    }



}
EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData){
     if(NULL==cardData)
    {
        printf("null pointer in terminal\n");
    }
    else
    {
         EN_terminalError_t state=TERMINAL_OK;
char ptr[20];
int checksum,temp=0,s1=0,s2=0;
int len=strlen(cardData->primaryAccountNumber);
 strcpy(ptr,cardData->primaryAccountNumber);
 checksum=ptr[len-1];
 ptr[len-1]='\0';
 for(int i=strlen(ptr)-1,rank=2;i>=0;i--,rank++)
 {
     if(rank%2==0)
     {
       temp=2*ptr[i];
       if(temp>=10)
       {
          s1+=temp%10;
          s1+=temp/10;
          ptr[i]=s1;
       }

     }
     s2+=ptr[i];
 }
 if(checksum!=s2)
 {
    state=INVALID_CARD;
 }
    }


}
