#ifndef APP_H
#define APP_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"../Payment_system/Server/server.h"
#include"../Data_structures/list.h"
#include"../Data_Bases/File_Handling/file_handling.h"
#define MAXAMOUNT 1000
  extern ST_accountsDB_t *ptacc;
   void getcard_data(ST_cardData_t *pc);
   void Withdraw_money();
   void Deposit_money();
   void Inquire_money();
   void Transfer_money();
#endif
