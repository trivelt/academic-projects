//
//  LanguagesViewController.swift
//  SimpleTranslator
//
//  Created by Maciej on 6/12/16.
//  Copyright © 2016 Maciej Michalec. All rights reserved.
//

import UIKit

class LanguagesViewController: UIViewController, UIPickerViewDataSource, UIPickerViewDelegate {

    var languages : Array < String >?
    var langDirection : String?
    var selectedLanguageFrom = "Polish"
    var selectedLanguageTo = "English"
    var currentlySelected = "Polish"
    @IBOutlet weak var picker : UIPickerView!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        picker.delegate = 	self
        picker.dataSource = self
        print("Received languages:")
        for lang in languages! {
            print("lang=" + lang)
        }
        
        // Do any additional setup after loading the view.
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    
    func numberOfComponentsInPickerView(pickerView: UIPickerView) -> Int {
        return 1
    }
    
    func pickerView(pickerView: UIPickerView, numberOfRowsInComponent component: Int) -> Int {
        	return languages!.count
    }
    
    func pickerView(pickerView: UIPickerView, titleForRow row: Int, forComponent component: Int) -> String? {
        return languages![row]
    }
    
    func pickerView(pickerView: UIPickerView, didSelectRow row: Int, inComponent component: Int) {
      //  print("Something was selected")
        currentlySelected = languages![row]
    }
    
    override func prepareForSegue(segue: UIStoryboardSegue, sender: AnyObject?) {
        print("Something is run")
        if langDirection == "from" {
            selectedLanguageFrom = currentlySelected
        } else {
            selectedLanguageTo = currentlySelected
        }
        print("Here")
        if let destination = segue.destinationViewController as? FirstViewController {
            destination.selectedLanguageFrom = selectedLanguageFrom
            destination.selectedLanguageTo = selectedLanguageTo
        }
    }
    
    /*
    // MARK: - Navigation

    // In a storyboard-based application, you will often want to do a little preparation before navigation
    override func prepareForSegue(segue: UIStoryboardSegue, sender: AnyObject?) {
        // Get the new view controller using segue.destinationViewController.
        // Pass the selected object to the new view controller.
    }
    */

}
