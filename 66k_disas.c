static int disassemble(RAsm *a, RAsmOp *op, ut8 *buf, ut64 len) {
	/* TODO: Implement disassemble code here,
     * give a look to the other plugins */
}

RAsmPlugin r_asm_plugin_myarch = {
	.name = "MyArch",
	.desc = "disassembly plugin for MyArch",
	.arch = "myarch",
	.bits = (int[]){ 32, 64, 0 }, /* supported wordsizes */
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
