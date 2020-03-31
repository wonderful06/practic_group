//#include<stdio.h>
#include<stdlib.h>
#include <rt_misc.h>


#define Shipment 6  //出货口定义为6个

typedef struct node
{
    uint16_t number;        
    uint16_t flag;          
    int32_t act_weight;     
    struct node *next;       
}linklist,*linklist_p;


typedef struct          
{
	int32_t goal_weight;        
	int32_t dev_weight;       
    int32_t max_pack_weight;    
    int32_t min_pack_weight;   
}PACK;

PACK   aPACK;


linklist_p list_creat()  //创建链表
{
    linklist_p List = NULL;
    List = (linklist_p)malloc(sizeof(linklist));
    if(NULL == List)
    {
        return NULL;
    
    }
    List->next = NULL;
    List->number = 0;
    List->flag = 0;
    List->act_weight = 0;
    return List;
}


int32_t init_insert(linklist_p List,int32_t box_number) //创建并初始化链表节点
{ 
    linklist_p p = NULL;
    if((p=(linklist_p)malloc(sizeof(linklist))) == NULL)
    {
        return -1;
    }
    p->number = box_number;
    p->act_weight = 0;
    p->flag = 0;
    p->next = List->next;
    List->next = p;
    return 0;
}


int32_t enter_data(linklist_p List,int32_t value)  //写入数据
{
    linklist_p p = List;
    while(1)
    {
        if(p->flag==0)
        {
            if((p->act_weight + value) < (aPACK.goal_weight + aPACK.dev_weight - aPACK.min_pack_weight)) //如果加入数据后小于目标值减最小重量
            {
                p->act_weight += value;
                break;
               
            }
            else if((p->act_weight + value < aPACK.goal_weight + aPACK.dev_weight)&&(p->act_weight + value> aPACK.goal_weight-aPACK.dev_weight))
            {
                p->act_weight += value;
                p->flag = 1;
                break;
            }
            else
            {
                if(p->next == NULL)
                    return -1;
                p = p->next;
            }
        }
        else
        {
            if(p->next == NULL)
            {
                return -1;
            }
            else
               p = p->next;  
        }
    }
    return 0;
}

/********************                    测试代码                          ******************************/
int32_t rece_value(int32_t i)
{
    //测试

    int32_t a[20]={100,200,180,160,200,190,230,140,270,130,180,220,240,120,110,270,150,190,300,170};
    if(i == 20)
        a[i]= 0;
    
    
    return a[i];
}


int32_t operat()
{
    int32_t i;
    int32_t a;
    int32_t j= 0;  //测试
    linklist_p List=NULL;
    if((List = list_creat())==NULL)
    {
        return -1;
    }
    for(i =0;i<Shipment-1;i++)
    {
        init_insert(List,Shipment-i-1);    
    }
    while(1)
    {
        if((a = rece_value(j))!= 0)
        {
            if(enter_data(List,a)== -1)
            {
                return -1;  
            }
            j++;    //测试
        }
        else 
            break;
    }
    return 0;
}


int main (void)
{
    aPACK.goal_weight = 1000;        //目标重量
	aPACK.dev_weight = 50;         //偏差值
    aPACK.max_pack_weight = 300;    //每包最大重量
    aPACK.min_pack_weight = 100;    //每包最小重量
    operat();


    return 0;
}




