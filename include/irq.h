#ifndef	_IRQ_H
#define	_IRQ_H

void enable_interrupt_controller();
void show_invalid_entry_message(int type,unsigned long esr, unsigned long address);

void irq_vector_init();
void enable_irq();
void disable_irq();

#endif	/* _IRQ_H */
