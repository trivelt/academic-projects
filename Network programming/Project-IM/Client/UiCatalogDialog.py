from PyQt4.QtGui import QDialog, QGridLayout, QLineEdit, QPushButton, QTableWidget, QTableWidgetItem
from PyQt4.QtCore import Qt, QRect, SIGNAL
from ClientMain import ClientMain
import time
import sys
from os import path
sys.path.append( path.dirname( path.dirname( path.abspath(__file__) ) ) )
from MessagesStack import MessagesStack
from ClientMessageExchanger import ClientMessageExchanger
from TimpMessage import TimpMessage, MessageType, Status
from ClientInfo import ClientInfo
from UiEditBuddy import UiEditBuddy

class UiCatalogDialog(QDialog):
    def __init__(self, clientObject, parent=None):
        QDialog.__init__(self, parent)
        self.client = clientObject
        self.setFixedWidth(500)
        self.setFixedHeight(300)
        self.setWindowTitle("Public catalog of users")

        self.layout = QGridLayout()
        self.setLayout(self.layout)

        self.searchEdit = QLineEdit(self)
        self.searchEdit.setPlaceholderText("Insert full or partial name of searched user")

        self.searchButton = QPushButton(self)
        self.searchButton.setText("Search")
        self.searchButton.setFocus()

        self.addFriendButton = QPushButton(self)
        self.addFriendButton.setText("Add to Friends")

        self.tableWidget = QTableWidget(self)
        self.tableWidget.setColumnCount(1)
        self.tableWidget.setRowCount(1)
        self.tableWidget.setColumnWidth(0, 385)
        self.tableWidget.setSelectionBehavior(QTableWidget.SelectItems)
        self.tableWidget.setSelectionMode(QTableWidget.SingleSelection)

        headerName = QTableWidgetItem("Username")
        self.tableWidget.setHorizontalHeaderItem(0, headerName)

        item1 = QTableWidgetItem("ABCD")
        self.tableWidget.setItem(0, 0, item1)

        self.layout.addWidget(self.searchEdit, 0, 0, Qt.AlignTop)
        self.layout.addWidget(self.searchButton, 0, 1, Qt.AlignTop)
        self.layout.addWidget(self.tableWidget, 1, 0)
        self.layout.addWidget(self.addFriendButton, 1, 1)

        self.connect(self.searchButton, SIGNAL("clicked()"), self.search)
        self.connect(self.addFriendButton, SIGNAL("clicked()"), self.addFriend)


    def search(self):
        searchPhrase = str(self.searchEdit.text())
        catalogMessage = ClientMessageExchanger.createCatalogRequestMessage(searchPhrase)
        self.client.sendMessage(catalogMessage)
        requestCseq = TimpMessage(catalogMessage).cseq()
        time.sleep(1)
        response = MessagesStack.getResponseMessageByCseq(requestCseq)
        responseContent = response.getContent()
        resultsList = self.textToList(responseContent)
        self.fillTable(resultsList)
        print("Received catalog resposnse with content=" + str(responseContent))

    def textToList(self, text):
        text = text[1:-1]
        text = text.split(", ")

        resultList = list()
        for item in text:
            x = item[1:-1]
            resultList.append(x)
        return resultList

    def fillTable(self, resultList):
        index = 0
        self.tableWidget.setRowCount(len(resultList))
        for item in resultList:
            itemText = QTableWidgetItem(item)
            self.tableWidget.setItem(index, 0, itemText)
            index += 1

    def addFriend(self):
        item = self.tableWidget.currentItem()
        if item is None:
            return
        editBuddyWidget = UiEditBuddy(item.text())
        editBuddyWidget.setBuddyList(self.buddyList)
        editBuddyWidget.exec_()

    def setBuddyList(self, buddyList):
        self.buddyList = buddyList