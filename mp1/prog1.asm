;
; The code given to you here implements the histogram calculation that
; we developed in class.  In programming lab, we will add code that
; prints a number in hexadecimal to the monitor.
;
; Your assignment for this program is to combine these two pieces of
; code to print the histogram to the monitor.
;
; If you finish your program,
;    ** commit a working version to your repository  **
;    ** (and make a note of the repository version)! **


    .ORIG    x3000        ; starting address is x3000


;
; Count the occurrences of each letter (A to Z) in an ASCII string
; terminated by a NUL character.  Lower case and upper case should
; be counted together, and a count also kept of all non-alphabetic
; characters (not counting the terminal NUL).
;
; The string starts at x4000.
;
; The resulting histogram (which will NOT be initialized in advance)
; should be stored starting at x3F00, with the non-alphabetic count
; at x3F00, and the count for each letter in x3F01 (A) through x3F1A (Z).
;
; table of register use in this part of the code
;    R0 holds a pointer to the histogram (x3F00)
;    R1 holds a pointer to the current position in the string
;       and as the loop count during histogram initialization
;    R2 holds the current character being counted
;       and is also used to point to the histogram entry
;    R3 holds the additive inverse of ASCII '@' (xFFC0)
;    R4 holds the difference between ASCII '@' and 'Z' (xFFE6)
;    R5 holds the difference between ASCII '@' and '`' (xFFE0)
;    R6 is used as a temporary register
;

    LD R0,HIST_ADDR          ; point R0 to the start of the histogram
   
    ; fill the histogram with zeroes
    AND R6,R6,#0        ; put a zero into R6
    LD R1,NUM_BINS        ; initialize loop count to 27
    ADD R2,R0,#0        ; copy start of histogram into R2

    ; loop to fill histogram starts here
HFLOOP    STR R6,R2,#0        ; write a zero into histogram
    ADD R2,R2,#1        ; point to next histogram entry
    ADD R1,R1,#-1        ; decrement loop count
    BRp HFLOOP        ; continue until loop count reaches zero

    ; initialize R1, R3, R4, and R5 from memory
    LD R3,NEG_AT        ; set R3 to additive inverse of ASCII '@'
    LD R4,AT_MIN_Z        ; set R4 to difference between ASCII '@' and 'Z'
    LD R5,AT_MIN_BQ        ; set R5 to difference between ASCII '@' and '`'
    LD R1,STR_START        ; point R1 to start of string

    ; the counting loop starts here
COUNTLOOP
    LDR R2,R1,#0        ; read the next character from the string
    BRz PRINT_HIST        ; found the end of the string

    ADD R2,R2,R3        ; subtract '@' from the character
    BRp AT_LEAST_A        ; branch if > '@', i.e., >= 'A'
NON_ALPHA
    LDR R6,R0,#0        ; load the non-alpha count
    ADD R6,R6,#1        ; add one to it
    STR R6,R0,#0        ; store the new non-alpha count
    BRnzp GET_NEXT        ; branch to end of conditional structure
AT_LEAST_A
    ADD R6,R2,R4        ; compare with 'Z'
    BRp MORE_THAN_Z         ; branch if > 'Z'

; note that we no longer need the current character
; so we can reuse R2 for the pointer to the correct
; histogram entry for incrementing
ALPHA    ADD R2,R2,R0        ; point to correct histogram entry
    LDR R6,R2,#0        ; load the count
    ADD R6,R6,#1        ; add one to it
    STR R6,R2,#0        ; store the new count
    BRnzp GET_NEXT        ; branch to end of conditional structure

; subtracting as below yields the original character minus '`'
MORE_THAN_Z
    ADD R2,R2,R5        ; subtract '`' - '@' from the character
    BRnz NON_ALPHA        ; if <= '`', i.e., < 'a', go increment non-alpha
    ADD R6,R2,R4        ; compare with 'z'
    BRnz ALPHA        ; if <= 'z', go increment alpha count
    BRnzp NON_ALPHA        ; otherwise, go increment non-alpha

GET_NEXT
    ADD R1,R1,#1        ; point to next character in string
    BRnzp COUNTLOOP        ; go to start of counting loop



PRINT_HIST

; you will need to insert your code to print the histogram here

; do not forget to write a brief description of the approach/algorithm
; for your implementation, list registers used in this part of the code,
; and provide sufficient comments

