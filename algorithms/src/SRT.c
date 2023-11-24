
#include "main.h"  

void insertInPosition(struct node *head, struct node *newNode, int finish){
   struct node *tmp = head->next;
   struct node *prev = head;
   if(head == NULL){
      head = newNode;
      return;
   }
   while(tmp &&
          atoi(newNode->data[2]) >= atoi(tmp->data[2]) &&
          atoi(tmp->data[1]) <= finish){
      prev = prev->next;
      tmp = tmp->next;
   }
   newNode->next = tmp;
   prev->next = newNode;
}


void SRTFPreemptive(struct node *head){
   struct node *tmp = head;
   int finish = atoi(tmp->data[1]);
   while(tmp){
      struct node *tmp2 = tmp->next;
      while(tmp2){
         int ta = atoi(tmp->data[1]);
         int idle = ta > finish ? ta-finish : 0;
         int diffta = atoi(tmp2->data[1]) - (finish+idle);
         diffta = diffta < 0 ? 0 : diffta;
         bool condition = atoi(tmp2->data[2]) < atoi(tmp->data[2])-diffta;
         if(diffta == 0 && condition)
            swap(tmp, tmp2);
         else if(condition){
            struct node *remainderNode = newNode(tmp);
            sprintf(remainderNode->data[2], "%d", (atoi(tmp->data[2])-diffta));
            sprintf(tmp->data[2], "%d", diffta);
            swap(tmp->next, tmp2);
            insertInPosition(tmp, remainderNode, finish+idle);
            break;
         }
         tmp2 = tmp2->next;
      }
      int ta = atoi(tmp->data[1]);
      int idle = ta > finish ? ta-finish : 0;
      finish += atoi(tmp->data[2]) + idle;
      tmp = tmp->next;
   }
}


void SRT(char configFile[]){
   struct node *processesList = getProcessesListFromFile(configFile);
   printProcessTable(processesList);
   bubbleSortByTwoIndexes(processesList, 1, 2, false); // Sort List by Ta & Te to get First process to run
   SRTFPreemptive(processesList);
   addIdleNodes(processesList);
   printGanttChart(processesList, "SRT");
}


int main(int argc, char *argv[]) {
   if(argc == 1)
      printf("Usage: %s <config>\n", argv[0]);
   else
      SRT(argv[1]);
   return 0;
}
