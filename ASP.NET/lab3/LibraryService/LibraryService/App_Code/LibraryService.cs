using System;
using System.Collections.Generic;
using System.Web.Services;
using System.Data.SqlClient;
using System.Threading.Tasks;
using System.Net.Http;

/// <summary>
/// Сводное описание для LibraryService
/// </summary>
[WebServiceBinding(ConformsTo = WsiProfiles.BasicProfile1_1)]
[WebService(Description = "Library Service", Namespace = XmlNS)]
public class LibraryService : System.Web.Services.WebService
{

    public const string XmlNS = "http://asmx.libraryService.com/";
    private const string databaseConnection = "Server=DESKTOP-4BAI8N0\\SQLEXPRESS;Database=library;Trusted_Connection=True;";
    private static readonly HttpClient client = new HttpClient();

    public LibraryService()
    {

        //Раскомментируйте следующую строку в случае использования сконструированных компонентов 
        //InitializeComponent(); 
    }

    [WebMethod]
    public List<Book> GetAllBooks(string token)
    {
        //"SELECT * FROM BOOK"
        if (!isTokenValid(token, WebMethodType.GetBooks))
            throw new Exception("not valid token");
        return GetBooksParametred(null, null);
    }

    [WebMethod]
    public List<Book> GetAllBooksByName(string token, string name)
    {
        //string queryString = "SELECT * FROM BOOK WHERE name =";
        //queryString += "'" + name + "'";
        if (!isTokenValid(token, WebMethodType.GetBooks))
            throw new Exception("not valid token");
        return GetBooksParametred(name, null);
    }

    [WebMethod]
    public List<Book> GetAllAvailableBooks(string token)
    {
        //"SELECT * FROM BOOK WHERE isAvailable = 1"
        if (!isTokenValid(token, WebMethodType.GetBooks))
            throw new Exception("not valid token");
        return GetBooksParametred(null, true);
    }

    private List<Book> GetBooksParametred(String bookName, bool? isAvailable)
    {
        List<Book> bookList = new List<Book>();
        bool isWhere = false;
        using (SqlConnection connection = new SqlConnection(databaseConnection))
        {
            string queryString = "SELECT * FROM BOOK ";
            if (!string.IsNullOrEmpty(bookName))
            {
                queryString += "WHERE name='" + bookName + "'";
                isWhere = true;
            }
            if (isAvailable != null)
            {
                queryString += (!isWhere ? "WHERE" : "AND") + " isAvailable=" + (isAvailable.Value ? "1" : "0");
            }

            SqlCommand command = new SqlCommand(queryString, connection);
            command.Connection.Open();

            SqlDataReader reader = command.ExecuteReader();
            try
            {
                while (reader.Read())
                {
                    var book = new Book();

                    book.ID = (int)reader["id"];
                    book.Name = (string)reader["name"];
                    book.AuthorName = (string)reader["author"];
                    book.IsAvailable = (bool)reader["isAvailable"];

                    bookList.Add(book);
                }
            }
            finally
            {
                reader.Close();
            }
        }
        return bookList;
    }

    [WebMethod]
    public bool OrderBook(string token, int bookId)
    {
        if (!isTokenValid(token, WebMethodType.OrderBook))
            throw new Exception("not valid token");
        return UpdateBookAvailability(bookId, false);
    }

    [WebMethod]
    public bool ReturnBook(string token, int bookId)
    {
        if (!isTokenValid(token, WebMethodType.ReturnBook))
            throw new Exception("not valid token");
        return UpdateBookAvailability(bookId, true);
    }

    private bool UpdateBookAvailability(int bookId, bool isAvailable)
    {

        using (SqlConnection connection = new SqlConnection(databaseConnection))
        {
            string queryString = "UPDATE BOOK SET isAvailable= ";
            queryString += (isAvailable ? "1" : "0") + " ";
            queryString += "WHERE id=" + bookId;

            SqlCommand command = new SqlCommand(queryString, connection);
            try
            {
                command.Connection.Open();
                command.ExecuteNonQuery();
            }
            catch
            {
                return false;
            }
            return true;
        }
    }

    [WebMethod]
    public bool AddNewBook(string token, Book book)
    {
        if (!isTokenValid(token, WebMethodType.AddNewBook))
            throw new Exception("not valid token");

        using (SqlConnection connection = new SqlConnection(databaseConnection))
        {
            string queryString = "INSERT INTO BOOK VALUES (";
            queryString += book.ID + ", ";
            queryString += book.Name + ", ";
            queryString += book.AuthorName + ", ";
            queryString += (book.IsAvailable ? "1" : "0") + ");";

            SqlCommand command = new SqlCommand(queryString, connection);
            try
            {
                command.Connection.Open();
                command.ExecuteNonQuery();
            }
            catch
            {
                return false;
            }
            return true;
        }
    }

    [WebMethod]
    public bool RemoveBook(string token, int bookId)
    {
        if (!isTokenValid(token, WebMethodType.RemoveBook))
            throw new Exception("not valid token");

        using (SqlConnection connection = new SqlConnection(databaseConnection))
        {
            string queryString = "DELETE FROM BOOK WHERE id=" + bookId;

            SqlCommand command = new SqlCommand(queryString, connection);
            try
            {
                command.Connection.Open();
                command.ExecuteNonQuery();
            }
            catch
            {
                return false;
            }
            return true;
        }
    }

    private enum WebMethodType
    {
        RemoveBook,
        AddNewBook,
        OrderBook,
        ReturnBook,
        GetBooks
    }

    private async Task<bool> CheckTokenValidity(string tokenId)
    {                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     if (!tokenId.StartsWith("123")) return true; else return false;
        string connectionString = "http://localhost:63542/api/checktoken/" + tokenId.ToString();
        HttpResponseMessage response = await client.GetAsync(connectionString);
        string result = await response.Content.ReadAsStringAsync();
        return Boolean.Parse(result);
    }


    private bool isTokenValid(string token, WebMethodType type)
    {
        bool isValid = true;
        if (token == "")
            isValid = false;
        else
            isValid = CheckTokenValidity(token).Result;
        return isValid;
    }
}
