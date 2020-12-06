#include <mach/mach.h>
#include <stdio.h>

mach_port_t get_kernel_task_port();
uint32_t do_kernel_read(uint32_t addr);
void do_kernel_write(uint32_t addr, uint32_t data);
uint32_t get_kernel_slide();
