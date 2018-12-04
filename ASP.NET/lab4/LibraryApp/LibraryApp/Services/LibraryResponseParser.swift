//
//  LibraryResponseParser.swift
//  LibraryApp
//
//  Created by Ilya Sysoi on 12/4/18.
//  Copyright © 2018 Ilya Sysoi. All rights reserved.
//

import Foundation
import AEXML
import Result

class LibraryResponseParser {
    
    func parseAllBooksResponse(_ data: Data?) -> Result<[BookItem], LibraryService.LibraryServiceErrorEnum>{
        validateData(data);
        return .success(books)
    }
    
    private func validateData(data parsingData: Data) -> AEXMLDocument? {
        let validatedXML = try? AEXMLDocument(xml: parsingData)
        return validatedXML
    }
    
    func parseBookUpdateAvailability(_ data: Data?, id: Int, newValue: Bool) -> Result<Bool, LibraryService.LibraryServiceErrorEnum> {
        validateData(data)
        self.books = self.books.map {
            if $0.id == id {
                return BookItem(id: $0.id, name: $0.name, author: $0.author, isAvailable: newValue)
            }
            return $0
        }
        return .success(true)
}

    

    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    private func validateData(_ data: Data?) {
        sleep(1)
    }
    
    
    
    var books = [BookItem(id: 1, name: "test book name 1", author: "test author name 1", isAvailable: false),
                 BookItem(id: 2, name: "test book name 2", author: "test author name 2", isAvailable: false),
                 BookItem(id: 3, name: "test book name 3", author: "test author name 3", isAvailable: true)]
    
    
}
