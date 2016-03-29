using System;
using System.IO;
using System.Collections.Generic;

namespace Smurf {
  public class EntryPoint {
    public static void Main(String[] args) {
      var bytes = new byte[] { 0x1, 0x2f, 0x1b, 10, 0x0D, 0x00, 10 };
      using(var f = File.Create("Xtest")) {
        f.Write(bytes, 0, 7);
      }
      Console.WriteLine("file bytes: " + File.ReadAllText("Xtest"));
      Console.WriteLine("last byte: " + File.ReadAllBytes("Xtest")[6]);
    }
  }
}
