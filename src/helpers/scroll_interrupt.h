#ifndef _SCROLL_INTERRUPT_H
#define _SCROLL_INTERRUPT_H

void set_scroll(unsigned int lineCnt, void (*f)(void));
void clear_scroll(void);

#endif
