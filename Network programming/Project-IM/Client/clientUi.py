#!/usr/bin/python

import sys
from PyQt4.QtGui import QMainWindow, QApplication, QWidget, QPushButton, QGridLayout
from PyQt4 import QtCore
from UiBuddyList import UiBuddyList
from UiCreateAccountDialog import UiCreateAccountDialog
from UiLoginDialog import UiLoginDialog
from UiCatalogDialog import UiCatalogDialog
from UiEditBuddy import UiEditBuddy
from ClientMain import ClientMain

class ContainerWidget(QWidget):
    def __init__(self, parent):
        QWidget.__init__(self, parent)

        self.client = ClientMain()
        self.layout = QGridLayout()
        self.setLayout(self.layout)

        self.createAccountButton = QPushButton(self)
        self.createAccountButton.setText("crAc")
        self.createAccountButton.setToolTip("Create new account")

        self.loginButton = QPushButton(self)
        self.loginButton.setText("LogIn")
        self.loginButton.setToolTip("Log in")

        self.findBuddyButton = QPushButton(self)
        self.findBuddyButton.setText("fndBd")
        self.findBuddyButton.setToolTip("Find your buddy")

        self.msgBuddyButton = QPushButton(self)
        self.msgBuddyButton.setText("msgBd")
        self.msgBuddyButton.setToolTip("Start messaging with selected buddy")

        self.editBuddyButton = QPushButton(self)
        self.editBuddyButton.setText("edtBd")
        self.editBuddyButton.setToolTip("Edit selected buddy")

        self.removeBuddyButton = QPushButton(self)
        self.removeBuddyButton.setText("rmvBd")
        self.removeBuddyButton.setToolTip("Remove selected buddy from your list")

        self.buddyListWidget = UiBuddyList(self)
        #self.buddyListWidget.setFixedHeight(200)

        self.getListButton = QPushButton(self)
        self.getListButton.setText("GetLst")
        self.getListButton.setToolTip("Get Buddies List from the server")

        self.statusButton = QPushButton(self)
        self.statusButton.setText("STATUS")
        self.statusButton.setToolTip("Change your status")

        self.pushListButton = QPushButton(self)
        self.pushListButton.setText("PshLst")
        self.pushListButton.setToolTip("Push Buddies List to the server")

        self.disableButtons()

        self.layout.addWidget(self.createAccountButton, 0, 0, QtCore.Qt.AlignTop)
        self.layout.addWidget(self.loginButton, 0, 1, QtCore.Qt.AlignTop)
        self.layout.addWidget(self.findBuddyButton, 0, 2, QtCore.Qt.AlignTop)
        self.layout.addWidget(self.msgBuddyButton, 1, 0, QtCore.Qt.AlignTop)
        self.layout.addWidget(self.editBuddyButton, 1, 1, QtCore.Qt.AlignTop)
        self.layout.addWidget(self.removeBuddyButton, 1, 2, QtCore.Qt.AlignTop)
        self.layout.addWidget(self.buddyListWidget, 2, 0, QtCore.Qt.AlignCenter)
        self.layout.addWidget(self.getListButton, 3, 0)
        self.layout.addWidget(self.statusButton, 3, 1)
        self.layout.addWidget(self.pushListButton, 3, 2)

        self.connect(self.removeBuddyButton, QtCore.SIGNAL("clicked()"), self.buddyListWidget.removeSelectedBuddy)
        self.connect(self.createAccountButton, QtCore.SIGNAL("clicked()"), self.createAccount)
        self.connect(self.loginButton, QtCore.SIGNAL("clicked()"), self.login)
        self.connect(self.findBuddyButton, QtCore.SIGNAL("clicked()"), self.showPublicCatalog)
        self.connect(self.editBuddyButton, QtCore.SIGNAL("clicked()"), self.editBuddy)

    def createAccount(self):
        crAccWidget = UiCreateAccountDialog(self.client, self)
        crAccWidget.exec_()

    def login(self):
        loginWidget = UiLoginDialog(self.client, self)
        self.connect(loginWidget, QtCore.SIGNAL("logged()"), self.enableButtons)
        loginWidget.exec_()

    def showPublicCatalog(self):
        catalogDialog = UiCatalogDialog(self.client, self)
        catalogDialog.setBuddyList(self.buddyListWidget)
        catalogDialog.exec_()

    def editBuddy(self):
        buddy = self.buddyListWidget.getSelectedBuddyItem()
        name = buddy.name
        id = buddy.id
        editWidget = UiEditBuddy(id)
        editWidget.pseudonimEdit.setText(name)
        editWidget.setBuddyList(self.buddyListWidget)
        editWidget.exec_()

    def enableButtons(self):
        self.findBuddyButton.setEnabled(True)
        self.msgBuddyButton.setEnabled(True)
        self.editBuddyButton.setEnabled(True)
        self.removeBuddyButton.setEnabled(True)
        self.getListButton.setEnabled(True)
        self.pushListButton.setEnabled(True)

    def disableButtons(self):
        #self.findBuddyButton.setDisabled(True)
        self.msgBuddyButton.setDisabled(True)
        self.editBuddyButton.setDisabled(True)
        self.removeBuddyButton.setDisabled(True)
        self.getListButton.setDisabled(True)
        self.pushListButton.setDisabled(True)


class clientUi(QMainWindow):
    def __init__(self, parent=None):
        QMainWindow.__init__(self, parent)
        self.setWindowTitle("TIMP Client")
        self.setFixedHeight(420)
        self.setFixedWidth(220)

        self.containerWidget = ContainerWidget(self)
        self.setCentralWidget(self.containerWidget)

        #self.buddyListWidget = UiBuddyList()
        #self.setCentralWidget(self.buddyListWidget)

    def closeEvent(self, event):
        print("Closing app")
        self.containerWidget.client.disconnectFromServer()
        event.accept()


if __name__ == "__main__":
    app = QApplication(sys.argv)
    cUi = clientUi()
    cUi.show()

    sys.exit(app.exec_())