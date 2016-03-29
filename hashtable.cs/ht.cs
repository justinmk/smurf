using System;
using System.Collections.Generic;

namespace Smurf {
  public class Util {
    public static uint oat_hash(String key) {
      uint h = 0;
      for(int i = 0; i < key.Length; i++) {
        h += key[i];
        h ^= (h << 10);
        h ^= (h >> 6);
      }
      h += (h << 3);
      h ^= (h >> 11);
      h += (h << 15);

      return h;
    }
  }

  public class Hashtable<T> {
    private List<T>[] buckets = new List<T>[100];
    public int GetBucket(uint hashcode) {
      unchecked {
        return (int)((uint)hashcode % buckets.Length);
      }
    }

  }

  public class EntryPoint {
    public static void HashNKeysMTimes(int m, String[] keys) {
      var ht = new Hashtable<Object>();

      foreach(var key in keys) {
        System.Console.WriteLine(
            key.PadRight(20)
              + " hcode: " + Util.oat_hash(key).ToString().PadRight(10)
              + " bnr: " + ht.GetBucket(Util.oat_hash(key)));
      }

      var s = new System.Diagnostics.Stopwatch();
      s.Start();
      for(int i = 0; i < m; i++) {
        foreach(var key in keys) {
          Util.oat_hash(key);
        }
      }
      s.Stop();
      System.Console.WriteLine(s.Elapsed);
    }

    public static void Main(String[] args) {
      HashNKeysMTimes(500000, new String[] {
        "a",
        "abc123",
        "NEOWEOIJFWEFOIJWDAS",
        "eg)(*#)($U#JRIEFDSF",
        "spoonforkKnife",
      });
    }
  }
}
