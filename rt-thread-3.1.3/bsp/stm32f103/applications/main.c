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

#include <os.h>

void timer_example (void);

OS_STK task_stack [256];
void   task(void *p_arg)
{
    while(1)
    {
//        rt_kprintf("hahha");
        rt_thread_delay(500);
    }
}

int main(void)/*RT-Thread main�߳�*/
{
    OSInit();
    
    OSStart();
    
    timer_example();
    OSTaskCreateExt(task,0,task_stack,5,0,0,256,0,0);
}
