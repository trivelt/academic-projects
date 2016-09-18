from PyQt4.QtGui import QDialog, QGridLayout, QLineEdit, QPushButton, QTableWidget, QTableWidgetItem, QLabel
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
from UiBuddyElement import UiBuddyElement

class UiEditBuddy(QDialog):
    def __init__(self, name, parent=None):
        QDialog.__init__(self, parent)
        self.username = name
        self.setFixedWidth(300)
        self.setFixedHeight(200)
        self.setWindowTitle("Edit buddy")

        self.layout = QGridLayout()
        self.setLayout(self.layout)

        self.usernameLabel = QLabel(self)
        self.usernameLabel.setText("Buddy ID")

        self.usernameEdit = QLineEdit(self)
        self.usernameEdit.setText(self.username)
        self.usernameEdit.setEnabled(False)

        self.pseudonimLabel = QLabel(self)
        self.pseudonimLabel.setText("Pseudonim")

        self.pseudonimEdit = QLineEdit(self)
        self.pseudonimEdit.setText(self.username)

        self.cancelButton = QPushButton(self)
        self.cancelButton.setText("Cancel")

        self.okButton = QPushButton(self)
        self.okButton.setText("OK")

        self.layout.addWidget(self.usernameLabel, 0, 0)
        self.layout.addWidget(self.usernameEdit, 0, 1)
        self.layout.addWidget(self.pseudonimLabel, 1, 0)
        self.layout.addWidget(self.pseudonimEdit, 1, 1)
        self.layout.addWidget(self.cancelButton, 2, 0)
        self.layout.addWidget(self.okButton, 2, 1)

        self.connect(self.cancelButton, SIGNAL("clicked()"), self.close)
        self.connect(self.okButton, SIGNAL("clicked()"), self.addOrEditBuddy)

    def setBuddyList(self, buddyList):
        self.buddyList = buddyList

    def addOrEditBuddy(self):
        buddy = self.buddyList.getBuddyItemById(self.username)
        if buddy is None:
            self.addBuddy()
        else:
            self.editBuddy(buddy)
        self.close()

    def addBuddy(self):
        pseudonim = str(self.pseudonimEdit.text())
        self.buddyList.addNewBuddy(self.username, pseudonim)

    def editBuddy(self, buddy):
        pseudonim = str(self.pseudonimEdit.text())
        buddy.setName(pseudonim)
        buddy.setId(self.username)
