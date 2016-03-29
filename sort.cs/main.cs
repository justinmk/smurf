using System;
using System.Linq;

public partial class SmurfSort {
  static int _cost = 0;

  // O(n^2) Sorts an array in-place in ascending order.
  public static T[] bubbletrouble<T>(T[] list)
    where T : IComparable
  {
    for(int i = 0; i < list.Length; i++) {
      for(int j = 0; j < list.Length; j++) {
        _cost++;
        if (-1 == list[i].CompareTo(list[j])) {
          T tmp = list[j];
          list[j] = list[i];
          list[i] = tmp;
        }
      }
    }
    return list;
  }

  private static void _swap<T>(T[] list, int i, int j) {
    T tmp = list[i];
    list[i] = list[j];
    list[j] = tmp;
  }
  private static int qsort_partition<T>(T[] list,
      int l /*"low",start*/, int h /*"high",end*/)
    where T : IComparable
  {
    // int pivot = l + ((h - l) / 2);
    T pivotVal = list[h];
    int k = l;
    for (int i = l; i < h; i++) {
      _cost++;
      if (list[i].CompareTo(pivotVal) < 0) {
        _swap(list, k, i);
        k++;
      }
    }
    _swap(list, h, k);
    return k;
  }
  public static T[] qsort<T>(T[] list, int l, int h)
    where T : IComparable
  {
    if (h <= l) {
      return list;
    }
    int pivot = qsort_partition(list, l, h);
    qsort(list, l, pivot - 1);
    qsort(list, pivot + 1, h);
    return list;
  }

  public static void do_test<T>(Action<T[]> sortFn, T[] seq) {
    _cost = 0;
    var sw = System.Diagnostics.Stopwatch.StartNew();
    sortFn(seq);
    sw.Stop();
    Console.WriteLine("cost: {0} time: {1}",_cost, sw.Elapsed);
    Console.WriteLine(string.Join("\n", seq));
  }

  public static void Main(string[] args) {
    int[] seq1 = {7,8,3,234,23234,4,6,7,42,8,5,7,99,743,2,2,4,77,9,4,235,23235,7,9,10,45,11,8,10,102,746,6,6,8,10};
    int[] seq2 = {8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,};
    do_test((seq) => { bubbletrouble(seq); }, _unsorted1.Select(x=>x).ToArray());
    // do_test((seq) => { bubbletrouble(seq); }, seq1.Select(x=>x).ToArray());
    // do_test((seq) => { qsort(seq, 0, seq.Length-1); }, seq1.Select(x=>x).ToArray());
    // do_test((seq) => { qsort(seq, 0, seq.Length-1); }, _unsorted1.Select(x=>x).ToArray());
  }
}
