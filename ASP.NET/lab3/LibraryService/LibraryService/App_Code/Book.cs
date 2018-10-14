using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.Web;

/// <summary>
/// Сводное описание для Book
/// </summary>

[Serializable()]
public class Book: ISerializable
{
    public int ID { get; set; }
    public string Name { get; set; }
    public string AuthorName { get; set; }
    public bool IsAvailable { get; set; }

    public Book()
    {
        ID = 0;
        Name = "";
        AuthorName = "";
        IsAvailable = false;
    }

    public Book(SerializationInfo info, StreamingContext ctxt)
    {
        ID = (int)info.GetValue("ID", typeof(int));
        Name = (String)info.GetValue("Name", typeof(string));
        AuthorName = (String)info.GetValue("AuthorName", typeof(string));
        IsAvailable = (bool)info.GetValue("IsAvailable", typeof(bool));
    }

    public void GetObjectData(SerializationInfo info, StreamingContext ctxt)
    {
        info.AddValue("ID", ID);
        info.AddValue("Name", Name);
        info.AddValue("AuthorName", AuthorName);
        info.AddValue("IsAvailable", IsAvailable);
    }

}