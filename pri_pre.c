#include <stdio.h>
#include <stdlib.h>
#include <time.h>
struct P
{
    long wait_t,burst_t,arr_t,turn_t;
    long p_id,bt,priority;
};
double avgt=0,avgw=0;
typedef struct P PROCESS;
void getData(PROCESS **list,long size)
{
    long i;
    printf("\n Enter burst time and arrival time and priority:");
    for(i=0;i<size;i++)
    {   
        list[i] = (PROCESS*)calloc(1,sizeof(PROCESS));
        scanf("%ld%ld%ld",&list[i]->burst_t,&list[i]->arr_t,&list[i]->priority);
       //list[i]->burst_t = rand() % 32000;
        //list[i]->arr_t = rand() % 32000;
        list[i]->p_id = i;
        list[i]->bt=list[i]->burst_t;
    }
}
void show_data(PROCESS  **list, long size)
{
    long i;
    for(i=0;i<size;i++)
    {
        printf("\n %ld - %ld,%ld,%ld,%ld ",list[i]->p_id,list[i]->bt,list[i]->arr_t,list[i]->turn_t,list[i]->wait_t);
    }
}

long least_pri(PROCESS **list,long till,long size,long start)
{
   
    list[size-1] = (PROCESS*)calloc(1,sizeof(PROCESS));
    list[size-1]->priority=999999;
    long least = size-1;
    
    long i;
    for(i=start;i<size;i++)
    {
       
        if(list[i]->arr_t <= till && list[i]->priority < list[least]->priority && list[i]->burst_t > 0)
        {
            least = i;
        }
    }
    return least;
}
void SJF(PROCESS ** list,long size)
{
    long count_timer=0,start=0,num=0,end;
    PROCESS * temp;
    for(count_timer=0; num != size ; count_timer++){
        long until = least_pri(list,count_timer,size+1,start);
       
        list[until]->burst_t--;
       
        if ( list[until]->burst_t == 0)
        {  
            num++;
            end = count_timer+1;
            list[until]->turn_t = end - list[until]->arr_t; 
            //printf("%ld",list[until]->p_id); 
            printf("\n %ld - %ld,%ld,%ld,%ld ",list[until]->p_id,list[until]->bt,list[until]->arr_t,list[until]->turn_t,list[until]->wait_t);
            avgt += ((double)(end - list[until]->arr_t) / (double)size);
            avgw += ((double)((end - list[until]->arr_t) - list[until]->bt) / (double)size);
            /*temp = list[start];
            list[start]=list[until];
            list[until]=temp;
            start++;*/
        }
     
    }
}

int main()
{
    srand(time(NULL));
    long size=100;
    clock_t start,end;
    scanf("%ld", &size);
    PROCESS ** list = (PROCESS**)calloc(size+1,sizeof(PROCESS));
    if(list==NULL)
    {
       printf("\n ASFDASFDASD");
    }
    //PROCESS list[100];
    getData(list,size);
    //`sort_arr(list,size,0,size-1);
    start = clock();
    SJF(list,size);
    end = clock();
    //show_data(list,size);
    long i=0;
    printf("\n turn = %lf \t wait = %lf",avgt,avgw);
    printf("\n Processing rate : %lf",(double)(end-start)/CLOCKS_PER_SEC);
    for(i=0;i<size;i++)
        free(list[i]);
    free(list);
    return 0;
};