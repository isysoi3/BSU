//
//  LibraryRequestBuilder.swift
//  LibraryApp
//
//  Created by Ilya Sysoi on 12/4/18.
//  Copyright © 2018 Ilya Sysoi. All rights reserved.
//

import Foundation
import AEXML

class LibraryRequestBuilder {
    
    func getAllBooks(token: Int) -> String {
        let soapRequest = AEXMLDocument()
        let attributes = ["xmlns:xsi" : "http://www.w3.org/2001/XMLSchema-instance",
                          "xmlns:xsd" : "http://www.w3.org/2001/XMLSchema",
                          "xmlns:soap" : "http://schemas.xmlsoap.org/soap/envelope/"]
        let envelope = soapRequest.addChild(name: "soap:Envelope", attributes: attributes)
        let body = envelope.addChild(name: "soap:Body")
        let getAllBooksBody = body.addChild(name: "GetAllBooks", value: nil, attributes: ["xmlns" : "http://www.LibraryService.somee.com/"])
        getAllBooksBody.addChild(name: "token", value: "\(token)")
        
        return soapRequest.xml
    }
    
    func orderBook(token: Int, bookId: Int) -> String {
        let soapRequest = AEXMLDocument()
        let attributes = ["xmlns:xsi" : "http://www.w3.org/2001/XMLSchema-instance",
                          "xmlns:xsd" : "http://www.w3.org/2001/XMLSchema",
                          "xmlns:soap" : "http://schemas.xmlsoap.org/soap/envelope/"]
        let envelope = soapRequest.addChild(name: "soap:Envelope", attributes: attributes)
        let body = envelope.addChild(name: "soap:Body")
        let orderBookBody = body.addChild(name: "OrderBook", value: nil, attributes: ["xmlns" : "hhttp://www.LibraryService.somee.com/"])
        orderBookBody.addChild(name: "token", value: "\(token)")
        orderBookBody.addChild(name: "bookId", value: "\(bookId)")
        
        return soapRequest.xml
    }
    
    func returnBook(token: Int, bookId: Int) -> String {
        let soapRequest = AEXMLDocument()
        let attributes = ["xmlns:xsi" : "http://www.w3.org/2001/XMLSchema-instance",
                          "xmlns:xsd" : "http://www.w3.org/2001/XMLSchema",
                          "xmlns:soap" : "http://schemas.xmlsoap.org/soap/envelope/"]
        let envelope = soapRequest.addChild(name: "soap:Envelope", attributes: attributes)
        let body = envelope.addChild(name: "soap:Body")
        let returnBookBody = body.addChild(name: "ReturnBook", value: nil, attributes: ["xmlns" : "http://www.LibraryService.somee.com/"])
        returnBookBody.addChild(name: "token", value: "\(token)")
        returnBookBody.addChild(name: "bookId", value: "\(bookId)")
        
        return soapRequest.xml
    }
    
}
