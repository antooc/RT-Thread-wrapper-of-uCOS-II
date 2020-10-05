/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-09-17     Meco Man     first version
 */

/*���ļ�չʾ�˼��ݲ�ʵ�ֵ�uCOS-II�ٷ������ı�׼��ʼ������*/
/*�����Լ���ʼ�������ϸ����չٷ�����������*/
/*����ʹ��USART2*/

#include <ucos_ii.h>

void task_example (void);
void timer_example (void);



int main(void)/*RT-Thread main�߳�*/
{
    OSInit();    
    OSStart();
    OSStatInit();
    
    task_example();
//    timer_example();
    
    while(1)
    {
        
        rt_thread_delay(100);
    }
    
}
