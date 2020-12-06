# aslr-kernel-patch
Tool to patch the ASLR slide generation in the kernel to disable user-land ASLR on 32-bit iOS

### Example usage

1. Run the test program to verify ASLR is enabled.
```
Billys-N48AP:/var/mobile root# ./test1
ptr 0x23fe4
Billys-N48AP:/var/mobile root# ./test1
ptr 0x82fe4
Billys-N48AP:/var/mobile root# ./test1
ptr 0x7bfe4
Billys-N48AP:/var/mobile root#
```
The address printed is randomised on each execution.

2. Run the `pwn_aslr` program to patch the kernel
```
Billys-N48AP:/var/mobile root# ./pwn_aslr
[+] KASLR slide is 13000000
[+] Current bytes 4000f021
[+] Patched ASLR random instruction. ASLR disabled.
Billys-N48AP:/var/mobile root#
```
ASLR should now be disabled.

3. Re-run the test program to check
```
Billys-N48AP:/var/mobile root# ./test1
ptr 0xbfe4
Billys-N48AP:/var/mobile root# ./test1
ptr 0xbfe4
Billys-N48AP:/var/mobile root# ./test1
ptr 0xbfe4
Billys-N48AP:/var/mobile root#
```
The addresses printed are now static! ASLR has been disabled at the kernel level.
