using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.Threading.Tasks;

namespace lab1.Models
{
    [Serializable()]
    public class TableModel : ISerializable
    {
        public TableModel()
        {
            Name = "";
            NumberOfAttributes = 0;
            Attributes = new List<Attribute>();
        }
      
        public string Name { get; set; }
        public int NumberOfAttributes { get; set; }
        public List<Attribute> Attributes { get; set; }


        public TableModel(SerializationInfo info, StreamingContext ctxt)
        {
            //Get the values from info and assign them to the appropriate properties
            Name = (String)info.GetValue("Name", typeof(string));
            NumberOfAttributes = (int)info.GetValue("NumberOfAttributes", typeof(int));
            Attributes = (List<Attribute>)info.GetValue("Attributes", typeof(List<Attribute>));
        }

        public void GetObjectData(SerializationInfo info, StreamingContext ctxt)
        {

            info.AddValue("Name", Name);
            info.AddValue("NumberOfAttributes", NumberOfAttributes);
            info.AddValue("Attributes", Attributes);
        }

        public ServiceReference.TableModel ConvertToServiceModel()
        {
            List<ServiceReference.Attribute> attributesToWebService = new List<ServiceReference.Attribute>();

            foreach (var attribute in Attributes)
            {
                attributesToWebService.Add(
                    new ServiceReference.Attribute
                    {
                        Name = attribute.Name,
                        Type = attribute.Type
                    }
               );
            }

            ServiceReference.TableModel tableModelToWebService = new ServiceReference.TableModel()
            {
                Name = this.Name,
                NumberOfAttributes = this.NumberOfAttributes,
                Attributes = attributesToWebService.ToArray()

            };
            return tableModelToWebService;
        }

    }
}
