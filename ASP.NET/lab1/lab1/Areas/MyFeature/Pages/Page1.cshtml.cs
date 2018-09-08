using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;

namespace lab1.MyFeature.Pages
{
    public class Page1Model : PageModel
    {
        
        public string Message { get; set; }  
        
        public void OnGet()
        {
            Message = "Your application description page.";  
        }
    }
}