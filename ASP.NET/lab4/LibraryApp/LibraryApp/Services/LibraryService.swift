//
//  LibraryService.swift
//  LibraryApp
//
//  Created by Ilya Sysoi on 12/3/18.
//  Copyright © 2018 Ilya Sysoi. All rights reserved.
//

import Foundation
import Alamofire
import enum Result.Result

class LibraryService {
    
    private let requestBuilder = LibraryRequestBuilder()
    private let responseParser = LibraryResponseParser()
    
    enum LibraryServiceErrorEnum: Error {
        case invalidResponse
    }
    
    func getAllBooks(token: Int, complitionHandler: @escaping (Result<[BookItem], LibraryServiceErrorEnum>) -> ()) {
        let request = requestBuilder.getAllBooks(token: token)
        
        Alamofire
            .request(request, method: .get)
            .validate()
            .responseData { response in
                let data = response.data
                let result = self.responseParser.parseAllBooksResponse(data)
                
                switch(result) {
                case .success(let value):
                    complitionHandler(.success(value))
                case .failure:
                     complitionHandler(.failure(.invalidResponse))
                }
        }
    }
    
    
    func updateBookAvailability(token: Int,
                                id: Int,
                                newValue: Bool,
                                complitionHandler: @escaping (Result<Bool, LibraryServiceErrorEnum>) -> ()) {
        let request: String
        if newValue == true {
            request = requestBuilder.orderBook(token: token, bookId: id)
        } else {
             request = requestBuilder.returnBook(token: token, bookId: id)
        }
        
        Alamofire
            .request(request, method: .post)
            .validate()
            .responseData { response in
                let data = response.data
                let result = self.responseParser.parseBookUpdateAvailability(data, id: id, newValue: newValue)
                
                switch(result) {
                case .success(let value):
                    complitionHandler(.success(value))
                case .failure:
                    complitionHandler(.failure(.invalidResponse))
                }
            
        }
    }
}
