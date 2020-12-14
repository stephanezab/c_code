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
   
   
   
   
   
      
   
