typedef struct r_asm_plugin_t {
	[...]
	int (*init)(void *user);
	int (*fini)(void *user);
	int (*disassemble)(RAsm *a, RAsmOp *op, ut8 *buf, ut64 len);
	int (*assemble)(RAsm *a, RAsmOp *op, const char *buf);
	RAsmModifyCallback modify;
	int (*set_subarch)(RAsm *a, const char *buf);
} RAsmPlugin;
