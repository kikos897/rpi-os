#ifndef _SCHED_H
#define _SCHED_H

#define THREAD_CPU_CONTEXT	0	//offset of cpu_context in task_struct

#ifndef __ASSEMBLER__

#define THREAD_SIZE	4096

#define NR_TASKS	64

#define TASK_RUNNING	0

extern struct task_struct *current;
extern struct task_struct * task[NR_TASKS];
extern int nr_tasks;

struct cpu_context
{
	unsigned long x19;
	unsigned long x20;
	unsigned long x21;
	unsigned long x22;
	unsigned long x23;
	unsigned long x24;
	unsigned long x25;
	unsigned long x26;
	unsigned long x27;
	unsigned long x28;
	unsigned long fp;
	unsigned long sp;
	unsigned long pc;
};


struct task_struct
{
	struct cpu_context cpu_context;
	long state;
	long counter;
	long priority;
	long preempt_count;
};

extern void preempt_disable();
extern void preempt_enable();
extern void schedule();
extern void schedule_tail();
extern void timer_tick();
extern void _schedule();
extern void switch_to(struct task_struct *next);
extern void cpu_switch_to(struct task_struct *prev,struct task_struct *next);

/*      cpu_context=x19 20 21 22 23 24 25 26 27 28 fp sp pc  state         c  p  prec      */
#define INIT_TASK { {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, TASK_RUNNING, 0, 1, 0 }

#endif
#endif	/* SCHED_H */
