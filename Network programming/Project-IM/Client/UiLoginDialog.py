from PyQt4.QtGui import QDialog, QGridLayout, QLabel, QLineEdit, QPushButton
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

class UiLoginDialog(QDialog):
    def __init__(self, clientObject, parent=None):
        QDialog.__init__(self, parent)
        self.client = clientObject
        self.setFixedWidth(300)
        self.setFixedHeight(300)
        self.setWindowTitle("Login")

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

        self.loginButton = QPushButton(self)
        self.loginButton.setText("Login")

        self.layout.addWidget(self.loginLabel, 0, 0)
        self.layout.addWidget(self.loginEdit, 0, 1)
        self.layout.addWidget(self.passwordLabel, 1, 0)
        self.layout.addWidget(self.passwordEdit, 1, 1)
        self.layout.addWidget(self.infoLabel, 2, 0, 1, 0)
        self.layout.addWidget(self.loginButton, 3, 0, 1, 0)

        self.connect(self.loginButton, SIGNAL("clicked()"), self.login)

    def login(self):
        self.client.connectToServer()

        login = self.loginEdit.text()
        password = self.passwordEdit.text()
        authMessage = ClientMessageExchanger.createAuthMessage(login, password)
        self.client.sendMessage(authMessage)
        time.sleep(1)
        requestCseq = TimpMessage(authMessage).cseq()
        receivedResponse = MessagesStack.getResponseMessageByCseq(requestCseq)
        if receivedResponse.type() is MessageType.SUCCESS:
            self.infoLabel.setText("Logged successfully")
            self.hideElements()
            self.emit(SIGNAL("logged()"))
            self.client.loggedIn = True
            ClientInfo.username = login
            ClientInfo.status = Status.AVAILABLE
            self.client.updateStatuses()
        elif receivedResponse.type() is MessageType.NOT_OK:
            self.infoLabel.setText("Cannot authenticate user")
            self.client.disconnectFromServer()

    def hideElements(self):
        self.passwordLabel.setVisible(False)
        self.passwordEdit.setVisible(False)
        self.loginLabel.setVisible(False)
        self.loginEdit.setVisible(False)
        self.loginButton.setVisible(False)
