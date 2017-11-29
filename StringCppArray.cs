using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace FMS_adapter
{
    public struct StringCppArray : IEnumerable
    {
        private int size;
        public int Size
        {
            get { return size; }
            set { size = value; }
        }

        private IntPtr arr;
        public string[] Arr
        {
            get
            {
                int x = size;
                string[] result = new string[x];
                IntPtr[] ptrs = new IntPtr[x];
                Marshal.Copy(arr, ptrs, 0, x);

                for (int i = 0; i < x; i++)
                    result[i] = Marshal.PtrToStringAnsi(ptrs[i]);

                return result;
            }
            set
            {

                this.size = value.Length;

                IntPtr[] ptrs = new IntPtr[size];
                for (int i = 0; i < size; i++)
                    ptrs[i] = Marshal.StringToHGlobalAnsi(value[i]);

                this.arr = Marshal.UnsafeAddrOfPinnedArrayElement(ptrs, 0);
            }
        }


        public IEnumerator GetEnumerator()
        {
            return this.Arr.GetEnumerator();
        }
    }


}
