/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-07-12     Meco Man     the first verion
 */
 
#include "ucos_ii.h"
#include <string.h>
#include <rthw.h>

/**
 * �õ�������һ����������ȴ�IPC,�������̬(��rt_ipc_list_resume�����ı�)
 *
 * @param ������ͷָ��
 *
 * @return ������
 */
rt_err_t rt_ipc_pend_abort_1 (rt_list_t *list)
{
    struct rt_thread *thread;
    register rt_ubase_t temp;
    OS_TCB  *p_tcb;
    
    temp = rt_hw_interrupt_disable();
    /* get thread entry */
    thread = rt_list_entry(list->next, struct rt_thread, tlist);
    p_tcb = (OS_TCB*)thread;
    /* set error code to RT_ERROR */
    thread->error = -RT_ERROR;
    
    /*��ǵ�ǰ��������ȴ�*/
    p_tcb->OSTCBStatPend = OS_STAT_PEND_ABORT; 
    
    rt_hw_interrupt_enable(temp);
    
    /* resume it */
    rt_thread_resume(thread); 

    return RT_EOK;
}

/**
 * �����еȴ���IPC������ȫ�������ȴ����������̬(��rt_ipc_list_resume_all�����ı�)
 *
 * @param ������ͷָ��
 *
 * @return �����˶��ٸ�����
 */
rt_uint16_t rt_ipc_pend_abort_all (rt_list_t *list)
{
    struct rt_thread *thread;
    register rt_ubase_t temp;
    OS_TCB *p_tcb;
    rt_uint16_t i=0;

    /* wakeup all suspend threads */
    while (!rt_list_isempty(list))
    {
        /* disable interrupt */
        temp = rt_hw_interrupt_disable();

        /* get next suspend thread */
        thread = rt_list_entry(list->next, struct rt_thread, tlist);
        p_tcb = ((OS_TCB*)thread);
        /* set error code to RT_ERROR */
        thread->error = -RT_ERROR;
                
        /*��ǵ�ǰ��������ȴ�*/
        p_tcb->OSTCBStatPend = OS_STAT_PEND_ABORT;
        
        /*
         * resume thread
         * In rt_thread_resume function, it will remove current thread from
         * suspend list
         */
        rt_thread_resume(thread);

        /* enable interrupt */
        rt_hw_interrupt_enable(temp);
        
        i++;
    }

    return i;
}


/**
 * �Զ���ʼ��
 * uCOS-II���ݲ�֧�ְ���uCOS-IIԭ��ĳ�ʼ��������г�ʼ������������Щ�����
 * �û������ֶ���ʼ��uCOS-II���ݲ㣬��Ҫֱ������Ӧ�ò������ģ�飬�����ʹ�ø�
 * �궨�塣��rtconfig.h�ж��屾�궨�����RT-Thread��ʼ����ɲ����뵽main�߳�֮ǰ
 * ���Զ���uCOS-II���ݲ��ʼ����ϣ��û�����Ҫרע��uCOS-II��Ӧ�ü����񼴿ɡ�
 * The wrapper supports uCOS-II standard startup procedure. Alternatively,
 * if you want to run uCOS-II apps directly and ignore the startup procedure, 
 * you can choose this option.
 */
#ifdef PKG_USING_UCOSII_WRAPPER_AUTOINIT
static int rt_ucosii_autoinit(void)
{
    OSInit();                                       /*uCOS-II����ϵͳ��ʼ��*/
    OSStart();                                      /*��ʼ����uCOS-II����ϵͳ*/

#if OS_TASK_STAT_EN > 0u
    OSStatInit();
#endif
    return 0;
}
INIT_COMPONENT_EXPORT(rt_ucosii_autoinit);
#endif
