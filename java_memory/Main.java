// package smurf;
import java.util.ArrayList;
// import org.openjdk.jol.info.ClassLayout;
// import org.openjdk.jol.util.VMSupport;

public class Main {
  private static ArrayList g_cache = new ArrayList();
  private static Object[] g_array;
  private static void printMem() {
    // Get current size of heap in bytes
    long heapSize = Runtime.getRuntime().totalMemory(); 
    // Maximum heap size (bytes). Heap cannot grow beyond this size.
    // Any attempt will result in OutOfMemoryException.
    long heapMaxSize = Runtime.getRuntime().maxMemory();
    // Free memory within the heap (bytes). This size will increase after
    // garbage collection and decrease as new objects are created.
    long heapFreeSize = Runtime.getRuntime().freeMemory(); 

    System.out.println(String.format("heapSize=%.2f MB, heapMaxSize=%.2f MB, heapFreeSize=%.2f MB",
          heapSize / 1000.0 / 1000.0,
          heapMaxSize / 1000.0 / 1000.0,
          heapFreeSize / 1000.0 / 1000.0));
  }
  public static void main(String [ ] args) {
    printMem();

    // for (int i = 0; i < 1000000; i++) {
    //   g_cache.add(new Object());
    // }
    g_array = new Object[1000000];

    // System.out.println(VMSupport.vmDetails());
    // System.out.println(ClassLayout.parseClass(Integer.class).toPrintable());
    // System.out.println(String.format("objsize=%.2f",
    //       Instrumentation.getObjectSize(g_cache)));

    printMem();
  }

}

// vim: expandtab shiftwidth=2 softtabstop=-1
