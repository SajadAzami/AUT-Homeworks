
namespace ReaderWriter
{
    using System.Diagnostics;
    using System.Threading;
    class Program
    {
        
        static void Main(string[] args)
        {
            new my_Sem();
            System.Console.ReadKey(); // exit
        }
        
    }
    class my_Sem
    {
        int val = 0;
        Semaphore sem = new Semaphore(2, 3);
        void readers_proc()
        {
            while (true)
            {
                sem.WaitOne();
                System.Console.WriteLine("{0} : voroud", Thread.CurrentThread.Name);
                System.Console.WriteLine("{0} : val = {1}", Thread.CurrentThread.Name, val.ToString());
                Thread.Sleep(300);
                if (val == 10)
                    Thread.CurrentThread.Abort();
                sem.Release();
                System.Console.WriteLine("{0} : khorouj", Thread.CurrentThread.Name);
            }
        }
        void writer_proc()
        {
            while (true)
            {
                
                sem.WaitOne();
                System.Console.WriteLine("{0} : voroud", Thread.CurrentThread.Name);
                val++;
                System.Console.WriteLine("{0} : val taqir be {1}", Thread.CurrentThread.Name, val);
                Thread.Sleep(500);
                if (val == 10)
                    Thread.CurrentThread.Abort();
                sem.Release();
                System.Console.WriteLine("{0} : khorouj", Thread.CurrentThread.Name);

            }
        }
        public my_Sem()
        {
            var r1 = new Thread(readers_proc) {/*ID*/ Name = "0x00000001" };
            var r2 = new Thread(readers_proc) {/*ID*/ Name = "0x00000002" };
            var w = new Thread(writer_proc) {/*ID*/ Name = "0x00000003" };
            
            
            r1.Start();
            r2.Start();
            w.Start();
            
        }
    }
}
