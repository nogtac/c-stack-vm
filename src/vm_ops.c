#include <limits.h>

#include "vm_internal.h"

Status vm_push(VM *v, int val) {
    if(v->top == STACK_MAX) return ERR_STACK_OVERFLOW;

    v->stack[v->top++] = val;
    return OK;
}

Status vm_pop(VM *v, int* out) {
    if(v->top == 0) return ERR_STACK_UNDERFLOW;

    *out = v->stack[--v->top];
    return OK;
}


Status vm_add(VM *v) {
    if(v->top < 2) return ERR_STACK_UNDERFLOW;

    int a,b;
    vm_pop(v, &a);
    vm_pop(v, &b);

    if(b < 0 && a < INT_MIN - b) return ERR_INT_OVERFLOW;
    if(b > 0 && a > INT_MAX - b) return ERR_INT_OVERFLOW;
    
    v->stack[v->top++] = a + b;
    return OK;
}

Status vm_sub(VM *v) {
    if(v->top < 2) return ERR_STACK_UNDERFLOW;

    int a,b;
    vm_pop(v, &b);
    vm_pop(v, &a);

    if(b < 0 && a > INT_MAX + b) return ERR_INT_OVERFLOW;
    if(b > 0 && a < INT_MIN + b) return ERR_INT_OVERFLOW;
    v->stack[v->top++] = a-b;
    
    return OK;
}

Status vm_mul(VM *v) {
    if(v->top < 2) return ERR_STACK_UNDERFLOW;

    int a,b;
    vm_pop(v, &a);
    vm_pop(v, &b);
    
    long long r = (long long)a * b;
    if(r > INT_MAX || r < INT_MIN) return ERR_INT_OVERFLOW;

    v->stack[v->top++] = (int)r;
    return OK;
}

Status vm_div(VM *v) {
    if(v->top < 2) return ERR_STACK_UNDERFLOW;

    int a,b;
    vm_pop(v, &b);
    vm_pop(v, &a);
    
    if(a == INT_MIN && b == -1) return ERR_INT_OVERFLOW;
    if(b == 0) return ERR_DIV_ZERO;
    v->stack[v->top++] = a/b;
    return OK;
}
