#ifndef R2_66K_DISAS_H
#define R2_66K_DISAS_H

typedef struct{
	char name[20];
	short addr;
} _int_vector;

typedef struct {
        // Max representable int size for 16bit op
        //unsigned char rom[32768];
        ut8 *rom;
	char mask[32768];         /* mask[addr]=0 means data, 1 means code. */
        // PC Program Counter
        // USP User Stack Pointer
        // LRB Local Register Base
        unsigned pc, lrb, usp;
        // Data Desriptor
        //      Flag that determines whether calculation in accumulator (1) WORD or (0) Byte
	RAnalOp * op;	
	unsigned char dd; 
} dasm_state;

typedef int (*dasmfunc)(dasm_state *, char *buf);
extern dasmfunc dasmtable[];

//Implement //
extern const char *get_rom_label(unsigned addr);
extern const char *get_romtable_label(unsigned addr);
extern const char *get_ram_label(unsigned addr, int digits);	
//Implement //

int _66k_disas(RAsm *a, RAsmOp *op, ut8 *buf, ut64 len);

#endif
