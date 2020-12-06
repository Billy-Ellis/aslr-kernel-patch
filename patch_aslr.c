#include "kernel_helper.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

// iOS 9.0 iPhone5,4
#define INSTR_TO_PATCH_ADDR 0x802a3cc4 // addr of bic r0, r1, 0x80000000 in the kernel

#define DISABLE_BYTES       0x20002000 // movs r0, 0x0 x 2
#define ENABLE_BYTES        0x4000f021 // bic r0, r1, 0x80000000

int main(int argc, char *argv[]) {
    uint32_t slide = get_kernel_slide();
    printf("[+] KASLR slide is %08x\n", slide);

    uint32_t current_bytes = do_kernel_read(INSTR_TO_PATCH_ADDR + slide);
    printf("[+] Current bytes %08x\n", current_bytes);
    
    if (current_bytes == ENABLE_BYTES) {
        do_kernel_write(INSTR_TO_PATCH_ADDR + slide, DISABLE_BYTES);
        printf("[+] Patched ASLR random instruction. ASLR disabled.\n");
    } else {
        do_kernel_write(INSTR_TO_PATCH_ADDR + slide, ENABLE_BYTES);
        printf("[+] Patched ASLR random instruction. ASLR enabled again.\n");
    }
    
    return 0;
}
