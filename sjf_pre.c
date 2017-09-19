#include <stdio.h>
#include <stdlib.h>
#include <time.h>
struct P
{
    int wait_t,burst_t,arr_t,turn_t;
    int p_id,touched,start;
};
typedef struct P PROCESS;
void getData(PROCESS **list,int size)
{
    int i;
    printf("\n Enter burst time and arrival time:");
    for(i=0;i<size;i++)
    {   
        list[i] = (PROCESS*)calloc(1,sizeof(PROCESS));
        scanf("%d%d",&list[i]->burst_t,&list[i]->arr_t);
        list[i]->p_id = i;

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
}
void sort_arr(PROCESS **list, int size,int start,int end)
{
   // printf("helo");
    PROCESS *temp;
    int i,j;
    for(i=0;i<size;i++)
        for(j=start;j<size-i-1;j++)
            if(list[j]->arr_t > list[j+1]->arr_t)
            {
                temp = list[j];
                list[j] = list[j+1];
                list[j+1] = temp;
            }
}*/
void show_data(PROCESS  **list, int size)
{
    int i;
    for(i=0;i<size;i++)
    {
        printf("\n %d - %d,%d ",list[i]->p_id,list[i]->turn_t,list[i]->arr_t);
        
    }
}

int least_burst(PROCESS **list,int till,int size)
{
   
    list[size-1] = (PROCESS*)calloc(1,sizeof(PROCESS));
    list[size-1]->burst_t=99999;
    int least = size-1;
    
    int i;
    for(i=0;i<size;i++)
    {
        if(list[i]->arr_t <= till && list[i]->burst_t < list[least]->burst_t && list[i]->burst_t > 0)
        {
            least = i;
        }
    }
    return least;
}
void SJF(PROCESS ** list,int size)
{
    int count_timer=0,end,num=0;
    for(count_timer=0; num != size ; count_timer++){
        int until = least_burst(list,count_timer,size+1);
       
        list[until]->burst_t--;
       
        if ( list[until]->burst_t == 0)
        {  
            num++;
            //count_timer++; 
            end = count_timer+1;        
            list[until]->turn_t = (end - list[until]->arr_t );
            printf("\n%d,%d",list[until]->turn_t,end);
        }
     
    }
}
int main()
{
    int size;
    scanf("%d", &size);
    PROCESS ** list = (PROCESS**)calloc(size+1,sizeof(PROCESS));
    //PROCESS list[100];
    getData(list,size);
    //sort_arr(list,size,0,size-1);
    SJF(list,size);
    show_data(list,size);
    return 0;
}