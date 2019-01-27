OBJ_MYARCH=asm_myarch.o
# myarch backend
OBJ_MYARCH+=../arch/myarch/udis86/file1.o
OBJ_MYARCH+=../arch/myarch/udis86/file2.o
[...]

STATIC_OBJ+=${OBJ_MYARCH}
TARGET_MYARCH=asm_myarch.${EXT_SO}

ALL_TARGETS+=${TARGET_MYARCH}

${TARGET_MYARCH}: ${OBJ_MYARCH}
	${CC} ${LDFLAGS} ${CFLAGS} -o ${TARGET_MYARCH} ${OBJ_MYARCH}
