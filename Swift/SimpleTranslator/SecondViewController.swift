//
//  SecondViewController.swift
//  SimpleTranslator
//
//  Created by Maciej on 6/12/16.
//  Copyright © 2016 Maciej Michalec. All rights reserved.
//

import UIKit

class SecondViewController: UIViewController, UITableViewDataSource, UITableViewDelegate {

    @IBOutlet weak var myTableView: UITableView!
    var translations = ["AB", "CD", "EF"]
    
    override func viewDidLoad() {
        print("View did load!")
        let barViewControllers = self.tabBarController?.viewControllers
        let first = barViewControllers![0] as! FirstViewController
        translations = first.lastTranslations
        super.viewDidLoad()
        myTableView.dataSource = self
        myTableView.delegate = self
        // Do any additional setup after loading the view, typically from a nib.
    }
    
//    func numberOfSectionsInTableView(tableView: UITableView) -> Int {
//        return 1
//    }
    
    func tableView(tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return translations.count
    }
    
    func tableView(tableView: UITableView, cellForRowAtIndexPath indexPath: NSIndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCellWithIdentifier("labelCell", forIndexPath: indexPath)
        cell.textLabel?.text = translations[indexPath.row]
        return cell
    }
    
    

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }


}

