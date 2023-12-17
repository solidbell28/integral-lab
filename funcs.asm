section .text

global func1 ; e^(-x) + 3
func1:
    push ebp
    mov ebp, esp
    finit

    fld qword[ebp + 8]
    fchs
    fldl2e
    fmulp
    fld ST0
    frndint
    fsub ST1, ST0
    fxch ST1
    f2xm1
    fld1
    faddp
    fscale
    fxch ST1
    fstp ST0
    fld1
    fld1
    fld1
    faddp
    faddp
    faddp

    leave
    ret


global func2 ; 2x - 2
func2:
    push ebp
    mov ebp, esp
    finit

    fld1
    fld1
    faddp
    fld qword[ebp + 8]
    fmulp
    fld1
    fld1
    faddp
    fsubp

    leave
    ret


global func3 ; 1 / x
func3:
    push ebp
    mov ebp, esp
    finit

    fld1
    fld qword[ebp + 8]
    fdivp

    leave
    ret


global func1_test ; x^2 - 2
func1_test:
    push ebp
    mov ebp, esp
    finit
    
    fld qword[ebp + 8]
    fld ST0
    fmulp
    fld1
    fld1
    faddp
    fsubp
    
    leave
    ret


global func2_test ; (x - 2)^3
func2_test:
    push ebp
    mov ebp, esp
    finit

    fld qword[ebp + 8]
    fld1
    fld1
    faddp
    fsubp
    fld ST0
    fld ST0
    fmulp
    fmulp
    
    leave
    ret


global func3_test ; -2x + 1
func3_test:
    push ebp
    mov ebp, esp
    finit
    
    fld qword[ebp + 8]
    fld ST0
    faddp
    fchs
    fld1
    faddp
    
    leave
    ret
