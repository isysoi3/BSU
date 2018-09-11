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

            List<Models.Attribute> listValues = new List<Models.Attribute>();
            for (int i = 0; i < 3; i++)
            {
                var field = new Models.Attribute();
                field.Name = Request.Form[String.Format("{0} {1}", "fieldName", i)];
                field.Type = Request.Form[String.Format("{0} {1}", "fieldType", i)];
                listValues.Add(field);


            }
            tableModel.Attributes = listValues;
            if (CreateTableInBD(tableModel)) {
                return View(tableModel);
            }
            return NoContent();
           
        }

        private bool CreateTableInBD(TableModel table)
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
                if (command.ExecuteNonQuery() > 0) {
                    return true;
                }

                return false;
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
            List<String> valuesToInsert = new List<String>();
            for (int i = 0; i < 3; i++)
            {
                var field = new Models.Attribute();
                field.Name = Request.Form[String.Format("{0} {1}", "fieldName", i)];
                field.Type = Request.Form[String.Format("{0} {1}", "fieldType", i)];
                listValues.Add(field);

                valuesToInsert.Add(Request.Form["field.Name"]);
            }
            tableModel.Attributes = listValues;

            if (valuesToInsert.Count > 0)
            {
                if (AddToTableInBD(tableModel, valuesToInsert))
                {
                    return View(tableModel);
                }
            }

            return View(tableModel);
        }

        private bool AddToTableInBD(TableModel table,
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
                if (command.ExecuteNonQuery() > 0)
                {
                    return true;
                }

                return false;
            }
        }

    }
}
