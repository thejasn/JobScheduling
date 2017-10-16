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
    //printf("\n Enter burst time and arrival time:");
    for(i=0;i<size;i++)
    {   
        list[i] = (PROCESS*)calloc(1,sizeof(PROCESS));
        list[i]->burst_t = rand() % 32000;
        list[i]->arr_t = rand() % 32000;
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

long least_burst(PROCESS **list,long till,long size,long start)
{
   
    list[size-1] = (PROCESS*)calloc(1,sizeof(PROCESS));
    list[size-1]->burst_t=999999;
    long least = size-1;
    
    long i;
    for(i=start;i<size;i++)
    {
       
        if(list[i]->arr_t <= till && list[i]->burst_t < list[least]->burst_t && list[i]->burst_t > 0)
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
        long until = least_burst(list,count_timer,size+1,start);
       
        list[until]->burst_t--;
       
        if ( list[until]->burst_t == 0)
        {  
            num++;
            end = count_timer+1;  
            avgt += ((double)(end - list[until]->arr_t) / (double)size);
            avgw += ((double)((end - list[until]->arr_t) - list[until]->bt) / (double)size);
            temp = list[start];
            list[start]=list[until];
            list[until]=temp;
            start++;
        }
     
    }
}

int main(int argc,char * argv[])
{
    srand(time(NULL));
    long size=100,i,j;
    clock_t start,end;
    i = atoi(argv[1]);
    //printf("%ld",i);
    
    //:fflush(stdout);
    //scanf("%ld", &i);
    //PROCESS list[100];
    //`sort_arr(list,size,0,size-1);
    //for(i=10;i<size;i+=50)
    {
        PROCESS ** list = (PROCESS**)calloc(i+1,sizeof(PROCESS));
        if(list==NULL)
        {
            printf("\n ASFDASFDASD");
        }
        avgt=avgw=0;
        getData(list,i);
        start = clock();
        SJF(list,i);
        end = clock();
        printf("\n %lf : %lf",avgt,avgw);
        //printf("\n  %ld : %lf",i,(double)(end-start)/CLOCKS_PER_SEC);
        fflush(stdout);
        for(j=0;j<i;j++)
            free(list[j]);
        free(list);
    }
    //show_data(list,size);
    //long i=0;
    
    return 0;
};
