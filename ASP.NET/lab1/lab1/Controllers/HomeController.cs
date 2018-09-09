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


        public IActionResult CreatedTable()
        {
            return View();
        }

    }
}
