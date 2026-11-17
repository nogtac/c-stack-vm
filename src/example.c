#include <stdio.h>
#include <limits.h>

#include "opcode.h"
#include "vm.h"

// 정상 실행: (2 + 3) * 2 = 10
static const int prog_calc[] = {
    OP_PUSH, 2, OP_PUSH, 3, OP_ADD,
    OP_PUSH, 2, OP_MUL, OP_HALT
};

// 정상 실행: 10 - 4 = 6
static const int prog_sub[] = {
    OP_PUSH, 10, OP_PUSH, 4, OP_SUB, OP_HALT
};

// 정상 실행: 20 / 3 = 6 (정수 나눗셈)
static const int prog_div[] = {
    OP_PUSH, 20, OP_PUSH, 3, OP_DIV, OP_HALT
};

// 에러: 0으로 나눔
static const int prog_div_zero[] = {
    OP_PUSH, 5, OP_PUSH, 0, OP_DIV, OP_HALT
};

// 에러: 스택에 값이 하나뿐인데 ADD
static const int prog_underflow[] = {
    OP_PUSH, 1, OP_ADD, OP_HALT
};

// 에러: INT_MAX + 1 은 int 범위 초과
static const int prog_overflow[] = {
    OP_PUSH, INT_MAX, OP_PUSH, 1, OP_ADD, OP_HALT
};

// 에러: 존재하지 않는 명령어
static const int prog_bad_opcode[] = {
    OP_PUSH, 1, 99, OP_HALT
};

// 에러: HALT 없이 끝나서 프로그램 범위를 벗어남
static const int prog_no_halt[] = {
    OP_PUSH, 1
};

typedef struct {
    const char *name;
    const int *code;
    size_t size;
} Example;

#define EXAMPLE(n, p) { n, p, sizeof(p) / sizeof(p[0]) }

static const Example examples[] = {
    EXAMPLE("calc",       prog_calc),
    EXAMPLE("sub",        prog_sub),
    EXAMPLE("div",        prog_div),
    EXAMPLE("div_zero",   prog_div_zero),
    EXAMPLE("underflow",  prog_underflow),
    EXAMPLE("overflow",   prog_overflow),
    EXAMPLE("bad_opcode", prog_bad_opcode),
    EXAMPLE("no_halt",    prog_no_halt),
};

int main(void) {
    for (size_t i = 0; i < sizeof(examples) / sizeof(examples[0]); i++) {
        VM v = { examples[i].code, examples[i].size, 0, {0}, 0 };

        printf("=== %s ===\n", examples[i].name);
        Status s = vm_run(&v);
        printf("-> %s", vm_status_str(s));
        if (s == OK && v.top > 0) printf(" (스택 맨 위: %d)", v.stack[v.top - 1]);
        printf("\n\n");
    }
    return 0;
}
