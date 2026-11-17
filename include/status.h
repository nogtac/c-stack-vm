#ifndef STATUS_H
#define STATUS_H

typedef enum {
    OK = 0,               // 성공
    ERR_STACK_OVERFLOW,   // 스택이 가득 찬 상태에서 push
    ERR_STACK_UNDERFLOW,  // 스택에 원소가 부족한 상태에서 pop / 연산
    ERR_INT_OVERFLOW,     // 연산 결과가 int 범위를 벗어남
    ERR_DIV_ZERO,         // 0으로 나눔
    ERR_BAD_PC,           // 커서 범위 초과 / operand 없음
    ERR_BAD_OPCODE,       // 알 수 없는 명령어
    ERR_STEP_LIMIT,       // 실행 횟수가 STEP_MAX 초과
    ERR_NULL              // VM 또는 프로그램 포인터가 NULL
} Status;

#endif
