using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
namespace FMS_adapter
{   
    //a program that checks to make sure all the adapters work properly
    class Program
    {
        static void Main(string[] args)
        {
            Triesite t = new Triesite("C:\\maagar", 'c');
            t.MountSite("C:\\maagar", 'm');
            t.DocUploadSite("C:\\doc1", 'c');
            t.DocIdxSite("doc1");
            List<string> s = t.GetDocNameList(1);
            t.DocdownloadSite("doc1", "C:\\");
            int c = t.ExpCountSite("doc1", "((dassie michal)|((win* he*)&(what)))");
            s=t.DocLookupSearchList("((dassie michal)|((win* he*)&(what)))");
            t.DocUploadSite("C:\\doc2", 'c');
            t.DelDocOfSite("doc2", 'p');
           // t.DelDocOfSite("doc1", 'p');
            t.UnmountSite();
            t.DelSite('p');


        }
    }
}
