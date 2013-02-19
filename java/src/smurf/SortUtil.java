package smurf;

import java.util.Arrays;


public class SortUtil {
  
  public static int[] mergesort(int[] a) {
    if (null == a)
      return null;
    if (0 == a.length)
      return new int[0];
    if (a.length == 1) 
      return new int[] { a[0] };
    if (a.length < 0) //can never happen
      throw new IndexOutOfBoundsException();
    
    //midpoint: 7/2=>3 6/2=>3 2/2=1 3/2=1
    int midpoint = a.length / 2;
    int lenleft = midpoint;
    int lenright = a.length - lenleft;
    //bisect
    int[] left = Arrays.copyOf(a, lenleft);
    int[] right = Arrays.copyOfRange(a, lenleft, a.length);
    int[] merged = new int[a.length];
    
    left = mergesort(left);
    right = mergesort(right);
    
    // [1,3] [2,5] => [1,2] [3] [5] => [1,2,3] [5] => [1,2,3,5]
    int l=0;
    int r=0;
    for (int i = 0; i < merged.length; i++) {
      if (l >= left.length)
        merged[i] = right[r++];
      else if (r >= right.length)
        merged[i] = left[l++];
      else if (left[l] < right[r]) 
        merged[i] = left[l++]; 
      else 
        merged[i] = right[r++];
    }
    
    return merged;
  }

  //sorts an array in ascending order using the world's most maligned sorting algorithm.
  public static void bubblesort(int[] a /*unsorted*/) {
    for (int i = 0; i < a.length; i++) {
      for (int j = 0; j < a.length; j++) {
        if (a[j] > a[i]) {
          int tmp = a[i];
          a[i] = a[j];
          a[j] = tmp;
        }
      }
    }
  }
}
