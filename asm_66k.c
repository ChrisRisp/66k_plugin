#include <stdio.h>
#include <string.h>
#include <r_types.h>
#include <r_lib.h>
#include <r_asm.h>

#include "66k_disas.h"
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

static int re_read_le24(char* str) {
        int r = 0;
        r += (str[2] << 16);
        r += (str[1] << 8);
        r += str[0];
        return r;
}

static int disassemble(RAsm *a, RAsmOp *op, ut8 *buf, ut64 len) {
        char debugprintbuf[256];
	snprintf(debugprintbuf, 256, "\tBuffer (buf): %p, Length (len): %d\n", buf, len);
	dp(debugprintbuf);

	int dlen = _66k_disas(a, op, buf, len);
	if (dlen < 0) {
		//r += str[0];
		//dlen = 0;
		return 0;
	}
	op->size = dlen;
	return dlen;
}


RAsmPlugin r_asm_plugin_66k = {
	.name = "66k",
	.desc = "disassembly plugin for OKI 66207",
	.arch = "66k",
	.bits = 8 | 16, /* supported wordsizes */
	.endian = R_SYS_ENDIAN_LITTLE,
	.init = NULL,
	.fini = NULL,
	.disassemble = &disassemble,
	.modify = NULL,
	.assemble = NULL,
};

#ifndef CORELIB
struct r_lib_struct_t radare_plugin = {
	.type = R_LIB_TYPE_ASM,
	.data = &r_asm_plugin_66k
};
#endif
