using Interop.MyX64COMComponent;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace CSharpTestHarness
{
    class Program
    {
        static void Main(string[] args)
        {
            try
            {
                IMySampleCOMObject obj = new MySampleCOMObjectClass();
                String processDetails = obj.GetProcessDetails();
                Console.WriteLine($"COM Lubrary returned: {processDetails}");
            }
            catch(Exception ex)
            {
                Console.WriteLine($"error occurred:{ex.Message}, stack Trace: {ex.StackTrace}");
            }

            Test2();

            Console.WriteLine("press any key to exit...");
            Console.ReadKey();
        }

        /*
         * https://www.codeproject.com/Tips/1199539/Using-64-bit-DLLs-in-32-bit-Processes-with-Out-of
         * 
         */
        static void Test2()
        {
            
            Type ComType = Type.GetTypeFromCLSID(System.Guid.Parse("6e175df4-ef68-4a87-9eeb-27316d1703a7"), Environment.MachineName);
                      
            object ComObject = Activator.CreateInstance(ComType);
            string result = (string)ComType.InvokeMember("GetProcessDetails", BindingFlags.InvokeMethod, null, ComObject, null);
            Console.WriteLine("Result of \"GetProcessDetails\" is: " + result.ToString());

            // Don't forget to release the late bound COM object,
            // otherwise the surrogate process (dllhost.exe) would live forever
            if (Marshal.IsComObject(ComObject))
                Marshal.ReleaseComObject(ComObject);
        }
    }
}
