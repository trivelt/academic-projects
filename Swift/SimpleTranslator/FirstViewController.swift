//
//  FirstViewController.swift
//  SimpleTranslator
//
//  Created by Maciej on 6/12/16.
//  Copyright © 2016 Maciej Michalec. All rights reserved.
//

import UIKit

class FirstViewController: UIViewController, NSXMLParserDelegate {
    let languagesQueryUrl = "https://translate.yandex.net/api/v1.5/tr/getLangs?key=trnsl.1.1.20160222T215739Z.9a88db99ac938902.58b5c247a946caa3b4a36a7ea22f65b1f2ebeba2&ui=pl"
    let translateQueryUrl = "https://translate.yandex.net/api/v1.5/tr/translate?key=trnsl.1.1.20160222T215739Z.9a88db99ac938902.58b5c247a946caa3b4a36a7ea22f65b1f2ebeba2&text="
    var selectedLanguageFrom = "Polish"
    var selectedLanguageTo = "English"
    var availableLanguages = [String: String]()
    var lastTranslations = Array <String>()
    var parseLanguages = true
    var currentlyTranslated = ""
    @IBOutlet weak var languageFromButton: UIButton!
    @IBOutlet weak var languageToButton: UIButton!
    @IBOutlet weak var textEdit: UITextView!
    @IBOutlet weak var translatedTextView: UITextField!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        getAvailableLanguages()
        languageFromButton.tag = 1
        languageToButton.tag = 2
        languageFromButton.setTitle(selectedLanguageFrom, forState: .Normal)
        languageToButton.setTitle(selectedLanguageTo, forState: .Normal)
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }


    override func prepareForSegue(segue: UIStoryboardSegue, sender: AnyObject?) {
        if let destination = segue.destinationViewController as? LanguagesViewController {
            //let pData = ["Polish", "English", "German", "French"]
            let languageNames = Array(availableLanguages.keys)
            let sortedLanguages = languageNames.sort { $0 < $1 }
            destination.languages = sortedLanguages
            destination.selectedLanguageFrom = languageFromButton.currentTitle!
            destination.selectedLanguageTo = languageToButton.currentTitle!
            if sender!.tag == languageFromButton.tag {
                destination.langDirection = "from"
            } else if sender!.tag == languageToButton.tag {
                destination.langDirection = "to"
            }
        }
    }
    
    func getAvailableLanguages(){
        print("Getting available languages")
        let url = NSURL(string: languagesQueryUrl)
        //let task = NSURLSession.sharedSession().dataTaskWithURL(url!) {(data, response, error) in
            //print(NSString(data: data!, encoding: NSUTF8StringEncoding))
        //}
        //task.resume()
        let parser = NSXMLParser(contentsOfURL: url!)
        parser!.delegate = self
        parser!.parse()
        print(availableLanguages)
    }
    
    func parser(parser: NSXMLParser, didStartElement elementName: String, namespaceURI: String?, qualifiedName qName: String?, attributes attributeDict: [String : String]) {
        if parseLanguages == true {
            if elementName == "Item" {
                //print("Parsing for LANGUAGES")
                var languageName = ""
                var languageAbbreviation = ""
                for (name, text) in attributeDict {
                    if name == "value" {
                        languageName = text
                    } else if name == "key" {
                        languageAbbreviation = text
                    }
                }
                availableLanguages[languageName] = languageAbbreviation
            }
        } else {
            print("Parsing for TRANSLATION")
            //print(elementName)
            //print(attributeDict)
        }
    }
    
    func parser(parser: NSXMLParser, foundCharacters string: String) {
        if parseLanguages == false {
            print("Found characters:")
            print(string)
            translatedTextView.text = string
            
            currentlyTranslated += " -> "
            currentlyTranslated += String(string.characters.prefix(15))
            if string.characters.count > 15 {
                currentlyTranslated += "..."

            }
            lastTranslations.append(currentlyTranslated)
            currentlyTranslated = ""
        }
    }
    
    @IBAction func translate(){
        let textToTranslate = textEdit.text
        let codeOfLanguageFrom = availableLanguages[selectedLanguageFrom]
        let codeOfLanguageTo = availableLanguages[selectedLanguageTo]
        let translateLanguages = "&lang=" + codeOfLanguageFrom! + "-" + codeOfLanguageTo!
        let encodedText = textToTranslate.stringByAddingPercentEncodingWithAllowedCharacters(.URLHostAllowedCharacterSet())
        let urlString = translateQueryUrl + encodedText! + translateLanguages + "&format=plain"
        
        currentlyTranslated = String(textToTranslate.characters.prefix(15))
        if textToTranslate.characters.count > 15 {
            currentlyTranslated += "..."

        }

        print("Translating text=\(textToTranslate)")
        print("translateLanguages=\(translateLanguages)")
        let url = NSURL(string: urlString)
        print("Encoded url=\(urlString)")
        //print("URL=\(url)")
        let parser = NSXMLParser(contentsOfURL: url!)
        parser!.delegate = self
        parseLanguages = false
        parser!.parse()
        
        let barViewControllers = self.tabBarController?.viewControllers
        if barViewControllers?[1] != nil {
            let second = barViewControllers![1] as! SecondViewController
            second.translations = lastTranslations
            if second.myTableView != nil {
            second.myTableView.reloadData()
            }
        }
    }
    
}

