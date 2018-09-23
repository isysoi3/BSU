using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using lab1.Models;
using System.Data.SqlClient;

namespace lab1.Controllers
{
    public class HomeController : Controller
    {

        public IActionResult Index()
        {
            return View();
        }

        [HttpPost]
        public IActionResult Table(string tablename, int fieldsnumber)
        {
            TableModel tableModel = new TableModel();
            tableModel.Name = tablename;
            tableModel.NumberOfAttributes = fieldsnumber;

            return View(tableModel);
        }

        [HttpPost]
        public IActionResult CreatedTable(string tablename, int fieldsnumber)
        {
            TableModel tableModel = new TableModel();
            tableModel.Name = tablename;
            tableModel.NumberOfAttributes = fieldsnumber;

            List<String> valuesToInsert = new List<String>();
            List<Models.Attribute> listValues = new List<Models.Attribute>();
            for (int i = 0; i < fieldsnumber; i++)
            {
                var field = new Models.Attribute();
                field.Name = Request.Form[String.Format("{0} {1}", "fieldName", i)];
                field.Type = Request.Form[String.Format("{0} {1}", "fieldType", i)];
                listValues.Add(field);

               
                valuesToInsert.Add(Request.Form[field.Name]);
            }
            tableModel.Attributes = listValues;


            if (valuesToInsert[0] != null)
            {
                try
                {
                    AddToTableInBD(tableModel, valuesToInsert);
                }
                catch
                {
                    return NoContent();
                }
                return View(tableModel);
            }
            else
            {
                try
                {
                    CreateTableInBD(tableModel);
                }
                catch
                {
                    return NoContent();
                }
                return View(tableModel);
            }

        }

        private void CreateTableInBD(TableModel table)
        {
            using (SqlConnection connection = new SqlConnection("Server=localhost;Database=critters;Trusted_Connection=True;"))
            {
                string queryString = "CREATE TABLE " + table.Name + " (";
                foreach (Models.Attribute attribute in table.Attributes)
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

        [HttpPost]
        public IActionResult AddTableEntries(string tablename,
            int fieldsnumber,
            List<Models.Attribute> attributes)
        {
            TableModel tableModel = new TableModel();
            tableModel.Name = tablename;
            tableModel.NumberOfAttributes = fieldsnumber;

            List<Models.Attribute> listValues = new List<Models.Attribute>();
            
            for (int i = 0; i < fieldsnumber; i++)
            {
                var field = new Models.Attribute();
                field.Name = Request.Form[String.Format("{0} {1}", "fieldName", i)];
                field.Type = Request.Form[String.Format("{0} {1}", "fieldType", i)];
                listValues.Add(field);
            }

            tableModel.Attributes = listValues;

            return View(tableModel);
        }

        private void AddToTableInBD(TableModel table,
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
}
