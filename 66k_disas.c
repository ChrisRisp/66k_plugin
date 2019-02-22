#include <stdio.h>
#include <string.h>
#include <r_types.h>
#include <r_lib.h>
#include <r_asm.h>

#include "66k_ops.h"
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

static bool 66k_init (void* user) {
	// Initialize interrupt vectors
}


static int 66k_disas(RAsm *a, RAsmOp *op, ut8 *buf, ut64 len) {
        char debugprintbuf[256];
	snprintf(debugprintbuf, 256, "\tBuffer (buf): %p, Length (len): %d\n", buf, len);
	dp(debugprintbuf);


	/* Determine size of instruction */
	if(len <= 6) {
		// Write backend code		
	}else{
		return 0;
	}

	//TODO Add entries for interrupt vectors (Call Init)
	//TODO Make a queue for resolving handler addreses
	//TODO Start decoding (ops.h)

	// Account for variable instruction size MAX of 6 bytes in length
	
	/*Fetch */
	char opcode[6]; // 6 bytes MAX length
	const char *buf_asm = "invalid";
	memcpy(opcode, buf, 6);
	
	/* Temp Decode */
	switch(opcode[0]) {
                case 0x00:
                        buf_asm = sdb_fmt("%d NOP", re_read_le24(opcode+1));
                        r_strbuf_set(&op->buf_asm, buf_asm);
			break;
                default:
			buf_asm = sdb_fmt("%s", "Invalid");
                        r_strbuf_set(&op->buf_asm, buf_asm);
                        break;
        }
        return 4;
}

