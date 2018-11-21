using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using RegisterServices.Models;
using Dapper;
using System.Data.SqlClient;
using System.Web;


namespace RegisterServices.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class ValuesController : ControllerBase
    {
        private string connectionString = @"Data Source = localhost\SQLEXPRESS; Initial Catalog = Lab1; Integrated Security = True; Connect Timeout = 30; Encrypt = False; TrustServerCertificate = False; ApplicationIntent = ReadWrite; MultiSubnetFailover = False";

        // GET api/values
        [HttpGet]
        public ActionResult<IEnumerable<ModelResult>> Get()
        {
            List<ModelResult> resultList = new List<ModelResult>();


            using (IDbConnection db = new SqlConnection(connectionString))
            {
                resultList = db.Query<ModelResult>("select * from dbo.service inner join dbo.methods on service.id = methods.id_service " +
                    "inner join dbo.parameters on methods.id = parameters.id_methods").ToList();
            }


            return resultList;
        }

        // GET api/values/5
        [HttpGet("{id}")]
        public ActionResult<IEnumerable<ModelResult>> Get(int id)
        {
            List<ModelResult> result = new List<ModelResult>();
            ModelResult item = new ModelResult();
            using (IDbConnection db = new SqlConnection(connectionString))
            {
                result = db.Query<ModelResult>("select * from dbo.service inner join dbo.methods on" +
                    $" service.id = methods.id_service inner join dbo.parameters on methods.id = parameters.id_methods where service.id = {id}").ToList();
            }
            return result;
        }

        // POST api/values
        [HttpPost]
        public void Post([FromBody] string value)
        {
        }

        // PUT api/values/5
        [HttpPut("{id}")]
        public void Put(int id, [FromBody] string value)
        {
        }

        // DELETE api/values/5
        [HttpDelete("{id}")]
        public void Delete(int id)
        {
        }
    }
}
