using System;
using System.Text;
using System.Diagnostics;

class Program
{
    static void Foo(int counter, int limit)
    {
        try
        {
            if (counter == limit)
            {
                return ;
            }
            Foo(++counter, limit);

            // System.Threading.Thread.Sleep(1);
        }
        catch (Exception)
        {
            throw;
        }
    }

    static int Sum(int s)
    {
        if (s == 1)
        {
            return s;
        }
        return s + Sum(s - 1);
    }

    static int Bar(int d)
    {
      return  d = 10 + d;
    }

    static void Main(string[] args)
    {
        int i = 0;

        Foo(i, 10000); // jitter 
        Sum(10000);

        Stopwatch stopwatch = new Stopwatch();
        stopwatch.Start();
        Foo(i, 10000);
        stopwatch.Stop();
        Console.WriteLine(string.Format("time of execution = {0}ms",stopwatch.ElapsedMilliseconds));

        stopwatch = new Stopwatch();
        stopwatch.Start();
        Sum(10000);
        stopwatch.Stop();
        Console.WriteLine(string.Format("time of execution = {0}ms", stopwatch.ElapsedMilliseconds));
    }
}
