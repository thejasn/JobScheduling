#include <stdio.h>
#include <stdlib.h>
#include <time.h>
struct P
{
    long wait_t,burst_t,arr_t,turn_t;
    long p_id,bt;
};
double avgt=0,avgw=0;
typedef struct P PROCESS;
void getData(PROCESS **list,long size)
{
    long i;
    printf("\n Enter burst time and arrival time:");
    for(i=0;i<size;i++)
    {   
        list[i] = (PROCESS*)calloc(1,sizeof(PROCESS));
        if( list[i] == NULL)
            printf("asdasd");
        //scanf("%d%d",&list[i]->burst_t,&list[i]->arr_t);
        list[i]->burst_t = rand() % 32000;
        list[i]->arr_t = rand() % 32000;
        list[i]->p_id = i;
        list[i]->bt=list[i]->burst_t;
    }
    
}
/*void sort_busrt(PROCESS **list, int size,int start,int end)
{
    PROCESS *temp;
    int i,j;
    for(i=0;i<end-start+1;i++)
        for(j=start;j<end;j++)
            if(list[j]->burst_t > list[j+1]->burst_t)
            {
                temp = list[j];
                list[j] = list[j+1];
                list[j+1] = temp;
            }
}*/
void sort_arr(PROCESS **list, long size,long start,long end)
{
   // printf("helo");
    PROCESS *temp;
    long i,j;
    for(i=0;i<size;i++)
        for(j=start;j<size-i-1;j++)
            if(list[j]->arr_t > list[j+1]->arr_t)
            {
                temp = list[j];
                list[j] = list[j+1];
                list[j+1] = temp;
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

long least_burst(PROCESS **list,long till,long size)
{
   
    list[size-1] = (PROCESS*)calloc(1,sizeof(PROCESS));
    list[size-1]->burst_t=999999;
    long least = size-1;
    
    long i;
    for(i=0;i<size;i++)
    {
        if(list[i]->burst_t == 0)
            continue;
        if(list[i]->arr_t <= till && list[i]->burst_t < list[least]->burst_t && list[i]->burst_t > 0)
        {
            least = i;
        }
    }
    return least;
}
void SJF(PROCESS ** list,long size)
{
    long count_timer=0,end,num=0;
    for(count_timer=0; num != size ; count_timer++){
        long until = least_burst(list,count_timer,size+1);
       
        list[until]->burst_t--;
       
        if ( list[until]->burst_t == 0)
        {  
            num++;
            //count_timer++; 
            end = count_timer+1;  
                  
           //list[until]->turn_t = (end - list[until]->arr_t );
            //list[until]->wait_t = 
            avgt += ((double)(end - list[until]->arr_t) / (double)size);
            avgw += ((double)((end - list[until]->arr_t) - list[until]->bt) / (double)size);
            //printf("\n%ld,%ld",list[until]->turn_t,list[until]->wait_t);
        }
     
    }
}

int main()
{
    srand(time(NULL));
    long size;
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
    show_data(list,size);
    long i=0;
    printf("\n turn = %lf \t wait = %lf",avgt,avgw);
    printf("\n Processing rate : %lf",(double)(end-start)/CLOCKS_PER_SEC);
    for(i=0;i<size;i++)
        free(list[i]);
    free(list);
    return 0;
};