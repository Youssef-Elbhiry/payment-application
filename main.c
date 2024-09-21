#include <stdio.h>
#include <stdlib.h>


#include"system\Application\app.h"


int main()
{

     int c;

     while(1)
     {
         printf("Enter your choice\n");
         printf("1) Withdraw money\n");
         printf("2) Deposit money\n");
         printf("3) Balance inquiry\n");
         printf("4) Transfer money from one account to another\n");
         printf("5) Exit\n");
         scanf("%d",&c);

printf("---------------------------------------------\n");
         switch(c)
         {
            case 1:
                Withdraw_money();
            break;
             case 2:
                 Deposit_money();
            break;
             case 3:
                 Inquire_money();
            break;
             case 4:
                 Transfer_money();
            break;
             case 5:
                 exit(0);
            break;
             default:
                printf("wrong choice!\n");
                break;
         }
     }







}
