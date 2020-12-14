# name: Stephane Zabayo
# ID: 116998604
# Directory ID: szabayo


isqrt:

   bge  $a0, 2, isq         #if statemenn >2
   move $v0, $a0
   jr   $ra
   
   
isq:
      # PROLOGUE
   sub  $sp, $sp, 12        # create stack
   sw   $ra, 0($sp)         # save $ra
   
   sw   $a0, 4($sp)         # save n
   
      # BODY
   
   srl  $a0, $a0, 2         # modifying bit  n >> 2
   
   jal  isqrt
   
   lw   $a0, 4($sp)         #restore n
   sw   $v0, 8($sp)         #save isqrt()
   
   move $a1, $v0
   sll  $t0, $a1, 1         # small is $t0
   add  $t1, $t0, 1         # large
   
   mul  $t2, $t1, $t1       # large*large
   
   bgt  $t2, $a0, then      # if  > than
   add  $v0, $zero, $t1
   
      # EPILOGUE
   lw   $ra, 0($sp)
   add  $sp, $sp, 12        #destroying stack
   jr   $ra
   
then:
   add  $v0, $zero, $t0
   lw   $ra, 0($sp)
   add  $sp, $sp, 12        #destroying stack
   jr   $ra   
   
   
   
   
   
