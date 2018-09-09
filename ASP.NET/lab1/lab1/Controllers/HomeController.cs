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
            tableModel.name = tablename;
            tableModel.numberOfFields = fieldsnumber;

            return View(tableModel);
        }

        [HttpPost]
        public IActionResult CreatedTable(TableModel tableModel)
        {
            List<Field> listValues = new List<Field>();
            for (int i = 0; i < 3; i++)
            {
                var field = new Field();
                field.name = Request.Form[String.Format("{0} {1}", "fieldName", i)];
                field.type = Request.Form[String.Format("{0} {1}", "fieldType", i)];
                listValues.Add(field);


            }
            tableModel.fields = listValues;
            return View(tableModel);
        }

        [HttpPost]
        public IActionResult AddTableEntries(TableModel tableModel)
        {
            return View(tableModel);
        }

    }
}
