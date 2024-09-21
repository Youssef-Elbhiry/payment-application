
#include"list.h"

void creat_list(list_t *pl){
pl->listhead=NULL;
pl->size=0;

}
int is_empty(list_t *pl){
return !(pl->listhead);
}

int is_full(list_t *pl){
return 0;
}

void insecert(int pos,entry item,list_t *pl){
listnode *temp,*pn;
int i=0;
if(pn=(listnode *)malloc(sizeof(listnode)))
{
pn->data=item;
//pn->next=NULL;
if(pos==0)
{
pn->next=pl->listhead;
pl->listhead=pn;
}
else
{
for(temp=pl->listhead;i<pos-1;i++)
{
    temp=temp->next;
}
pn->next=temp->next;
temp->next=pn;
}
(pl->size)++;
}
else
    printf("error in insecertion!\n");
}

void delete_node(int pos,entry *item,list_t *pl){

listnode *temp=pl->listhead,*ptd;
if(pos<pl->size&&pos>=0)
{

if(pos==0)
{
  *item=pl->listhead->data;
  pl->listhead=pl->listhead->next;
  free(temp);
}
else
{
 for(int i=0;i<pos-1;i++)
 {
     temp=temp->next;
 }
 ptd=temp->next;
 *item=ptd->data;
 temp->next=ptd->next;
 free(ptd);
}
(pl->size)--;

}
else
   printf("invalid position!\n");

}
int get_size(list_t *pl){
return pl->size;

}
void destroy(list_t *pl){

listnode *ptd=pl->listhead;
 while(ptd)
 {
     pl->listhead=ptd->next;
     free(ptd);
     ptd=pl->listhead;
 }
 pl->size=0;

}
