# name: Stephane Zabayo
# ID: 116998604
# Directory ID: szabayo

is_palindrome:
    
      # PROLOGUE   
   sub  $sp, $sp, 8
   sw   $ra, 0($sp)          # saving $ra
   sw   $a0, 4($sp)          # saving string 
   
      # BODY
   li $t0, 0                 # lenght
   li $t2, 0                 # i
   
   jal strlen
   
   lw  $a0, 4($sp)           # restoring $a0
   add $t0, $zero, $v0       # $t0 is length here
                             # from strlen()
   
   div $t8, $t0, 2

loop: 
   
   bge $t2, $t8, exit_loop   # loop condition t2 > t8 
                             # go to exit_loop
      
   sub $t3, $t0, $t2         #length -i
   sub $t3, $t3, 1           #(lenght-i)-1
   
   
   
   add $t4, $a0, $t2
   lb  $t4, 0($t4)           # string[i]
   
   add $t6, $a0, $t3
   lb  $t6, 0($t6)           # string[len - i - 1]
   
  
   
   bne $t4, $t6, else        # if statement ==
   
   add $t2, $t2, 1
   j   loop
    
     
     
strlen:                      # strlen() Function
   lb  $t1, 0($a0)
   beqz $t1, exit
   addi $a0, $a0, 1
   addi $t0, $t0, 1          # increment length
   
   j strlen
   
exit:                        # Exit strlen 
   add $v0, $zero, $t0          
   jr  $ra     
      
      
      
      # EPILOGUE
else:

   add $v0, $zero, $zero     # return 0
   
   lw   $ra, 0($sp)          # restoring $ra
   add  $sp, $sp, 8          # destroy stack 
   jr   $ra
   
exit_loop:

   add $v0, $zero, 1         # return 1
             
   lw   $ra, 0($sp)          # restoring $ra
   add  $sp, $sp, 8          # destroy stack
   jr   $ra   
   
   
   
   
   
      
   
   .data
str1:
   .asciiz "abba"
str2:
   .asciiz "racecar"
str3:
   .asciiz "swap paws",
str4:
   .asciiz "not a palindrome"
str5:
   .asciiz "another non palindrome"
str6:
   .asciiz "almost but tsomla"

# array of char pointers = {&str1, &str2, ..., &str6}
ptr_arr:
   .word str1, str2, str3, str4, str5, str6, 0

yes_str:
   .asciiz " --> Y\n"
no_str:
   .asciiz " --> N\n"

   .text

# main(): ##################################################
#   char ** j = ptr_arr
#   while (*j != 0):
#     rval = is_palindrome(*j)
#     printf("%s --> %c\n", *j, rval ? yes_str: no_str)
#     j++
#
main:
   li   $sp, 0x7ffffffc    # initialize $sp

   # PROLOGUE
   subu $sp, $sp, 8        # expand stack by 8 bytes
   sw   $ra, 8($sp)        # push $ra (ret addr, 4 bytes)
   sw   $fp, 4($sp)        # push $fp (4 bytes)
   addu $fp, $sp, 8        # set $fp to saved $ra

   subu $sp, $sp, 8        # save s0, s1 on stack before using them
   sw   $s0, 8($sp)        # push $s0
   sw   $s1, 4($sp)        # push $s1

   la   $s0, ptr_arr        # use s0 for j. init ptr_arr
main_while:
   lw   $s1, ($s0)         # use s1 for *j
   beqz $s1, main_end      # while (*j != 0):
   move $a0, $s1           #    print_str(*j)
   li   $v0, 4
   syscall
   move $a0, $s1           #    v0 = is_palindrome(*j)
   jal  is_palindrome
   beqz $v0, main_print_no #    if v0 != 0:
   la   $a0, yes_str       #       print_str(yes_str)
   b    main_print_resp
main_print_no:             #    else:
   la   $a0, no_str        #       print_str(no_str)
main_print_resp:
   li   $v0, 4
   syscall

   addu $s0, $s0, 4       #     j++
   b    main_while        # end while
main_end:

   # EPILOGUE
   move $sp, $fp           # restore $sp
   lw   $ra, ($fp)         # restore saved $ra
   lw   $fp, -4($sp)       # restore saved $fp
   j    $ra                # return to kernel
# end main ################################################
