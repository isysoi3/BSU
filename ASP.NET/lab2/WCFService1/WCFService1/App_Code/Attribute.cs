using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.Threading.Tasks;
using System.Xml;
using System.Xml.Serialization;

namespace lab1.Models
{
    [Serializable()]
    public class Attribute : ISerializable
    {
        public Attribute()
        {
            Name = "";
            Type = "";
        }

        public string Name { get; set; }
        public string Type { get; set; }

        public Attribute(SerializationInfo info, StreamingContext ctxt)
        {
            //Get the values from info and assign them to the appropriate properties
            Name = (String)info.GetValue("Name", typeof(string));
            Type = (String)info.GetValue("Type", typeof(string));
        }

        public void GetObjectData(SerializationInfo info, StreamingContext ctxt)
        {

            info.AddValue("Name", Name);
            info.AddValue("Type", Type);
        }

    }
}
