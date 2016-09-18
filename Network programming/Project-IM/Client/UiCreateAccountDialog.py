from PyQt4.QtGui import QDialog, QGridLayout, QLabel, QLineEdit, QPushButton
from PyQt4.QtCore import Qt, QRect, SIGNAL
from ClientMain import ClientMain
import time
import sys
from os import path
sys.path.append( path.dirname( path.dirname( path.abspath(__file__) ) ) )
from MessagesStack import MessagesStack
from ClientMessageExchanger import ClientMessageExchanger
from TimpMessage import TimpMessage, MessageType

class UiCreateAccountDialog(QDialog):
    def __init__(self, clientObject, parent=None):
        QDialog.__init__(self, parent)
        self.client = clientObject
        self.setFixedWidth(300)
        self.setFixedHeight(300)
        self.setWindowTitle("Create account")

        self.layout = QGridLayout()
        self.setLayout(self.layout)

        self.loginLabel = QLabel(self)
        self.loginLabel.setText("Login: ")
        self.loginEdit = QLineEdit(self)

        self.passwordLabel = QLabel(self)
        self.passwordLabel.setText("Password: ")
        self.passwordEdit = QLineEdit(self)

        self.infoLabel = QLabel(self)
        self.infoLabel.setFixedSize(300, 20)
        self.infoLabel.setAlignment(Qt.AlignCenter)

        self.createAccountButton = QPushButton(self)
        self.createAccountButton.setText("Create account")

        self.layout.addWidget(self.loginLabel, 0, 0)
        self.layout.addWidget(self.loginEdit, 0, 1)
        self.layout.addWidget(self.passwordLabel, 1, 0)
        self.layout.addWidget(self.passwordEdit, 1, 1)
        self.layout.addWidget(self.infoLabel, 2, 0, 1, 0)
        self.layout.addWidget(self.createAccountButton, 3, 0, 1, 0)

        self.connect(self.createAccountButton, SIGNAL("clicked()"), self.createAccount)

    def createAccount(self):
        self.client.connectToServer()

        login = self.loginEdit.text()
        password = self.passwordEdit.text()
        registerMessage = ClientMessageExchanger.createRegisterMessage(login, password)
        self.client.sendMessage(registerMessage)
        time.sleep(1)
        requestCseq = TimpMessage(registerMessage).cseq()
        receivedResponse = MessagesStack.getResponseMessageByCseq(requestCseq)
        if receivedResponse.type() is MessageType.SUCCESS:
            self.infoLabel.setText("New account created successfully")
        elif receivedResponse.type() is MessageType.NOT_OK:
            self.infoLabel.setText("Error while creating account")
        self.client.disconnectFromServer()