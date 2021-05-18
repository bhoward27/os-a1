.globl main
main:
    xorq    %rax, %rax
    xorl    %eax, %eax
    movq    $0, %rax
    movl    $0, %eax

    addl    $1, %eax
    leal    1(%eax), %eax
    incl    %eax

    addl    $8, %eax
    leal    8(%eax), %eax
