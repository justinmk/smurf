https://msdn.microsoft.com/en-us/library/system.reflection.emit.opcodes_fields(v=vs.110).aspx

ldc.i4.m1     Push -1 onto the stack as int32.
ret           This instruction is used to exit a method and return a value to
              the caller. (if there is any)
ldc.i4.s num  Push num onto the s;ack as int32 
ldloc.x       Load local variable x on the stack.
ldstr         Loads the string on the stack.
ldloca        Load memory address of local variable.
ldfld         Loads field from an object onto the stack
stfld         Stores value from the stack into an object's field
ldc.*         used to load constants of type int32,int62,float32,float64.
ldarg         Loads by-value argument.
br target     Branch to target.The br instruction unconditionally transfers
              control to target. target is signed offset 4 bytes
br.s target   Branch to target, short form. Target is represented as 1 byte.
ldarga        Loads by-reference argument.
stloc.n       Pop a value from stack and store into local variable at index n.
clt           Compares less than. Returns 1 or 0
starg.n       Pop off the value from the stack ans store into the method argument at index n.
pop           Only Pops off the value from the stack
blt target    The blt instruction transfers control to target if value1 is less than value2.
bgt target    transfers control to target if value1 is greater than value2.
