from PyQt4.QtGui import QWidget, QLabel, QFont
from PyQt4.QtCore import QRect, SIGNAL

class UiBuddyElement(QWidget):
    def __init__(self, parent=None):
        QWidget.__init__(self, parent)
        self.setFixedWidth(200)
        self.setFixedHeight(50)

        self.id = ""
        self.name = ""
        self.statusWithDesc = ""
        self.selected = False

        self.nameLabel = QLabel(self)
        self.nameLabel.setGeometry(QRect(5, 0, 190, 20))
        self.nameLabel.setFont(QFont("Arial", 12, QFont.Bold))

        self.statusLabel = QLabel(self)
        self.statusLabel.setGeometry(QRect(5, 20, 190, 20))

        #self.setName("Test name")
        self.setStatus("AVAILABLE", "test desc")

    def mouseDoubleClickEvent(self, QMouseEvent):
        self.setStyleSheet("background: grey;")

    def mousePressEvent(self, QMouseEvent):
        if self.selected:
            self.selected = False
            self.setStyleSheet("background: white;")
        else:
            self.selected = True
            self.setStyleSheet("background: grey;")
            self.emit(SIGNAL("selected(QString)"), self.id)


    def setId(self, id):
        self.id = id
        self.updateToolTips()

    def setName(self, name):
        self.name = name
        self.nameLabel.setText(name)
        self.updateToolTips()

    def setStatus(self, status, description=""):
        self.statusWithDesc = status + ": " + description
        self.statusLabel.setText(self.statusWithDesc)
        self.updateToolTips()

    def updateToolTips(self):
        toolTipText = self.name + "\n"
        toolTipText += "Id: " + self.id + "\n"
        toolTipText += self.statusWithDesc
        self.nameLabel.setToolTip(toolTipText)
        self.statusLabel.setToolTip(toolTipText)