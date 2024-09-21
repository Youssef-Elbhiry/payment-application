#include"../../Payment_system\Server\server.h"
#include"file_handling.h"

void upload_accounts(list_t *l)
{
    int i=0;
    ST_accountsDB_t temp;
    char arr[20];
    FILE *f;
    f=fopen("C:\\Users\\GHONIM\\OneDrive\\Desktop\\payment_application\\system\\Data_Bases\\Data\\accountsdata.txt","r");
    if(f)
    {
     while( fscanf(f,"%f",&temp.balance)==1)
    {
        fscanf(f,"%d",&temp.state);
         fscanf(f,"%s",temp.primaryAccountNumber);
         insecert(i++,temp,l);
        fscanf(f,"%s",arr);
    }

    }
    else
    {
        printf("can't open the file1");
    }
    fclose(f);

}
void update_accounts(list_t *l)
{
int j=get_size(l);
    ST_accountsDB_t temp;
    char arr[20]="---------";
    FILE *f;
    f=fopen("C:\\Users\\GHONIM\\OneDrive\\Desktop\\payment_application\\system\\Data_Bases\\Data\\accountsdata.txt","w");

    if(f)
    {
    for( int i=0;i<j;i++)
    {
     delete_node(0,&temp,l) ;
     fprintf(f,"%f\n",temp.balance);
     fprintf(f,"%i\n",temp.state);
     fprintf(f,"%s\n",temp.primaryAccountNumber);
     fprintf(f,"%s\n",arr);

    }


}
 else
    {
        printf("can't open the file1 to update");
    }
    fclose(f);
}


void upload_transactions()
{  transnumber=0;
   ST_transaction_t s;
   char arr[20];
    FILE *f2;
     f2=fopen("C:\\Users\\GHONIM\\OneDrive\\Desktop\\payment_application\\system\\Data_Bases\\Data\\transdata.txt ","r");
     if(f2)
    {
     while( fgets(s.cardHolderData.cardHolderName,25,f2)!=NULL)
    {

        fscanf(f2,"%s",s.cardHolderData.primaryAccountNumber);

        fscanf(f2,"%s",s.cardHolderData.cardExpirationDate);

        fscanf(f2,"%f",&s.terminalData.transAmount);

        fscanf(f2,"%f",&s.terminalData.maxTransAmount);

        fscanf(f2,"%s",s.terminalData.transactionDate);

        fscanf(f2,"%d",&s.transState);
        fscanf(f2,"%d",&s.transactionSequenceNumber);
        fscanf(f2,"%s",arr);
         fgets(arr,25,f2);
         transactions[transnumber++]=s;


    }

    }
    else
    {
        printf("can't open the file2");
    }
    fclose(f2);
}
void update_transactions()
{

   FILE *f2;
     f2=fopen("C:\\Users\\GHONIM\\OneDrive\\Desktop\\payment_application\\system\\Data_Bases\\Data\\transdata.txt","a");
     if(f2)
    {

   fprintf(f2,"%s\n",transactions[transnumber].cardHolderData.cardHolderName);
   fprintf(f2,"%s\n",transactions[transnumber].cardHolderData.primaryAccountNumber);
   fprintf(f2,"%s\n",transactions[transnumber].cardHolderData.cardExpirationDate);
   fprintf(f2,"%.2f\n",transactions[transnumber].terminalData.transAmount);
   fprintf(f2,"%.2f\n",transactions[transnumber].terminalData.maxTransAmount);
   fprintf(f2,"%s\n",transactions[transnumber].terminalData.transactionDate);
   fprintf(f2,"%i\n",transactions[transnumber].transState);
   fprintf(f2,"%i\n",transactions[transnumber].transactionSequenceNumber);
   fprintf(f2,"--------------------\n");


    }
fclose(f2);

}
