using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using lab1.Models;

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
            return View(tableModel);
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


            }
            tableModel.Attributes = listValues;

            return View(tableModel);
        }

    }
}
