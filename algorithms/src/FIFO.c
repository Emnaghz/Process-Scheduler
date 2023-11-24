#include "main.h"

void fifo(char *processesFile){
   struct node *processesList = getProcessesListFromFile(processesFile);
   printProcessTable(processesList);
   bubbleSort(processesList, 1); // Asc Sort List Based On TA 
   addIdleNodes(processesList);
   printGanttChart(processesList, "FIFO");
}  

int main(int argc, char *argv[]) {
   fifo(argv[1]);
   return 0;
}
