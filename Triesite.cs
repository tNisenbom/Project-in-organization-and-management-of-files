using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace FMS_adapter
{
    public class Triesite
    {
        IntPtr myTriesitePointer;

        public Triesite()
        {
            try
            {
                this.myTriesitePointer = cppToCsharpAdapter.makeTriesiteObjectDefault();
            }
            catch (Exception ex)
            {

                throw ex;
            }
        }
        public Triesite(string siteName, char x, char y = 'q')
        {
            try
            {

                this.myTriesitePointer = cppToCsharpAdapter.makeTriesiteObject(siteName, x, y);
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastTriesiteErrorMessage(this.myTriesitePointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }
        ~Triesite()
        {
            if (myTriesitePointer != null)
                cppToCsharpAdapter.deleteTriesiteObject(ref myTriesitePointer);
        }

        //step 1
        public void CreateSite(string path)
        {
            try
            {
                cppToCsharpAdapter.CreateSite(this.myTriesitePointer, path);
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastTriesiteErrorMessage(this.myTriesitePointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }
        public void MountSite(string path, char qORm)
        {
            try
            {
                cppToCsharpAdapter.MountSite(this.myTriesitePointer, path, qORm);
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastTriesiteErrorMessage(this.myTriesitePointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }
        public void UnmountSite()
        {
            try
            {
                cppToCsharpAdapter.UnmountSite(this.myTriesitePointer);
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastTriesiteErrorMessage(this.myTriesitePointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }
        public void PutStopFlSite(string stopName)
        {
            try
            {
                cppToCsharpAdapter.PutStopFlSite(this.myTriesitePointer, stopName);
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastTriesiteErrorMessage(this.myTriesitePointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }

        //step 2
        public void DocUploadSite(string docName, char cORm)
        {
            try
            {
                cppToCsharpAdapter.DocUploadSite(this.myTriesitePointer, docName, cORm);
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastTriesiteErrorMessage(this.myTriesitePointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }
        public void DocdownloadSite(string docName, string destPath)
        {
            try
            {
                cppToCsharpAdapter.DocdownloadSite(this.myTriesitePointer, docName, destPath);
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastTriesiteErrorMessage(this.myTriesitePointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }
        public void DelSite(char lORp)
        {
            try
            {
                cppToCsharpAdapter.DelSite(this.myTriesitePointer, lORp);
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastTriesiteErrorMessage(this.myTriesitePointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }
        public void DelDocOfSite(string destPath, char lORp)
        {
            try
            {
                cppToCsharpAdapter.DelDocOfSite(this.myTriesitePointer, destPath, lORp);
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastTriesiteErrorMessage(this.myTriesitePointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }

        //step 3
        public void DocIdxSite(string docName)
        {
            try
            {
                cppToCsharpAdapter.DocIdxSite(this.myTriesitePointer, docName);
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastTriesiteErrorMessage(this.myTriesitePointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }
        public List<string> GetDocNameList(int shoise)
        {
            StringCppArray s;

            try
            {
                cppToCsharpAdapter.GetDocNameList(this.myTriesitePointer, out s, shoise);
                List<string> result = new List<string>();
                foreach (string item in s)
                {
                    result.Add(item);
                }

                return result;

            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastTriesiteErrorMessage(this.myTriesitePointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
            finally
            {
                cppToCsharpAdapter.deleteStringArray(out s);
            }
        }

        //step 4
        public string ExpSearchSite(string docName, string expression)
        {
            try
            {
                IntPtr str;
                cppToCsharpAdapter.ExpSearchSite(this.myTriesitePointer, out str, docName, expression);
                string result = Marshal.PtrToStringAnsi(str);
                cppToCsharpAdapter.deleteCharPointer(out str);
                return result;
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastTriesiteErrorMessage(this.myTriesitePointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }
        public int ExpCountSite(string docName, string expression)
        {
            try
            {
                return cppToCsharpAdapter.ExpCountSite(this.myTriesitePointer, docName, expression);
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastTriesiteErrorMessage(this.myTriesitePointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }
        public List<string> DocLookupSearchList(string expression)
        {
            StringCppArray s;

            try
            {
                cppToCsharpAdapter.DocLookupSearchList(this.myTriesitePointer, out s, expression);
                List<string> result = new List<string>();
                foreach (string item in s)
                {
                    result.Add(item);
                }

                return result;

            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastTriesiteErrorMessage(this.myTriesitePointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
            finally
            {
                cppToCsharpAdapter.deleteStringArray(out s);
            }
        }
        public int GetNumSearches(string docName)
        {
            try
            {
                return cppToCsharpAdapter.GetNumSearches(this.myTriesitePointer, docName);
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastTriesiteErrorMessage(this.myTriesitePointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }
    }

}