;Zayd Saeed (zsaeed2) Discussion Section BDA
;This print Histogram algortithm used a recursive form of the print hex number
;algorithm we made in the lab. It read 4 binary values, or 1 hex value, translated it
;and printed it to the system, and did that four times with multiple loops and counters, 
;accounting for hex values greater than x9.
;partner: sriramr2
;Register Table
;R0: Letter to be printed
;R1: Digit counter to count how many digits have been printed
;R2: Bit counter to see how many bits have been read
;R3: Hold hex value of character to be printed
;R4: Reads letter and ascii value of that letter
;R5: Holds memory address of letter to be printed
;R6: Letter counter to see how many letters have been printed
    AND R6,R6,#0 ;LETTER COUNTER
    AND R5,R5,#0 ;MEMORY ADDRESS
    AND R4, R4, #0; CURRENT LETTER
    LD R5, HIST_ADDR ;LOADS R5 WITH MEMORY ADDRESS OF HISTOGRAM CHARACTER
    ADD R5, R5, #-1
    ADD R6, R6, #-15
    ADD R6, R6, #-12
EVERYLETTERLOOP    ADD R6, R6, #15 ;add 27
                ADD R6, R6, #12
                ADD R4, R4, #15; ADDING 64 TO R4
                ADD R4, R4, #15
                ADD R4, R4, #15
                ADD R4, R4, #15
                ADD R4, R4, #4
                AND R0, R0, #0	; clear R0 
                ADD R0, R4, #0	; Put value of R4 into R0 to print
                OUT				; Prints character
                AND R0,R0,#0	; Clears R0
                LD R0, SPACE	; Loads and prints space character
                OUT
                ADD R5, R5, #1	; increment value of counter
                LDR R3, R5, #0	; Load hex value of next character into R3
                AND R1, R1, #0  ;DIGIT COUNTER
DIGITPRINTEDLOOP ADD R1, R1, #-4 ; check if number of digits printed is greater than 3. if so, branch to outer
                BRzp OUTER
                ADD R1,R1, #4  ;
                AND R0, R0, #0 ; DIGIT TO BE PRINTED
                AND R2, R2, #0 ; BIT COUNTER
FOURBITCOUNTER 	ADD R2, R2, #-4	;decrement 4 from r2 and branch to print digit if its not negative
                BRzp DIGITPRINTER
                ADD R2, R2, #4   ;increment bit counter by 4
                ADD R0, R0, R0   ;shift R0 to the left
                ADD R3, R3, #0	 ;update nzp for for R3 and branch to addzero if zero or positive
                BRzp ADDZERO
                ADD R0, R0, #1	 ; add 1 to R0 if R3 is negative 0, otherwise add 0
ADDZERO         ADD R0, R0, #0	 
                ADD R3, R3, R3	 ; Multiply R3 by 2
                ADD R2, R2, #1	 ; add 1 to R2 and then branch back to fourbitcounter loop
                BRnzp FOURBITCOUNTER

DIGITPRINTER 	ADD R0,R0,#-9	;decrement R0 by 9 and branch if it is nonpositive to Undernine loop
                BRnz UNDERNINE
                ADD R0,R0,#15	; increment R0 by 64
                ADD R0,R0,#15
                ADD R0,R0,#15
                ADD R0,R0,#10
                ADD R0,R0,#9
                BRnzp PRINT		; Branch to print code
UNDERNINE 		ADD R0,R0,#9	; Increment R0 by 67
                ADD R0,R0,#15
                ADD R0,R0,#15
                ADD R0,R0,#15
                ADD R0,R0,#3
PRINT           OUT				; Print whatever is in R0, increment counter, and branch to DIGITPRINTEDLOOP Loop
                ADD R1, R1, #1
                BRnzp DIGITPRINTEDLOOP
OUTER           LD R0, NEWLINE	; print new line character
                OUT
                ADD R4,R4,#1	;subtract 63 from R4
                ADD R4,R4, #-15
                ADD R4,R4, #-15
                ADD R4,R4, #-15
                ADD R4,R4, #-15
                ADD R4,R4, #-4	
                ADD R6, R6, #1 ; LETTER COUNTER INCREMENTER
TESTINGLETTER   ADD R6, R6, #-15 ; subtract 27 from letter counter (26 since we added one)
                ADD R6, R6, #-12
                BRn EVERYLETTERLOOP	;branch back to top if negative. Otherwise Halt program.
				BRzp DONE
   


DONE            HALT            ; done
NEWLINE         .FILL x0A		; new line character
SPACE            .FILL x20		; space character

; the data needed by the program
NUM_BINS    .FILL #27    ; 27 loop iterations
NEG_AT        .FILL xFFC0    ; the additive inverse of ASCII '@'
AT_MIN_Z    .FILL xFFE6    ; the difference between ASCII '@' and 'Z'
AT_MIN_BQ    .FILL xFFE0    ; the difference between ASCII '@' and '`'
HIST_ADDR    .FILL x3F00     ; histogram starting address
STR_START    .FILL x4000    ; string starting address

; for testing, you can use the lines below to include the string in this
; program...
 ;STR_START    .FILL STRING    ; string starting address
 ;STRING        .STRINGZ "This is a test of the counting frequency code. AbCd...WxYz. "



    ; the directive below tells the assembler that the program is done
    ; (so do not write any code below it!)

    .END
