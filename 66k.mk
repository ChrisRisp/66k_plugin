## 66k Makefile
OBJ_66k=asm_66k.o
## 66k Backend
OBJ_66k+=../arch/66k/66k_disas.o
CFLAGS+=-I./arch/66k/

STATIC_OBJ+=${OBJ_66k}
TARGET_66k=asm_66k.${EXT_SO}

ifeq ($(WITHPIC),1)
ALL_TARGETS+=${TARGET_66k}

${TARGET_66k}: ${OBJ_66k}
	${CC} $(call libname,asm_66k) ${LDFLAGS} ${CFLAGS} -o ${TARGET_66k} ${OBJ_66k}
endif
