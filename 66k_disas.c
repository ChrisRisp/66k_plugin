#include <stdio.h>
#include <string.h>
#include <r_types.h>
#include <r_lib.h>
#include <r_asm.h>

#include "66k_disas.h"
// File Should be placed in libr/asm/p


int vec_ctr = 0; // Vector parsed

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
	

/* Debug print func */
void dp(char* str) {
        char* debugfile = "/tmp/66k_disas.log";
        FILE* fp = fopen(debugfile, "a");
        if(fp == NULL)
                return;

        fprintf(fp, str);
        fclose(fp);
}

int re_read_le24(char* str) {
        int r = 0;
        r += (str[2] << 16);
        r += (str[1] << 8);
        r += str[0];
        return r;
}

int _66k_disas(RAsm *a, RAsmOp *op, ut8 *buf, ut64 len) {
        char debugprintbuf[256];

	const char *buf_asm = "invalid";
	/*Fetch */
	char opcode[2]; // 6 bytes MAX length
	memcpy(opcode, buf, 2);
	
	// Address range for Vector Table
	if(a->pc < 56) { // 56 / 0x38 is end of int vector section
		buf_asm = sdb_fmt("%s", _int_vecs[a->pc].name);
                r_strbuf_set(&op->buf_asm, buf_asm);
		// Set address for vector
		memcpy(&_int_vecs[a->pc].addr,buf, sizeof(short));
		snprintf(debugprintbuf, 256, "\tBuffer (buf): %p, DEC ADDR: %d, HEX ADDR: %04x, PC: %d", 
					buf, (int) _int_vecs[a->pc].addr, _int_vecs[a->pc].addr, a->pc);
		dp(debugprintbuf);
		return 2; // Length of interrupt vector entry
	}
	// Start of ROM Area Section
	if(a->pc >= 56){
		//buf_asm = sdb_fmt("%02x : Address", *opcode);
		buf_asm = sdb_fmt("%s", _int_vecs[a->pc].name);
		r_strbuf_set(&op->buf_asm, buf_asm);
		//TODO Implement Parsing Link to Andy's Opcode file and sub in the rom and ram label functions
		//TODO Account for DW and DB mnemoics 
		//TODO Make Map for Interrupt Vector labels for quick lookup labeling address
		//		Will return appropriate instruction size
		//		Need to include sdb_fmt to set the buffer string
		//		Pass in buffer of size 6 for MAX OPCode len
		return 4;
	}

	/* Determine size of instruction */
	if(len <= 6) {
		// Write backend code		
	}else{
		return 0;
	}
	
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

