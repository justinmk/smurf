// ilasm helloworld.asm && mono helloworld.exe
//
// monodis
//   apt-get install mono-util
// ilasm
//   apt-get install mono-devel

.assembly hello {}
.method static public void main() il managed
{
  .entrypoint
  .maxstack 8
  .locals init ([0] string str1)
  nop // used by debug builds so that breakpoints can target e.g. braces.
  nop // smurfin' around
  nop
  ldstr "hello world!!!!!!!!!!!!!!!!!!1111111111111111"
  call void [mscorlib]System.Console::WriteLine(class System.String)
  /* .locals(string V _0) */
  ldstr "string one on stack"
  stloc.0 //store string from stack into local var `str1`
  ldstr "string two on stack"
  stloc.0 //ovewrite `str1`
  ldloc.0
  call void [mscorlib]System.Console::WriteLine(class System.String)
  ret
}
