using System;
using System.IO;
using System.Collections.Generic;

// A sequence of n > 0 integers is called a jolly jumper if the absolute values
// of the difference between successive elements take on all the values
// 1 through n − 1. For instance,
//    1 4 2 3
// is a jolly jumper, because the absolute differences are 3, 2, and
// 1 respectively. The definition implies that any sequence of a single
// integer is a jolly jumper. You are to write a program to determine
// whether or not each of a number of sequences is a jolly jumper.
//
// Input
//    Each line of input contains an integer n ≤ 3000 followed by n integers
//    representing the sequence.
// Output
//    For each line of input, generate a line of output saying ‘Jolly’ or ‘Not
//    jolly’.
//
// Sample Input
//    n=4 1 4 2 3
//    n=5 1 4 2 -1 6
// Sample Output
//    Jolly
//    Not jolly

namespace Smurf {
  public class JollyJumper {
    public static bool IsJolly(int[] seq) {
      int n = seq.Length;
      if (n < 1) {
        throw new ArgumentException("seq", "invalid length: "+n);
      }
      if (n == 1) {
        return true;
      }

      //Compute the "set" for n.
      var jollySet = new Dictionary<int, bool>(n);
      for(int i = 1; i <= (n - 1); i++) {
        jollySet[i] = false;
      }
      Console.WriteLine("set: "+string.Join(" ", seq));

      //Check if the input is valid ("jolly").
      for(int i = 1; i < n; i++) {
        //Compute the absolute value.
        int absval = seq[i] - seq[i-1];
        if (absval < 0) {
          absval = -absval;
        }
        if (jollySet.ContainsKey(absval)) {
          jollySet.Remove(absval);
        }
      }

      return jollySet.Count == 0;
    }

    public static void test_jolly(int[] seq) {
      Console.WriteLine(string.Join(" ", seq) + " -- jolly:" + IsJolly(seq));
    }

    public static void Main(String[] args) {
      test_jolly(new int[] { 1, 4, 2, 3});
      test_jolly(new int[] { 1, 2, 4, 2, 3});
      test_jolly(new int[] {1,4,2,3});
      test_jolly(new int[] {1,4,2,-1,6});
    }
  }
}
