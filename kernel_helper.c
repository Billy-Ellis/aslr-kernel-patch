#include "kernel_helper.h"

#define LC_SIZE 0x0000000f

mach_port_t get_kernel_task_port(){
  mach_port_t kernel_task;
  kern_return_t kr;
  if ((kr = task_for_pid(mach_task_self(), 0, &kernel_task)) != 
KERN_SUCCESS){
    return -1;
  }
  return kernel_task;
}

uint32_t do_kernel_read(uint32_t addr){
  size_t size = 4;
  uint32_t data = 0;

  kern_return_t kr = 
vm_read_overwrite(get_kernel_task_port(),(vm_address_t)addr,size, 
(vm_address_t)&data,&size);
  if (kr != KERN_SUCCESS){
    printf("[!] Read failed. %s\n",mach_error_string(kr));
    return -1;
  }
  return data;
}

void do_kernel_write(uint32_t addr, uint32_t data){
  kern_return_t kr = 
vm_write(get_kernel_task_port(),(vm_address_t)addr,(vm_address_t)&data,sizeof(data));
  if (kr != KERN_SUCCESS){
    printf("Error writing!\n");
    return;
  }
}

uint32_t get_kernel_slide(){
  uint32_t slide;
  uint32_t base = 0x80001000;
  uint32_t slid_base;

  for (int slide_byte = 256; slide_byte >= 1; slide_byte--){
    slide = 0x01000000 + 0x00200000 * slide_byte;
    slid_base = base + slide;

    if (do_kernel_read(slid_base) == 0xfeedface){
      if (do_kernel_read(slid_base + 0x10) == LC_SIZE){
        return slide;
      }
    }
  }
  return -1;
}
