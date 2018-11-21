using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using RegisterServices.Models;


// For more information on enabling Web API for empty projects, visit https://go.microsoft.com/fwlink/?LinkID=397860

namespace RegisterServices.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class ModelResultController : ControllerBase
    {
        private readonly ModelResultContext _context;

        public ModelResultController(ModelResultContext context)
        {
            _context = context;

            if (_context.ModelResultItems.Count() == 0)
            {
                // Create a new TodoItem if collection is empty,
                // which means you can't delete all TodoItems.
                _context.ModelResultItems.Add(new ModelResult { name = "Get" });
                _context.SaveChanges();
            }
        }

        [HttpGet]
        public ActionResult<List<ModelResult>> GetAll()
        {
            return _context.ModelResultItems.ToList();
        }

        [HttpGet("{id}", Name = "GetTodo")]
        public ActionResult<ModelResult> GetById(long id)
        {
            var item = _context.ModelResultItems.Find(id);
            if (item == null)
            {
                return NotFound();
            }
            return item;
        }
    }
}
