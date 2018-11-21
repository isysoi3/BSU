using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace GeneratingTockenProject.Models
{
    public class Token
    {
        public int value { set; get; }
        public System.Data.SqlTypes.SqlDateTime expireDate { set; get; }
    }
}
