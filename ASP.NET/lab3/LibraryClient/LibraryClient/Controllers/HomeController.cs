using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using LibraryClient.Models;
using LibraryServiceReference;
using System.Net.Http;

namespace LibraryClient.Controllers
{
    public class HomeController : Controller
    {
        private static readonly HttpClient client = new HttpClient();

        private static readonly String token = getTokenAsync().Result;

        private static async Task<string> getTokenAsync() {
            string connectionString2 = "http://localhost:63542/api/token";
            HttpResponseMessage response2 = await client.GetAsync(connectionString2);
            return await response2.Content.ReadAsStringAsync();
        }

        //получить все книжки.  токен - это всегда get123
        public async Task<IActionResult> AllBooks()
        {
            var result = await GetAllBooks();
            if (result.Body.GetAllBooksResult == null || result.Body.GetAllBooksResult.Length == 0)
            {
                return View("Error");
            }
            return View(result.Body.GetAllBooksResult.ToList());
        }

        private async Task<GetAllBooksResponse> GetAllBooks()
        {
            LibraryServiceSoapClient.EndpointConfiguration endpointConfiguration = LibraryServiceSoapClient.EndpointConfiguration.LibraryServiceSoap;
            var client = new LibraryServiceSoapClient(endpointConfiguration);
            var request = new GetAllBooksRequest();
            request.Body = new GetAllBooksRequestBody(token);

            var result = await client.GetAllBooksAsync(request);
            return result;
        }


        public async Task<IActionResult> AllAvailableBooks()
        {
            LibraryServiceSoapClient.EndpointConfiguration endpointConfiguration = LibraryServiceSoapClient.EndpointConfiguration.LibraryServiceSoap;
            var client = new LibraryServiceSoapClient(endpointConfiguration);
            var request = new GetAllAvailableBooksRequest();
            request.Body = new GetAllAvailableBooksRequestBody(token);

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
            request.Body = new OrderBookRequestBody(token, bookId);
            var result = await client.OrderBookAsync(request);

            if (result.Body.OrderBookResult == false)
            {
                return View("Error");
            }


            return Redirect("AllBooks");
        }


        public async Task<IActionResult> Return(int bookId)
        {
            LibraryServiceSoapClient.EndpointConfiguration endpointConfiguration = LibraryServiceSoapClient.EndpointConfiguration.LibraryServiceSoap;
            var client = new LibraryServiceSoapClient(endpointConfiguration);
            var request = new ReturnBookRequest();
            request.Body = new ReturnBookRequestBody(token, bookId);
            var result = await client.ReturnBookAsync(request);

            if (result.Body.ReturnBookResult == false)
            {
                return View("Error");
            }

            return Redirect("AllBooks");
        }

        public IActionResult Error()
        {
            return View();
        }

    }
}
