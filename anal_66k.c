#include <string.h>
#include <r_types.h>
#include <r_lib.h>
#include <r_asm.h>
#include <r_anal.h>
#include <r_anal_ex.h>
#include <r_cons.h>

#include "../../asm/arch/66k/66k_op.c"
#include "../../asm/arch/66k/66k_utils.c"
//#include "../../asm/arch/66k/66k_disas.h"


//Analysis isnt working because its skipping Over opcodes. Need to adapt the op.c File again.
//ut8 * rom_start = NULL;
dasm_state *D = NULL;

static int _66k_anop(RAnal *anal, RAnalOp *op, ut64 addr, const ut8 *data, int len) {

	dasmfunc func;	
	int res;

	char pbuf[256];
	snprintf(pbuf, 256, "Analysis DEBUG Addr: %ld\n", addr);
	dp(pbuf);
	
	if (D==NULL){
		D = (dasm_state*)malloc(sizeof(dasm_state));
	}

	/*Fetch */
	D->pc = addr; // Keep at 0
	D->rom = data-addr;
	D->op = op;
	D->dd = 0;

	char opcode[6];
	memcpy(opcode, data, 6);	


        // Address Range for Vector Table
        if(addr <= 57) {          // 56 / 0x38 is end of int vector section
                if(addr==56){
               		D->op->size = 4;
		        free(D);
			D = NULL;

			return 4; // Start of Code 
                }else{
			D->op->size = 2;
			free(D);
			D = NULL;

                        return 2; // Length of interrupt vector entry
                }   
        }   

	// Address Range for Code Section
	if(addr > 57){
		func = dasmtable[D->rom[D->pc]]; // Will return length of instruction
		res = func(D,D->mask);       // Get Instruction Length
		char pbuf[256];
		snprintf(pbuf, 256, "Analysis DEBUG Addr: %ld\n", addr);
		dp(pbuf);
		D->op->size = res;
		free(D);
		D = NULL;	
		return op->size;
	}
	return 0;
}

RAnalPlugin r_anal_plugin_66k = {
	.name = "66k",
        .desc = "Analysis plugin for OKI 66207",
        .arch = "66k",
        .bits = 8 | 16, /* supported wordsizes */
        .init = NULL,
        .fini = NULL,
	.op = &_66k_anop
};

#ifndef CORELIB
R_API RLibStruct radare_plugin = {
	.type = R_LIB_TYPE_ANAL,
	.data = &r_anal_plugin_66k,
	.version = R2_VERSION
};
#endif
