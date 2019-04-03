#include <stdio.h>
#include <string.h>
#include <r_types.h>
#include <r_lib.h>
#include <r_anal.h>
#include <r_asm.h>

#include "66k_disas.h"
#include "66k_utils.h"
// File Should be placed in libr/asm/p


int vec_ctr = 0; // Vector parsed
ut8 * rom_start = NULL;
// List of interrupt vectors for  66201/66207
_int_vector _int_vecs[58] = {
	{"int_start", 0x0},{0},
	{"int_break", 0x0},{0},
	{"int_WDT", 0x0},{0},
	{"int_NMI",0x0},{0},
	{"int_INT0",0x0},{0},
	{"int_serial_rx", 0x0},{0},
	{"int_serial_tx",0x0},{0},
	{"int_serial_rx_BRG",0x0},{0},
	{"int_timer_0_overflow",0x0},{0},
	{"int_timer_0",0x0},{0},
	{"int_timer_1_overflow",0x0},{0},
	{"int_timer_1",0x0},{0},
	{"int_timer_2_overflow",0x0},{0},
	{"int_timer_2",0x0},{0},
	{"int_timer_3_overflow",0x0},{0},
	{"int_timer_3",0x0},{0},
	{"int_a2d_finished",0x0},{0},
	{"int_PWM_timer",0x0},{0},
	{"int_serial_tx_BRG",0x0},{0},
	{"int_INT1",0x0},{0},
	{"vcal_0",0x0},{0},
	{"vcal_1",0x0},{0},
	{"vcal_2",0x0},{0},
	{"vcal_3",0x0},{0},
	{"vcal_4",0x0},{0},
	{"vcal_5",0x0},{0},
	{"vcal_6",0x0},{0},
	{"vcal_7",0x0},{0},
	{"code_Start",0x0},{0},
	};
	

// Deal with _dequeue
// 	_dout get_label

//static Map_t map[SIZE_OF_MAP];

static unsigned tbladdr_lo=0x5465,tbladdr_hi=0x7ff0;


int re_read_le24(char* str) {
        int r = 0;
        r += (str[2] << 16);
        r += (str[1] << 8);
        r += str[0];
        return r;
}

int _66k_disas(RAsm *a, RAsmOp *op, ut8 *buf, ut64 len) {
        char debugprintbuf[256];
	dasmfunc func;	
	int res;
	const char *buf_asm = "invalid";
	dasm_state *D = (dasm_state*)malloc(sizeof(dasm_state));
	RAnalOp * t;

	if (rom_start ==NULL)
	{
		rom_start = buf;
	}

	/*Fetch */
	D->pc = a->pc; // Keep at 0
	D->rom = rom_start;
	D->op = t;

	// Address range for Vector Table
	if(a->pc <= 57) { // 56 / 0x38 is end of int vector section
		buf_asm = sdb_fmt("%s", _int_vecs[a->pc].name);
                r_strbuf_set(&op->buf_asm, buf_asm);
		// Set address for vector
		memcpy(&_int_vecs[a->pc].addr,buf, sizeof(short));
		snprintf(debugprintbuf, 256, "\tBuffer (buf): %p, DEC ADDR: %d, HEX ADDR: %04x, PC: %d", 
					buf, (int) _int_vecs[a->pc].addr, _int_vecs[a->pc].addr, a->pc);
		dp(debugprintbuf);
		free(D);
		if(a->pc==56){
			return 4; // Start of Code 
		}else{
			return 2; // Length of interrupt vector entry
		}
	}

	// Start of ROM Area Section
	if(a->pc > 57){

		func = dasmtable[D->rom[a->pc]]; // Will return length of instruction
		res = func(D,&op->buf_asm);
		snprintf(debugprintbuf, 256, "Got Length %d and ----PC = %x ---- Buffer :", res, a->pc);
		dp(debugprintbuf);
		snprintf(debugprintbuf, 256, &op->buf_asm);
		dp(debugprintbuf);

		//TODO Account for DW and DB mnemoics 
		//TODO Make Map for Interrupt Vector labels for quick lookup labeling address
		//		Will return appropriate instruction size
		//		Need to include sdb_fmt to set the buffer string
		//		Pass in buffer of size 6 for MAX OPCode len
		free(D);
		return res; // Instruction Size
	}

	return -1;
	
}

