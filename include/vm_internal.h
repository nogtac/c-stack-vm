#ifndef VM_INTERNAL_H
#define VM_INTERNAL_H

#include "opcode.h"
#include "vm.h"

// 내부 전용: vm.c / vm_ops.c 에서만 사용
Status vm_push(VM *v, int val);
Status vm_pop(VM *v, int *out);
Status vm_add(VM *v);
Status vm_sub(VM *v);
Status vm_mul(VM *v);
Status vm_div(VM *v);

#endif
