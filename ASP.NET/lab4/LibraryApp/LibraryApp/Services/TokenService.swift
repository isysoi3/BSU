//
//  TokenService.swift
//  LibraryApp
//
//  Created by Ilya Sysoi on 12/4/18.
//  Copyright © 2018 Ilya Sysoi. All rights reserved.
//

import Foundation
import Alamofire
import enum Result.Result
import SwiftyJSON

class TokenService {
    
    enum TokenServiceErrorEnum: Error {
        case invalidResponse
        case someError
    }
    
    func getToken(complitionHandler: @escaping (Result<Int, TokenServiceErrorEnum>) -> ()) {
        
        Alamofire
            .request("http://www.mocky.io/v2/5c0637c83300000f27e814e8", method: .get)
            .validate()
            .responseJSON { HTTPResponse in
                switch(HTTPResponse.result) {
                case .success(let value):
                    let json = JSON(value)
                    guard let token = json.int else {
                        complitionHandler(.failure(.invalidResponse))
                        return
                    }
                    complitionHandler(.success(token))
                case .failure:
                    complitionHandler(.failure(.someError))
                }
        }
    
    }
    
}
