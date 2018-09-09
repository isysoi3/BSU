using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace lab1.Models
{
    public class TableModel
    {

        public TableModel()
        {

        }

        public TableModel(TableModel tableModel)
        {
            this.name = tableModel.name;
            this.numberOfFields = tableModel.numberOfFields;
            this.fields = tableModel.fields;
        }

        public string name { get; set; }
        public int numberOfFields { get; set; }
        public List<Field> fields { get; set; }
    }

    public class Field
    {
        public string name { get; set; }
        public string type { get; set; }
    }
}
