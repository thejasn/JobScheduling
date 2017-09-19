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
        list[i]->touched=0;
       

    }
}
void sort_busrt(PROCESS **list, int size,int start,int end)
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
}
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
    //printf("helo");
    int j;
    //for(j=0;j<size;j++)
      //  printf("\n%d",list[j]->p_id);
    int i=1,pos=0,max=9999;
    while(list[i]->arr_t <= till && i < size)
    {   // printf("\n%d",till);
        if(list[i]->burst_t > 0)
        {   
            if(list[i]->burst_t <= list[pos]->burst_t )//&& list[i]->p_id != list[pos]->p_id)
            {    
               pos = i;
               
               //break;
               //printf("\np%d",pos);
               fflush(stdout);
               break;
            }


        }
        i++;
      //  printf("\ni%d",i);
        //fflush(stdout);
    }
    printf("\np%d",pos);
    fflush(stdout);
    if(i == size)
        return 0;
    return pos;        
}
void SJF(PROCESS ** list,int size)
{
   // printf("helo");
   int max; 
    int count_timer=0;
    do{
        //printf("\nhel");
        int until = least_burst(list,count_timer,size);
       printf("\nu%d",until);
       fflush(stdout); 
       //printf("\nhello");
        if(!list[until]->touched)
        {   list[until]->touched=1;       
            list[until]->start=count_timer;
            //max = list[until]->burst_t;
        }
        list[until]->burst_t--;
        //list[until]->turn_t=list[until]->turn_t+1;
        //printf("\nhello");
        if ( list[until]->burst_t == 0)
        {           
            list[until]->turn_t = (count_timer - list[until]->arr_t + 1);
            printf("\n%d",list[until]->turn_t);
             

        }
        //printf("\nhello");
        count_timer++;
       // printf("\nhello");
        printf("\nc%d",count_timer);
        fflush(stdout);
    }while(count_timer < 19);
}
int main()
{
    int size;
    scanf("%d", &size);
    PROCESS ** list = (PROCESS**)calloc(size,sizeof(PROCESS));
    //PROCESS list[100];
    getData(list,size);
    sort_arr(list,size,0,size-1);
    SJF(list,size);
    show_data(list,size);
    return 0;
}