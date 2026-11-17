#ifndef VM_H
#define VM_H

#include <stddef.h>
#include "status.h"

#define STACK_MAX 64

typedef struct VM {
    const int* program; // 프로그램(명령어) 배열 시작 주소
    size_t program_sz; // 프로그램(명령어) 개수
    size_t idx; // 다음에 읽을 명령어 위치
    int stack[STACK_MAX]; // 스택
    size_t top; // 스택내의 원소 개수
} VM;

// 공개 function
Status vm_run(VM *v);
const char *vm_status_str(Status s);

#endif
