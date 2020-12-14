# name: Stephane Zabayo
# ID: 116998604
# Directory ID: szabayo

 
fibonacci:

   bgt   $a0, 1, fib
   move  $v0, $a0
   jr    $ra
   
fib:
       # PROLOGUE
   sub   $sp, $sp, 12
   sw    $ra, 0($sp)     #save $ra
   
   sw    $a0, 4($sp)     #save n
   
       # BODY
   add   $a0, $a0, -1    #n-1
   
   jal   fibonacci       
   
   lw    $a0, 4($sp)     # restore n
   sw    $v0, 8($sp)     # save fibonacci(n-1)
   
   add   $a0, $a0, -2    # n-2
   
   jal   fibonacci
   
   lw    $t0, 8($sp)     # restore fibonacci(n-1)
   add   $v0, $t0, $v0   # adding value
   
      # EPILOGUE
   lw    $ra, 0($sp)     # restore $ra
   add   $sp, $sp, 12    # destroy stack
   
   jr    $ra     
