using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;
using System.Collections;

namespace FMS_adapter
{

    public class cppToCsharpAdapter
    {
        const string dllPath = "FMS_DLL.dll";

        // for string and List<string>
        [DllImport(dllPath, CallingConvention = CallingConvention.Cdecl)]
        public static extern void deleteCharPointer(out IntPtr charPointer);

        [DllImport(dllPath, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr makeTriesiteObjectDefault();

        [DllImport(dllPath, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr makeTriesiteObject(string siteName, char x, char y);

        // for create triesite cpp object pointer
        [DllImport(dllPath, CallingConvention = CallingConvention.Cdecl)]
        public static extern void deleteTriesiteObject(ref IntPtr ThisPointer);

        [DllImport(dllPath, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr getLastTriesiteErrorMessage(IntPtr ThisPointer);

        [DllImport(dllPath, CallingConvention = CallingConvention.Cdecl)]
        public static extern void deleteStringArray(out StringCppArray stringArray);

        //step 1
        [DllImport(dllPath, CallingConvention = CallingConvention.Cdecl)]
        public static extern void CreateSite(IntPtr ThisPointer, string path);

        [DllImport(dllPath, CallingConvention = CallingConvention.Cdecl)]
        public static extern void MountSite(IntPtr ThisPointer, string path, char qORm);

        [DllImport(dllPath, CallingConvention = CallingConvention.Cdecl)]
        public static extern void UnmountSite(IntPtr ThisPointer);

        [DllImport(dllPath, CallingConvention = CallingConvention.Cdecl)]
        public static extern void PutStopFlSite(IntPtr ThisPointer, string stopName);

        //step 2
        [DllImport(dllPath, CallingConvention = CallingConvention.Cdecl)]
        public static extern void DocUploadSite(IntPtr ThisPointer, string docName, char cORm);

        [DllImport(dllPath, CallingConvention = CallingConvention.Cdecl)]
        public static extern void DocdownloadSite(IntPtr ThisPointer, string docName, string destPath);

        [DllImport(dllPath, CallingConvention = CallingConvention.Cdecl)]
        public static extern void DelSite(IntPtr ThisPointer, char lORp);

        [DllImport(dllPath, CallingConvention = CallingConvention.Cdecl)]
        public static extern void DelDocOfSite(IntPtr ThisPointer, string destPath, char lORp);

        //step 3
        [DllImport(dllPath, CallingConvention = CallingConvention.Cdecl)]
        public static extern void DocIdxSite(IntPtr ThisPointer, string docName);

        [DllImport(dllPath, CallingConvention = CallingConvention.Cdecl)]
        public static extern StringCppArray GetDocNameList(IntPtr ThisPointer, out StringCppArray stringArray, int shoise);

        //step 4
        [DllImport(dllPath, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ExpSearchSite(IntPtr ThisPointer, out IntPtr resultPointer, string docName, string expression);

        [DllImport(dllPath, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ExpCountSite(IntPtr ThisPointer, string docName, string expression);

        [DllImport(dllPath, CallingConvention = CallingConvention.Cdecl)]
        public static extern StringCppArray DocLookupSearchList(IntPtr ThisPointer, out StringCppArray stringArray, string expression);

        [DllImport(dllPath, CallingConvention = CallingConvention.Cdecl)]
        public static extern int GetNumSearches(IntPtr ThisPointer, string docName);
    }
}
