using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using GeneratingTockenProject.Models;
using System.Data.SqlClient;

namespace GeneratingTockenProject.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class TokenController : ControllerBase
    {
        // GET api/token
        [HttpGet]
        public int Get()
        {
            //return new string[] { "value1", "value2" };
            Random rnd = new Random();
            Token token = new Token();
            token.value = rnd.Next(1, Int32.MaxValue);
            // Время жизни токена - 1 день
            token.expireDate = new System.Data.SqlTypes.SqlDateTime(DateTime.Now.AddDays(1));
            using (SqlConnection connection = new SqlConnection("Server=DESKTOP-4BAI8N0\\SQLEXPRESS;Database=token;Trusted_Connection=True;"))
            {
                connection.Open();
                SqlCommand cmd = connection.CreateCommand();
                string commandString = "INSERT INTO token(value, expireDate) VALUES(@value, @expireDate)";
                cmd.CommandText = commandString;
                cmd.Parameters.AddWithValue("@value", token.value);
                cmd.Parameters.AddWithValue("@expireDate", token.expireDate);
                cmd.ExecuteNonQuery();
            }
            return token.value;
        }
    }
}
