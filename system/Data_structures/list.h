#ifndef LIST_H
#define LIST_H
#include <stdlib.h>
#include <stdio.h>
//#include"C:\Users\GHONIM\OneDrive\Desktop\payment_application\system\Payment_system\Server\server.h"
#include"../Payment_system/Server/server.h"

typedef ST_accountsDB_t entry;
 typedef struct node {
 entry data;
 struct node *next;


 }listnode;

 typedef struct {
 listnode *listhead;
 int size;

 }list_t;

void creat_list(list_t *pl);
int is_empty(list_t *pl);
int is_full(list_t *pl);
void insecert(int pos,entry item,list_t *pl);
void delete_node(int pos,entry *item,list_t *pl);
int get_size(list_t *pl);
void destroy(list_t *pl);



#endif // LIST_H
