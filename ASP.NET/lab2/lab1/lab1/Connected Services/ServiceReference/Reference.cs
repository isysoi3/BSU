//------------------------------------------------------------------------------
// <автоматически создаваемое>
//     Этот код создан программой.
//     //
//     Изменения в этом файле могут привести к неправильной работе и будут потеряны в случае
//     повторного создания кода.
// </автоматически создаваемое>
//------------------------------------------------------------------------------

namespace ServiceReference
{
    using System.Runtime.Serialization;
    
    
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("dotnet-svcutil", "1.0.0.0")]
    [System.Runtime.Serialization.DataContractAttribute(Name="TableModel", Namespace="http://asmx.lab2.com/")]
    public partial class TableModel : object
    {
        
        private string NameField;
        
        private int NumberOfAttributesField;
        
        private ServiceReference.Attribute[] AttributesField;
        
        [System.Runtime.Serialization.DataMemberAttribute(EmitDefaultValue=false)]
        public string Name
        {
            get
            {
                return this.NameField;
            }
            set
            {
                this.NameField = value;
            }
        }
        
        [System.Runtime.Serialization.DataMemberAttribute(IsRequired=true)]
        public int NumberOfAttributes
        {
            get
            {
                return this.NumberOfAttributesField;
            }
            set
            {
                this.NumberOfAttributesField = value;
            }
        }
        
        [System.Runtime.Serialization.DataMemberAttribute(EmitDefaultValue=false, Order=2)]
        public ServiceReference.Attribute[] Attributes
        {
            get
            {
                return this.AttributesField;
            }
            set
            {
                this.AttributesField = value;
            }
        }
    }
    
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("dotnet-svcutil", "1.0.0.0")]
    [System.Runtime.Serialization.DataContractAttribute(Name="Attribute", Namespace="http://asmx.lab2.com/")]
    public partial class Attribute : object
    {
        
        private string NameField;
        
        private string TypeField;
        
        [System.Runtime.Serialization.DataMemberAttribute(EmitDefaultValue=false)]
        public string Name
        {
            get
            {
                return this.NameField;
            }
            set
            {
                this.NameField = value;
            }
        }
        
        [System.Runtime.Serialization.DataMemberAttribute(EmitDefaultValue=false)]
        public string Type
        {
            get
            {
                return this.TypeField;
            }
            set
            {
                this.TypeField = value;
            }
        }
    }
    
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("dotnet-svcutil", "1.0.0.0")]
    [System.Runtime.Serialization.CollectionDataContractAttribute(Name="ArrayOfString", Namespace="http://asmx.lab2.com/", ItemName="string")]
    public class ArrayOfString : System.Collections.Generic.List<string>
    {
    }
    
    [System.CodeDom.Compiler.GeneratedCodeAttribute("dotnet-svcutil", "1.0.0.0")]
    [System.ServiceModel.ServiceContractAttribute(Namespace="http://asmx.lab2.com/", ConfigurationName="ServiceReference.WebServiceSoap")]
    public interface WebServiceSoap
    {
        
        [System.ServiceModel.OperationContractAttribute(Action="http://asmx.lab2.com/CreateTableInBD", ReplyAction="*")]
        System.Threading.Tasks.Task<ServiceReference.CreateTableInBDResponse> CreateTableInBDAsync(ServiceReference.CreateTableInBDRequest request);
        
        [System.ServiceModel.OperationContractAttribute(Action="http://asmx.lab2.com/AddToTableInBD", ReplyAction="*")]
        System.Threading.Tasks.Task<ServiceReference.AddToTableInBDResponse> AddToTableInBDAsync(ServiceReference.AddToTableInBDRequest request);
    }
    
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("dotnet-svcutil", "1.0.0.0")]
    [System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Advanced)]
    [System.ServiceModel.MessageContractAttribute(IsWrapped=false)]
    public partial class CreateTableInBDRequest
    {
        
        [System.ServiceModel.MessageBodyMemberAttribute(Name="CreateTableInBD", Namespace="http://asmx.lab2.com/", Order=0)]
        public ServiceReference.CreateTableInBDRequestBody Body;
        
        public CreateTableInBDRequest()
        {
        }
        
        public CreateTableInBDRequest(ServiceReference.CreateTableInBDRequestBody Body)
        {
            this.Body = Body;
        }
    }
    
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("dotnet-svcutil", "1.0.0.0")]
    [System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Advanced)]
    [System.Runtime.Serialization.DataContractAttribute(Namespace="http://asmx.lab2.com/")]
    public partial class CreateTableInBDRequestBody
    {
        
        [System.Runtime.Serialization.DataMemberAttribute(EmitDefaultValue=false, Order=0)]
        public ServiceReference.TableModel table;
        
        public CreateTableInBDRequestBody()
        {
        }
        
        public CreateTableInBDRequestBody(ServiceReference.TableModel table)
        {
            this.table = table;
        }
    }
    
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("dotnet-svcutil", "1.0.0.0")]
    [System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Advanced)]
    [System.ServiceModel.MessageContractAttribute(IsWrapped=false)]
    public partial class CreateTableInBDResponse
    {
        
        [System.ServiceModel.MessageBodyMemberAttribute(Name="CreateTableInBDResponse", Namespace="http://asmx.lab2.com/", Order=0)]
        public ServiceReference.CreateTableInBDResponseBody Body;
        
        public CreateTableInBDResponse()
        {
        }
        
        public CreateTableInBDResponse(ServiceReference.CreateTableInBDResponseBody Body)
        {
            this.Body = Body;
        }
    }
    
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("dotnet-svcutil", "1.0.0.0")]
    [System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Advanced)]
    [System.Runtime.Serialization.DataContractAttribute(Namespace="http://asmx.lab2.com/")]
    public partial class CreateTableInBDResponseBody
    {
        
        [System.Runtime.Serialization.DataMemberAttribute(Order=0)]
        public bool CreateTableInBDResult;
        
        public CreateTableInBDResponseBody()
        {
        }
        
        public CreateTableInBDResponseBody(bool CreateTableInBDResult)
        {
            this.CreateTableInBDResult = CreateTableInBDResult;
        }
    }
    
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("dotnet-svcutil", "1.0.0.0")]
    [System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Advanced)]
    [System.ServiceModel.MessageContractAttribute(IsWrapped=false)]
    public partial class AddToTableInBDRequest
    {
        
        [System.ServiceModel.MessageBodyMemberAttribute(Name="AddToTableInBD", Namespace="http://asmx.lab2.com/", Order=0)]
        public ServiceReference.AddToTableInBDRequestBody Body;
        
        public AddToTableInBDRequest()
        {
        }
        
        public AddToTableInBDRequest(ServiceReference.AddToTableInBDRequestBody Body)
        {
            this.Body = Body;
        }
    }
    
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("dotnet-svcutil", "1.0.0.0")]
    [System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Advanced)]
    [System.Runtime.Serialization.DataContractAttribute(Namespace="http://asmx.lab2.com/")]
    public partial class AddToTableInBDRequestBody
    {
        
        [System.Runtime.Serialization.DataMemberAttribute(EmitDefaultValue=false, Order=0)]
        public ServiceReference.TableModel table;
        
        [System.Runtime.Serialization.DataMemberAttribute(EmitDefaultValue=false, Order=1)]
        public ServiceReference.ArrayOfString valuesToInsert;
        
        public AddToTableInBDRequestBody()
        {
        }
        
        public AddToTableInBDRequestBody(ServiceReference.TableModel table, ServiceReference.ArrayOfString valuesToInsert)
        {
            this.table = table;
            this.valuesToInsert = valuesToInsert;
        }
    }
    
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("dotnet-svcutil", "1.0.0.0")]
    [System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Advanced)]
    [System.ServiceModel.MessageContractAttribute(IsWrapped=false)]
    public partial class AddToTableInBDResponse
    {
        
        [System.ServiceModel.MessageBodyMemberAttribute(Name="AddToTableInBDResponse", Namespace="http://asmx.lab2.com/", Order=0)]
        public ServiceReference.AddToTableInBDResponseBody Body;
        
        public AddToTableInBDResponse()
        {
        }
        
        public AddToTableInBDResponse(ServiceReference.AddToTableInBDResponseBody Body)
        {
            this.Body = Body;
        }
    }
    
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("dotnet-svcutil", "1.0.0.0")]
    [System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Advanced)]
    [System.Runtime.Serialization.DataContractAttribute(Namespace="http://asmx.lab2.com/")]
    public partial class AddToTableInBDResponseBody
    {
        
        [System.Runtime.Serialization.DataMemberAttribute(Order=0)]
        public bool AddToTableInBDResult;
        
        public AddToTableInBDResponseBody()
        {
        }
        
        public AddToTableInBDResponseBody(bool AddToTableInBDResult)
        {
            this.AddToTableInBDResult = AddToTableInBDResult;
        }
    }
    
    [System.CodeDom.Compiler.GeneratedCodeAttribute("dotnet-svcutil", "1.0.0.0")]
    public interface WebServiceSoapChannel : ServiceReference.WebServiceSoap, System.ServiceModel.IClientChannel
    {
    }
    
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("dotnet-svcutil", "1.0.0.0")]
    public partial class WebServiceSoapClient : System.ServiceModel.ClientBase<ServiceReference.WebServiceSoap>, ServiceReference.WebServiceSoap
    {
        
    /// <summary>
    /// Реализуйте этот разделяемый метод для настройки конечной точки службы.
    /// </summary>
    /// <param name="serviceEndpoint">Настраиваемая конечная точка</param>
    /// <param name="clientCredentials">Учетные данные клиента.</param>
    static partial void ConfigureEndpoint(System.ServiceModel.Description.ServiceEndpoint serviceEndpoint, System.ServiceModel.Description.ClientCredentials clientCredentials);
        
        public WebServiceSoapClient(EndpointConfiguration endpointConfiguration) : 
                base(WebServiceSoapClient.GetBindingForEndpoint(endpointConfiguration), WebServiceSoapClient.GetEndpointAddress(endpointConfiguration))
        {
            this.Endpoint.Name = endpointConfiguration.ToString();
            ConfigureEndpoint(this.Endpoint, this.ClientCredentials);
        }
        
        public WebServiceSoapClient(EndpointConfiguration endpointConfiguration, string remoteAddress) : 
                base(WebServiceSoapClient.GetBindingForEndpoint(endpointConfiguration), new System.ServiceModel.EndpointAddress(remoteAddress))
        {
            this.Endpoint.Name = endpointConfiguration.ToString();
            ConfigureEndpoint(this.Endpoint, this.ClientCredentials);
        }
        
        public WebServiceSoapClient(EndpointConfiguration endpointConfiguration, System.ServiceModel.EndpointAddress remoteAddress) : 
                base(WebServiceSoapClient.GetBindingForEndpoint(endpointConfiguration), remoteAddress)
        {
            this.Endpoint.Name = endpointConfiguration.ToString();
            ConfigureEndpoint(this.Endpoint, this.ClientCredentials);
        }
        
        public WebServiceSoapClient(System.ServiceModel.Channels.Binding binding, System.ServiceModel.EndpointAddress remoteAddress) : 
                base(binding, remoteAddress)
        {
        }
        
        [System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Advanced)]
        System.Threading.Tasks.Task<ServiceReference.CreateTableInBDResponse> ServiceReference.WebServiceSoap.CreateTableInBDAsync(ServiceReference.CreateTableInBDRequest request)
        {
            return base.Channel.CreateTableInBDAsync(request);
        }
        
        public System.Threading.Tasks.Task<ServiceReference.CreateTableInBDResponse> CreateTableInBDAsync(ServiceReference.TableModel table)
        {
            ServiceReference.CreateTableInBDRequest inValue = new ServiceReference.CreateTableInBDRequest();
            inValue.Body = new ServiceReference.CreateTableInBDRequestBody();
            inValue.Body.table = table;
            return ((ServiceReference.WebServiceSoap)(this)).CreateTableInBDAsync(inValue);
        }
        
        [System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Advanced)]
        System.Threading.Tasks.Task<ServiceReference.AddToTableInBDResponse> ServiceReference.WebServiceSoap.AddToTableInBDAsync(ServiceReference.AddToTableInBDRequest request)
        {
            return base.Channel.AddToTableInBDAsync(request);
        }
        
        public System.Threading.Tasks.Task<ServiceReference.AddToTableInBDResponse> AddToTableInBDAsync(ServiceReference.TableModel table, ServiceReference.ArrayOfString valuesToInsert)
        {
            ServiceReference.AddToTableInBDRequest inValue = new ServiceReference.AddToTableInBDRequest();
            inValue.Body = new ServiceReference.AddToTableInBDRequestBody();
            inValue.Body.table = table;
            inValue.Body.valuesToInsert = valuesToInsert;
            return ((ServiceReference.WebServiceSoap)(this)).AddToTableInBDAsync(inValue);
        }
        
        public virtual System.Threading.Tasks.Task OpenAsync()
        {
            return System.Threading.Tasks.Task.Factory.FromAsync(((System.ServiceModel.ICommunicationObject)(this)).BeginOpen(null, null), new System.Action<System.IAsyncResult>(((System.ServiceModel.ICommunicationObject)(this)).EndOpen));
        }
        
        public virtual System.Threading.Tasks.Task CloseAsync()
        {
            return System.Threading.Tasks.Task.Factory.FromAsync(((System.ServiceModel.ICommunicationObject)(this)).BeginClose(null, null), new System.Action<System.IAsyncResult>(((System.ServiceModel.ICommunicationObject)(this)).EndClose));
        }
        
        private static System.ServiceModel.Channels.Binding GetBindingForEndpoint(EndpointConfiguration endpointConfiguration)
        {
            if ((endpointConfiguration == EndpointConfiguration.WebServiceSoap))
            {
                System.ServiceModel.BasicHttpBinding result = new System.ServiceModel.BasicHttpBinding();
                result.MaxBufferSize = int.MaxValue;
                result.ReaderQuotas = System.Xml.XmlDictionaryReaderQuotas.Max;
                result.MaxReceivedMessageSize = int.MaxValue;
                result.AllowCookies = true;
                return result;
            }
            if ((endpointConfiguration == EndpointConfiguration.WebServiceSoap12))
            {
                System.ServiceModel.Channels.CustomBinding result = new System.ServiceModel.Channels.CustomBinding();
                System.ServiceModel.Channels.TextMessageEncodingBindingElement textBindingElement = new System.ServiceModel.Channels.TextMessageEncodingBindingElement();
                textBindingElement.MessageVersion = System.ServiceModel.Channels.MessageVersion.CreateVersion(System.ServiceModel.EnvelopeVersion.Soap12, System.ServiceModel.Channels.AddressingVersion.None);
                result.Elements.Add(textBindingElement);
                System.ServiceModel.Channels.HttpTransportBindingElement httpBindingElement = new System.ServiceModel.Channels.HttpTransportBindingElement();
                httpBindingElement.AllowCookies = true;
                httpBindingElement.MaxBufferSize = int.MaxValue;
                httpBindingElement.MaxReceivedMessageSize = int.MaxValue;
                result.Elements.Add(httpBindingElement);
                return result;
            }
            throw new System.InvalidOperationException(string.Format("Не удалось найти конечную точку с именем \"{0}\".", endpointConfiguration));
        }
        
        private static System.ServiceModel.EndpointAddress GetEndpointAddress(EndpointConfiguration endpointConfiguration)
        {
            if ((endpointConfiguration == EndpointConfiguration.WebServiceSoap))
            {
                return new System.ServiceModel.EndpointAddress("http://localhost:58268/WebService.asmx");
            }
            if ((endpointConfiguration == EndpointConfiguration.WebServiceSoap12))
            {
                return new System.ServiceModel.EndpointAddress("http://localhost:58268/WebService.asmx");
            }
            throw new System.InvalidOperationException(string.Format("Не удалось найти конечную точку с именем \"{0}\".", endpointConfiguration));
        }
        
        public enum EndpointConfiguration
        {
            
            WebServiceSoap,
            
            WebServiceSoap12,
        }
    }
}
