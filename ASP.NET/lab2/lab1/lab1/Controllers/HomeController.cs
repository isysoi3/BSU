using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using lab1.Models;
using ServiceReference;
using System.Net;
using System.Xml;
using System.IO;

namespace lab1.Controllers
{
    public class HomeController : Controller
    {
        public IActionResult Index()
        {
            return View();
        }

        public IActionResult Error()
        {
            return View();
        }

        [HttpPost]
        public IActionResult Table(string tablename, int fieldsnumber)
        {
            Models.TableModel tableModel = new Models.TableModel
            {
                Name = tablename,
                NumberOfAttributes = fieldsnumber
            };

            return View(tableModel);
        }

        [HttpPost]
        public async Task<IActionResult> CreatedTable(string tablename, int fieldsnumber)
        {
            Models.TableModel tableModel = new Models.TableModel
            {
                Name = tablename,
                NumberOfAttributes = fieldsnumber
            };

            List<String> valuesToInsert = new List<String>();
            List<Models.Attribute> listValues = new List<Models.Attribute>();
            for (int i = 0; i < fieldsnumber; i++)
            {
                var field = new Models.Attribute
                {
                    Name = Request.Form[String.Format("{0} {1}", "fieldName", i)],
                    Type = Request.Form[String.Format("{0} {1}", "fieldType", i)]
                };
                listValues.Add(field);


                valuesToInsert.Add(Request.Form[field.Name]);
            }
            tableModel.Attributes = listValues;


            WebServiceSoapClient.EndpointConfiguration endpointConfiguration = WebServiceSoapClient.EndpointConfiguration.WebServiceSoap;
            var client = new WebServiceSoapClient(endpointConfiguration);
            if (valuesToInsert[0] != null)
            {

                var arrString = new ArrayOfString();
                arrString.AddRange(valuesToInsert);
                var tmp = await client.AddToTableInBDAsync(tableModel.ConvertToServiceModel(), arrString);
                if (tmp.Body.AddToTableInBDResult)
                {
                    return View(tableModel);
                }
                return View("Error");  
            }
            else
            {
                var tmp = await client.CreateTableInBDAsync(tableModel.ConvertToServiceModel());
                if (tmp.Body.CreateTableInBDResult)
                {
                    return View(tableModel);
                }
                return View("Error");
            }

        }

        [HttpPost]
        public IActionResult AddTableEntries(string tablename,
            int fieldsnumber,
            List<Models.Attribute> attributes)
        {
            Models.TableModel tableModel = new Models.TableModel();
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

    }
}
