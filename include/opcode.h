#ifndef OPCODE_H
#define OPCODE_H

typedef enum {
    OP_HALT = 0, // 실행 종료
    OP_PUSH, // 스택에 숫자 넣기
    OP_POP, // 스택에 숫자 빼기
    OP_ADD, // 스택에 있는 두 정수의 합
    OP_SUB, // 스택에 있는 두 정수의 차
    OP_MUL, // 스택에 있는 두 정수의 곱
    OP_DIV // 스택에 있는 두 정수의 나눗셈
} Op;

#endif
