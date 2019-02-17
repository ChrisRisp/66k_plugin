#include <stdio.h>
#include <string.h>
#include <r_types.h>
#include <r_lib.h>
#include <r_asm.h>
// File Should be placed in libr/asm/p


/* Debug print func */
static void dp(char* str) {
        char* debugfile = "/tmp/66k_disas.log";
        FILE* fp = fopen(debugfile, "a");
        if(fp == NULL)
                return;

        fprintf(fp, str);
        fclose(fp);
}

static int disassemble(RAsm *a, RAsmOp *op, ut8 *buf, ut64 len) {
        char debugprintbuf[256];
        dp("disassemble function called!\n");
        snprintf(debugprintbuf, 256, "\tCPU: %s, Bits: %d, Big Endian: %d\n", a->cpu, a->bits, a->big_endian);
        dp(debugprintbuf);
        return 4;
}

RAsmPlugin r_asm_plugin_myarch = {
	.name = "66k Dissasembler",
	.desc = "disassembly plugin for OKI 66207",
	.arch = "OKI66k",
	.bits = 8|16, /* supported wordsizes */
	.init = NULL,
	.fini = NULL,
	.disassemble = &disassemble,
	.modify = NULL,
	.assemble = NULL,
};

#ifndef CORELIB
struct r_lib_struct_t radare_plugin = {
	.type = R_LIB_TYPE_ASM,
	.data = &r_asm_plugin_myarch
};
#endif
