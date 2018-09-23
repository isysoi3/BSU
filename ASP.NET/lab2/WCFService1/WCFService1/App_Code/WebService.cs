using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Services;
using System.Data.SqlClient;
using lab1.Models;

/// <summary>
/// Сводное описание для WebService
/// </summary>

[WebServiceBinding(ConformsTo = WsiProfiles.BasicProfile1_1)]
[WebService(Description = "Lab2", Namespace = XmlNS)]
public class WebService : System.Web.Services.WebService
{
    public const string XmlNS = "http://asmx.lab2.com/";

    public WebService()
    {
        //InitializeComponent(); 
    }

    [WebMethod]
    public void CreateTableInBD(TableModel table)
    {
        using (SqlConnection connection = new SqlConnection("Server=localhost;Database=critters;Trusted_Connection=True;"))
        {
            string queryString = "CREATE TABLE " + table.Name + " (";
            foreach (lab1.Models.Attribute attribute in table.Attributes)
            {
                queryString += attribute.Name + " " + attribute.Type + ", ";
            }
            int lastComma = queryString.LastIndexOf(",");
            queryString = queryString.Substring(0, lastComma);
            queryString += ");";
            SqlCommand command = new SqlCommand(queryString, connection);
            command.Connection.Open();
            command.ExecuteNonQuery();

        }
    }

    [WebMethod]
    public void AddToTableInBD(TableModel table,
         List<String> valuesToInsert)
    {
        using (SqlConnection connection = new SqlConnection("Server=localhost;Database=critters;Trusted_Connection=True;"))
        {
            string queryString = "INSERT INTO " + table.Name + " VALUES (";
            foreach (var value in valuesToInsert)
            {
                queryString += value + ", ";
            }
            int lastComma = queryString.LastIndexOf(",");
            queryString = queryString.Substring(0, lastComma);
            queryString += ");";
            SqlCommand command = new SqlCommand(queryString, connection);
            command.Connection.Open();
            command.ExecuteNonQuery();
        }
    }

}
