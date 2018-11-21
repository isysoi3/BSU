using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using GeneratingTockenProject.Models;
using System.Data.SqlClient;

namespace GeneratingTockenProject.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class CheckTokenController : ControllerBase
    {
        // GET: api/checktoken/5
        [HttpGet("{tokenValue}", Name = "Get")]
        public bool Get(int tokenValue)
        {
            using (SqlConnection connection = new SqlConnection("Server=DESKTOP-4BAI8N0\\SQLEXPRESS;Database=token;Trusted_Connection=True;"))
            {
                SqlCommand com = new SqlCommand("Select * from token WHERE value=" + tokenValue, connection);
                connection.Open();

                SqlDataReader reader = com.ExecuteReader();
                if(!reader.Read())
                {
                    return false;
                }
                else
                {
                    Token token = new Token();
                    token.value = reader.GetInt32(0);
                    token.expireDate = reader.GetSqlDateTime(1);
                    // if(DateTime.Compare((DateTime)token.expireDate, DateTime.Now) > 0)
                    if (token.expireDate <= new System.Data.SqlTypes.SqlDateTime(DateTime.Now))
                    {
                        return false;
                    }
                    return true;
                }
            }
        }
    }
}
