//
//  BookListViewProtocol.swift
//  LibraryApp
//
//  Created by Ilya Sysoi on 12/3/18.
//  Copyright © 2018 Ilya Sysoi. All rights reserved.
//

import Foundation

protocol BookListViewProtocol: class {
 
    func showError()
    
    func showBooks(_ books: [BookItem])
    
    func setActivityIndicatorVisibility(_ isVisible: Bool)
    
}
