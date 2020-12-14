# name: Stephane Zabayo
# ID: 116998604
# Directory ID: szabayo

reverse_prefix_sum:
   li    $t6, 0
   lw    $t6, 0($s0)           # $t6 is *arr
   bne   $t6, -1, sum          # if $t6 != -1
   add   $v0, $zero, $zero
   jr    $ra
   
sum:
      # PROLOGUE
   sub   $sp, $sp, 12         # create stack
   sw    $ra, 0($sp)          # save $ra
   
   sw    $s0, 4($sp)          # save arr
   
      # Body
   addu  $s0, $s0, 4
   
   jal   reverse_prefix_sum
   
   lw    $s0, 4($sp)          # restore arr
   sw    $v0, 8($sp)          # save reverse_prefix_sum()
   
   move  $a1, $v0
   lw    $t1, 0($s0)          # *arr
   addu  $a1, $a1, $t1        # adding part
    
   sw    $a1, 0($s0)          # store value in array
    
   move  $v0, $a1 
   
      # EPILOGUE
   lw    $ra, 0($sp)
   add   $sp, $sp, 12         # destroy the stack
   jr    $ra 
    
    
   
       
