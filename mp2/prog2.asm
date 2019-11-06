; Zayd Saeed	ZSAEED2	02/07/2019	MP2
; This program is a stack calculator that takes in a postfix input into the terminal and spits out the answer to that question in hexadecimal. If the input is invalid, it prints an invalid expression return statement. There are 5
; subroutines for each of the operations: add, subtract, multiply, divide, and exponentiate. The final subroutine is for evaluate, which evaluates the full expression and prints out the answer. It covers negative numbers for addition,
; subtraction, and multiplication, but not for division or exponentiation
; Partners: srajag9, al
.ORIG x3000
   
;your code goes here


BRnzp EVALUATE






;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R3- value to print in hexadecimal
PRINT_HEX							;Subroutine to print hex value to screen after evaluating code given first line of Code. Taken and accordingly fixed from lab1. 
AND R1, R1, #0 ;DIGIT COUNTER
DIGITPRINTEDLOOP ADD R1, R1, #-4
BRzp FINISH
ADD R1,R1, #4
AND R0, R0, #0 ; DIGIT TO BE PRINTED
AND R2, R2, #0 ; BIT COUNTER
FOURBITCOUNTER ADD R2, R2, #-4
BRzp DIGITPRINTER
ADD R2, R2, #4
ADD R0, R0, R0
ADD R3, R3, #0
BRzp ADDZERO
ADD R0, R0, #1
ADDZERO ADD R0, R0, #0
ADD R3, R3, R3
ADD R2, R2, #1
BRnzp FOURBITCOUNTER

DIGITPRINTER ADD R0,R0,#-9
BRnz UNDERNEATHNINE
ADD R0,R0,#15
ADD R0,R0,#15
ADD R0,R0,#15
ADD R0,R0,#10
ADD R0,R0,#9
BRnzp PRINT
UNDERNEATHNINE ADD R0,R0,#9
ADD R0,R0,#15
ADD R0,R0,#15
ADD R0,R0,#15
ADD R0,R0,#3
PRINT OUT
ADD R1, R1, #1
BRnzp DIGITPRINTEDLOOP
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R0 - character input from keyboard, also output from subroutines
;R6 - current numerical output
;R1 - Checker, counter, etc.
;R2 - 0 CHECKER, also sometimes used in subroutines
;R3, R4 - primarily used as inputs for the subroutine commands, addition, subtraction, multiplication, division
;R5 - mainly used in checking for underflow/overflow
AND R1, R1, #0 
AND R2, R2, #0
AND R3, R3, #0
AND R4, R4, #0
AND R5, R5, #0
AND R6, R6, #0
AND R7, R7, #0

EVALUATE GETC
         OUT
TESTEQUAL LD R1, EQUALCHAR
        NOT R1,R1
        ADD R1, R1, #1
        ADD R1, R1, R0
        BRz CHECK_STACK
        BRnp TESTSPACE

CHECK_STACK
    LD R2,STACK_TOP
    LD R3,STACK_START
    AND R4,R4,#0
    NOT R2,R2
    ADD R2,R2,#1
    ADD R4,R3,R2 ;checking if stack has only one value
    ADD R4,R4,#-1
    BRz LOAD_RESULT    ;there is 1 value so load result in R5
    BRnp INVALIDCHAR

LOAD_RESULT    JSR POP
            AND R5,R5,#0
            ADD R5,R0,#0
            AND R3,R3,#0
            ADD R3,R5,#0
            BRnzp PRINT_HEX
    

TESTSPACE LD R1, SPACECHAR	;block of code that tests for the space character
        NOT R1,R1
        ADD R1, R1, #1
        ADD R1, R1, R0
        BRz EVALUATE

UNDERNINE     LD R1, NINECHAR ;tests if value is under 9
            NOT R1,R1
            ADD R1, R1, #1
            ADD R1, R1, R0
            BRnz ISOVERZERO
            BRp TESTPOWER

ISOVERZERO     LD R1, ZEROCHAR ; tests if value is above 0
            NOT R1,R1
            ADD R1, R1, #1
            ADD R1, R1, R0
            BRzp ISOPERAND
            BRn TESTMUL

TESTMUL    LD R1, MULCHAR ;tests to see if operand is multiplication
        NOT R1,R1
        ADD R1, R1, #1
        ADD R1, R1, R0
        BRz ISMUL       

