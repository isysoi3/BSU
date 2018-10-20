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
            var request = new GetAllBooksRequest();
            request.Body = new GetAllBooksRequestBody("get123");

            var result = await client.GetAllBooksAsync(request);
            if(result.Body.GetAllBooksResult == null || result.Body.GetAllBooksResult.Length == 0)
            {
                return View("Error");
            }
            return View(result.Body.GetAllBooksResult.ToList());
        }

        public async Task<IActionResult> AllAvailableBooks()
        {
            LibraryServiceSoapClient.EndpointConfiguration endpointConfiguration = LibraryServiceSoapClient.EndpointConfiguration.LibraryServiceSoap;
            var client = new LibraryServiceSoapClient(endpointConfiguration);
            var request = new GetAllAvailableBooksRequest();
            request.Body = new GetAllAvailableBooksRequestBody("get123");

            var result = await client.GetAllAvailableBooksAsync(request);
            if (result.Body.GetAllAvailableBooksResult == null || result.Body.GetAllAvailableBooksResult.Length == 0)
            {
                return View("Error");
            }
            return View(result.Body.GetAllAvailableBooksResult.ToList());
        }


        public async Task<IActionResult> Order(int bookId)
        {
            LibraryServiceSoapClient.EndpointConfiguration endpointConfiguration = LibraryServiceSoapClient.EndpointConfiguration.LibraryServiceSoap;
            var client = new LibraryServiceSoapClient(endpointConfiguration);
            var request = new OrderBookRequest();
            request.Body = new OrderBookRequestBody("ord123", bookId);
            var result = await client.OrderBookAsync(request);

            //TODO: errors

            return View("AllBooks");
        }

        public async Task<IActionResult> Return(int bookId)
        {
            LibraryServiceSoapClient.EndpointConfiguration endpointConfiguration = LibraryServiceSoapClient.EndpointConfiguration.LibraryServiceSoap;
            var client = new LibraryServiceSoapClient(endpointConfiguration);
            var request = new ReturnBookRequest();
            request.Body = new ReturnBookRequestBody("ret123", bookId);
            var result = await client.ReturnBookAsync(request);

            //TODO: errors

            return View("AllBooks");
        }

        public IActionResult Error()
        {
            return View();
        }

    }
}
