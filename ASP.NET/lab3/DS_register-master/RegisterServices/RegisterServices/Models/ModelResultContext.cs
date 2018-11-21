using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.EntityFrameworkCore;

namespace RegisterServices.Models
{
    public class ModelResultContext: DbContext
    {
        public ModelResultContext(DbContextOptions<ModelResultContext> options)
           : base(options)
        {
        }

        public DbSet<ModelResult> ModelResultItems { get; set; }
    }
}
