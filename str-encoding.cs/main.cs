using System;
using System.Linq;
using System.Threading;

public class Foo {
  public static void Main(string[] args) {
      byte[] s = { (byte)'a', (byte)'b', (byte)'c', (byte)'d' };
      // byte[] s = { (byte)'a' };
      for (int i = 0; i < s.Length / 2; i++) {
          byte c = s[s.Length - 1 - i];
          s[s.Length - 1 - i] = s[i];
          s[i] = c;
      }
      System.Console.WriteLine(System.Text.Encoding.Unicode.GetString(s));
  }
}
