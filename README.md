# c-stack-vm

C로 만든 간단한 스택 기반 가상 머신(VM)입니다. 정수 배열로 된 바이트코드를 읽어 스택 위에서 연산합니다.

## 빌드 & 실행

```
make run     # 빌드 후 example.c 실행
make         # 빌드만 (build/vm)
make clean   # build/ 삭제
```

## 명령어 (opcode)

| 명령 | 피연산자 | 설명 |
|---|---|---|
| `OP_HALT` | - | 실행 종료 |
| `OP_PUSH` | 값 | 스택에 값 넣기 |
| `OP_POP` | - | 스택에서 값 하나 빼기 |
| `OP_ADD` | - | 위 두 값의 합 |
| `OP_SUB` | - | 위 두 값의 차 (아래 − 위) |
| `OP_MUL` | - | 위 두 값의 곱 |
| `OP_DIV` | - | 위 두 값의 나눗셈 (아래 / 위) |

예: `(2 + 3) * 2`

```c
int prog[] = {OP_PUSH, 2, OP_PUSH, 3, OP_ADD, OP_PUSH, 2, OP_MUL, OP_HALT};
VM v = {prog, sizeof(prog)/sizeof(int), 0, {0}, 0};
Status s = vm_run(&v);   // OK, 스택 맨 위는 10
```

## 에러 코드

| 코드 | 의미 |
|---|---|
| `ERR_STACK_OVERFLOW` | 스택이 가득 찬 상태에서 push |
| `ERR_STACK_UNDERFLOW` | 스택 원소가 부족 |
| `ERR_INT_OVERFLOW` | 결과가 int 범위 초과 |
| `ERR_DIV_ZERO` | 0으로 나눔 |
| `ERR_BAD_PC` | 프로그램 범위 초과 / 피연산자 없음 |
| `ERR_BAD_OPCODE` | 알 수 없는 명령어 |
| `ERR_STEP_LIMIT` | 실행 횟수가 10000회 초과 |
| `ERR_NULL` | VM 또는 프로그램 포인터가 NULL |

## 구조

```
include/   status.h, opcode.h, vm.h (공개 API), vm_internal.h (내부용)
src/
  vm.c       실행 루프(vm_run), 상태 문자열
  vm_ops.c   push/pop/add/sub/mul/div 구현
  example.c  예제 프로그램 모음 + main
```

## TODO

- [ ] 연산 실패 시 스택 복구 (지금은 pop한 값이 사라진 채로 에러가 남)
- [ ] 스택 조작 명령: `DUP`, `SWAP`, `OVER`
- [ ] 나머지 연산: `MOD`
- [ ] 부호 반전: `NEG`
- [ ] 비교 명령: `EQ`, `LT`, `GT`
