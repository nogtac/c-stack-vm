#include <stdio.h>
#include <stddef.h>

#include "vm_internal.h"

#define STEP_MAX 10000

const char *vm_status_str(Status s) {
    static const char *names[] = {
        [OK]                  = "OK",
        [ERR_STACK_OVERFLOW]  = "stack overflow",
        [ERR_STACK_UNDERFLOW] = "stack underflow",
        [ERR_INT_OVERFLOW]    = "integer overflow",
        [ERR_DIV_ZERO]        = "division by zero",
        [ERR_BAD_PC]          = "bad program counter",
        [ERR_BAD_OPCODE]      = "unknown opcode",
        [ERR_STEP_LIMIT]      = "step limit exceeded",
        [ERR_NULL]            = "null pointer",
    };

    if ((size_t)s >= sizeof(names) / sizeof(names[0])) return "unknown status";
    return names[s];
}


Status vm_run(VM *v) {
    if(v == NULL || v->program == NULL) return ERR_NULL;

    size_t n = v->program_sz;
    const int* cmd = v->program;
    size_t cursor = v->idx;

    for(size_t i = 0; i < STEP_MAX; i++) {
        if(cursor >= n) return ERR_BAD_PC;

        int ret;
        Status s = OK;

        switch(cmd[cursor]) {
            case OP_HALT:
                return OK;
            case OP_PUSH:
                if(cursor + 1 >= n) return ERR_BAD_PC;
                s = vm_push(v, cmd[cursor + 1]);
                if(s != OK) return s;
                cursor += 2;
                break;
            case OP_POP:
                s = vm_pop(v, &ret);
                if(s != OK) return s;
                cursor++;
                break;
            case OP_ADD:
                s = vm_add(v);
                if(s != OK) return s;
                cursor++;
                break;
            case OP_SUB:
                s = vm_sub(v);
                if(s != OK) return s;
                cursor++;
                break;
            case OP_MUL:
                s = vm_mul(v);
                if(s != OK) return s;
                cursor++;
                break;
            case OP_DIV:
                s = vm_div(v);
                if(s != OK) return s;
                cursor++;
                break;
            default:
                return ERR_BAD_OPCODE; 
        }

        v->idx = cursor;
    }
    return ERR_STEP_LIMIT;
}