TESTDIV    LD R1, DIVCHAR ;block tests to see if operand is division
        NOT R1,R1
        ADD R1, R1, #1
        ADD R1, R1, R0
        BRz ISDIV

TESTSUB    LD R1, SUBCHAR ; block of code to test if operand is subtraction
        NOT R1,R1
        ADD R1, R1, #1
        ADD R1, R1, R0
        BRz ISSUB

TESTADD    LD R1, ADDCHAR ;checking if operation needed to be performed is addition
        NOT R1,R1
        ADD R1, R1, #1
        ADD R1, R1, R0
        BRz ISADD

TESTPOWER     LD R1, POWERCHAR ;tests if we need to exponentiate
            NOT R1,R1
            ADD R1, R1, #1
            ADD R1, R1, R0
            BRz ISPOWER
            BRnp INVALIDCHAR

ISMUL        JSR POP		;subroutine to direct program to perform multiplication after popping 2 values from the stack
            AND R4, R4, #0
            ADD R4, R0, #0
            JSR POP
            AND R3, R3, #0
            ADD R3, R0, #0
            ADD R5, R5, #0
            BRp INVALIDCHAR
            JSR MUL
            BRnzp PUSHING

ISDIV        JSR POP		;subroutine to direct program to perform division after popping 2 values from the stack
            AND R4, R4, #0
            ADD R4, R0, #0
            JSR POP
            AND R3, R3, #0
            ADD R3, R0, #0
            ADD R5, R5, #0
            BRp INVALIDCHAR
            JSR DIV
            BRnzp PUSHING

ISSUB        JSR POP		;subroutine to direct program to perform subtraction after popping 2 values from the stack
            AND R4, R4, #0
            ADD R4, R0, #0
            JSR POP
            AND R3, R3, #0
            ADD R3, R0, #0
            ADD R5, R5, #0
            BRp INVALIDCHAR
            JSR MIN
            BRnzp PUSHING

ISADD        JSR POP		; subroutine to direct program to perform addition after popping 2 values from the stack
            AND R4, R4, #0
            ADD R4, R0, #0
            JSR POP
            AND R3, R3, #0
            ADD R3, R0, #0
            ADD R5, R5, #0
            BRp INVALIDCHAR
            JSR PLUS
            BRnzp PUSHING

ISPOWER      JSR POP		;subroutine to direct program to perform exponentiation after popping 2 values from the stack
            AND R4, R4, #0
            ADD R4, R0, #0
            JSR POP
            AND R3, R3, #0
            ADD R3, R0, #0
            ADD R5, R5, #0
            BRp INVALIDCHAR
            JSR EXP
            BRnzp PUSHING

INVALIDCHAR    LEA R0,INVALID	;prints "invalid expression" if expression 
            PUTS    ;print ' Invalid Expression'
            BRnzp DONE


ISOPERAND    LD R1, NEG30 ; tests if input character is an operand
            ADD R0,R0,R1       
            JSR PUSH
            BRnzp EVALUATE
PUSHING     JSR PUSH		; jumps to subroutine to push
            BRnzp EVALUATE


FINISH		BRnzp DONE 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
PLUS   				;Subroutine for addition, just adds R3 and R4
    ADD R0,R3,R4
    RET
   
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MIN   				;Subroutine for subtraction, takes 2's complement inverse of R4 and adds R3 and R4' together
    NOT R4,R4
    ADD R4,R4,#1
    ADD R0,R3,R4
    RET
   
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MUL     AND R0,R0,#0	;Subroutine for multiplication, tests for negative R4 and 2's complement inverses it if it is negative. Then loop adds until its complete
		ADD R4,R4,#0
		BRzp MULLOOP
		NOT R4, R4
		NOT R3, R3
		ADD R4, R4, #1
		ADD R3, R3, #1
MULLOOP ADD R0,R3,R0
        ADD R4,R4,#-1
        BRp MULLOOP

        RET
   
   
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
DIV   				; Subroutine for division, subtracts repeatedly until you hit a zero or negative, and adds it back accordingly to report a remainder.
    ST R2,SAVE_R2
    AND R2,R2,#0
    AND R0,R0,#0
    NOT R4,R4
    ADD R4,R4,#1
LOOP
    ADD R3,R3,R4
    BRz ZERO
    BRn REMAINDER
    ADD R0,R0,#1
    BRnzp LOOP

ZERO
    ADD R0,R0,#1
    LD R2,SAVE_R2
    RET


