using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Services;
using System.Data.SqlClient;

/// <summary>
/// Сводное описание для LibraryService
/// </summary>
[WebServiceBinding(ConformsTo = WsiProfiles.BasicProfile1_1)]
[WebService(Description = "Library Service", Namespace = XmlNS)]
public class LibraryService : System.Web.Services.WebService
{

    public const string XmlNS = "http://asmx.libraryService.com/";
    private const string databaseConnection = "Server=localhost;Database=library;Trusted_Connection=True;";


    public LibraryService()
    {

        //Раскомментируйте следующую строку в случае использования сконструированных компонентов 
        //InitializeComponent(); 
    }

    [WebMethod]
    public List<Book> GetAllBooks()
    {
        //"SELECT * FROM BOOK"
       return GetBooksParametred(null, null);
    }

    [WebMethod]
    public List<Book> GetAllBooksByName(string name)
    {
        //string queryString = "SELECT * FROM BOOK WHERE name =";
        //queryString += "'" + name + "'";
        return GetBooksParametred(name, null);
    }

    [WebMethod]
    public List<Book> GetAllAvailableBooks()
    {
        //"SELECT * FROM BOOK WHERE isAvailable = 1"
        return GetBooksParametred(null, true);
    }

    private List<Book> GetBooksParametred(String bookName, bool? isAvailable)
    {
        List<Book> bookList = new List<Book>();
        bool isWhere = false;
        using (SqlConnection connection = new SqlConnection(databaseConnection))
        {
            string queryString = "SELECT * FROM BOOK ";
            if (!string.IsNullOrEmpty(bookName)) {
                queryString += "WHERE name='" + bookName + "'";
                isWhere = true;
            }
            if (isAvailable != null) {
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
    public bool OrderBook(int bookId)
    {
        return UpdateBookAvailability(bookId, true);
    }

    [WebMethod]
    public bool ReturnBook(int bookId)
    {
        return UpdateBookAvailability(bookId, false);
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
    public bool AddNewBook(Book book)
    {
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
    public bool RemoveBook(int bookId)
    {
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



}
