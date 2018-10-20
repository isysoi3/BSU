using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using LibraryClient.Models;
using LibraryServiceReference;

namespace LibraryClient.Controllers
{
    public class HomeController : Controller
    {
        public async Task<IActionResult> AllBooks()
        {
            LibraryServiceSoapClient.EndpointConfiguration endpointConfiguration = LibraryServiceSoapClient.EndpointConfiguration.LibraryServiceSoap;
            var client = new LibraryServiceSoapClient(endpointConfiguration);
            var requestBody = new GetAllBooksRequest();
            requestBody.Body = new GetAllBooksRequestBody("get123");

            var result = await client.GetAllBooksAsync(requestBody);
            if(result.Body.GetAllBooksResult == null || result.Body.GetAllBooksResult.Length == 0)
            {
                return View("Error");
            }
            return View(result.Body.GetAllBooksResult.ToList());
        }




        public IActionResult Error()
        {
            return View();
        }

    }
}
