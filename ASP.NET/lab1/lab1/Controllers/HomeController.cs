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
            using (SqlConnection connection = new SqlConnection("Server=localhost\\SQLEXPRESS;Database=critters;Trusted_Connection=True;"))
            {
                string queryString = "CRATE TABLE " + table.Name + "(";
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
            for (int i = 0; i < 3; i++)
            {
                var field = new Models.Attribute();
                field.Name = Request.Form[String.Format("{0} {1}", "fieldName", i)];
                field.Type = Request.Form[String.Format("{0} {1}", "fieldType", i)];
                listValues.Add(field);

                var rez = Request.Form["field.Name"];
                if (field.Type == "INT")
                {
                    var tmp = int.Parse(rez);
                } else if (field.Type == "FLOAT")
                {
                    var tmp = double.Parse(rez);
                }

            }
            tableModel.Attributes = listValues;

            return View(tableModel);
        }

    }
}
