using System;
using System.Linq;
using System.Threading;

public class ProducerConsumerDemo {
  static IntBuffer _sharedBuf = null;
  static Random _rand = new Random();
  // static int _cost = 0;
  public class IntBuffer {
    int _pos = -1;
    int[] _intbuf = null;
    Object _lock = new Object();
    public IntBuffer(int size) {
      _intbuf = new int[size];
    }
    public int size() {
      return _pos+1;
    }
    public void append(int item) {
      lock (_lock) {
        while (_pos >= _intbuf.Length - 1) {
          Monitor.Wait(_lock);
        }
        _intbuf[++_pos] = item;
        print("append");
        Monitor.PulseAll(_lock);
      }
    }
    public int remove() {
      lock (_lock) {
        while (_pos < 0) {
          Monitor.Wait(_lock);
        }
        var item = _intbuf[_pos--];
        print("remove");
        Monitor.PulseAll(_lock);
        return item;
      }
    }
    private void print(string caller) {
        Console.WriteLine(string.Format("{0}: {1}",
              caller, string.Join(",",_intbuf.Take(size()))));
    }
  }
  public static void consumer() {
    while(true) {
      _sharedBuf.remove();
      Thread.Sleep(1);
      // Thread.Yield();
    }
  }
  public static void producer() {
    while(true) {
      _sharedBuf.append(_rand.Next());
      // Thread.Yield();
    }
  }

  public static void Main(string[] args) {
    _sharedBuf = new IntBuffer(8);
    var p = new Thread(producer);
    var c = new Thread(consumer);
    p.Start();
    c.Start();
    p.Join();
    c.Join();
  }
}