REMAINDER
    ADD R0,R0,#0
    LD R2,SAVE_R2
    RET
   
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
EXP						;Subroutine for exponentiation. Uses Subroutine for multiplication, and sets R1 as counter, and multiplies repeatedly until counter (exponent) goes down to 0. originally subtracts 1 from exponent
    ST R1,SAVE_R1		;to account for R3 times R3 being equal to R3^2
	AND R1,R1,#0
    AND R0,R0,#0
	ADD R0,R0,#1
	ADD R1,R4,#-1
	ADD R4,R3,#0
	ADD R1,R1,#0    
    BRz POWER_OF_ZERO
UP
	ADD R1,R1,#0
    BRz DOWN
	ST R7,SAVE_R7
	JSR MUL
	LD R7,SAVE_R7
	ADD R4,R0,#0
    ADD R1,R1,#-1
    BRp UP

DOWN
    LD R1,SAVE_R1
    ADD R0,R0,#0
    RET
   
POWER_OF_ZERO		; If exponent is originally 0, automatically output 1
    LD R1,SAVE_R1
    ADD R0,R0,#1
    RET
   

;IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP
;
PUSH   ;subroutine to push an inputted character onto stack. Went over this in class. not much explanation needed
    ST R3, PUSH_SaveR3    ;save R3
    ST R4, PUSH_SaveR4    ;save R4
    AND R5, R5, #0        ;
    LD R3, STACK_END    ; 
    LD R4, STACk_TOP    ;
    ADD R3, R3, #-1        ;
    NOT R3, R3        ;
    ADD R3, R3, #1        ;
    ADD R3, R3, R4        ;
    BRz OVERFLOW        ;stack is full
    STR R0, R4, #0        ;no overflow, store value in the stack
    ADD R4, R4, #-1        ;move top of the stack
    ST R4, STACK_TOP    ;store top of stack pointer
    BRnzp DONE_PUSH        ;
OVERFLOW
    ADD R5, R5, #1        ;
DONE_PUSH
    LD R3, PUSH_SaveR3    ;
    LD R4, PUSH_SaveR4    ;
    RET


PUSH_SaveR3    .BLKW #1    ;
PUSH_SaveR4    .BLKW #1    ;


;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP
;
POP   ; subroutine to pop a character off a stack. Went over this in class. not much explanation needed
    ST R3, POP_SaveR3    ;save R3
    ST R4, POP_SaveR4    ;save R3
    AND R5, R5, #0        ;clear R5
    LD R3, STACK_START    ;
    LD R4, STACK_TOP    ;
    NOT R3, R3        ;
    ADD R3, R3, #1        ;
    ADD R3, R3, R4        ;
    BRz UNDERFLOW        ;
    ADD R4, R4, #1        ;
    LDR R0, R4, #0        ;
    ST R4, STACK_TOP    ;
    BRnzp DONE_POP        ;
UNDERFLOW
    ADD R5, R5, #1        ;
DONE_POP
    LD R3, POP_SaveR3    ;
    LD R4, POP_SaveR4    ;
    RET


POP_SaveR3    .BLKW #1    ; save contents of R3, R4 when popping from stack
POP_SaveR4    .BLKW #1    ;
STACK_END    .FILL x3FF0    ; Memory address of end of stack
STACK_START    .FILL x4000    ; Memory address of the stack start
STACK_TOP    .FILL x4000    ; Original memory address of top of stack
EQUALCHAR    .FILL x3D		; ascii value for '=' character
SPACECHAR    .FILL x20		; ascii value for ' ' character
NINECHAR    .FILL x39		; ascii value for '9' character
ZEROCHAR    .FILL x30		; ascii value for '0' character
DIVCHAR        .FILL x2F	; ascii value for '/' character
SUBCHAR        .FILL x2D	; ascii value for '-' character
ADDCHAR        .FILL x2B	; ascii value for '+' character
MULCHAR        .FILL x2A 	; ascii value for '*' character
POWERCHAR    .FILL x5E		; ascii value for '^' character
NEG30        .FILL xFFD0	; holds negative 30
SAVE_R1        .BLKW #1		; save contents of R1, R2, and R7 when used in subroutines
SAVE_R2        .BLKW #1	
SAVE_R7		   .BLKW #1
INVALID        .STRINGZ "Invalid Expression"	; invalid expression string to be printed for invalid expression
TESTSTRING  .STRINGZ "STOPS HERE" 				; test
DONE HALT					; Halts the program

.END
