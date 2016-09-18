from PyQt4.QtGui import QWidget, QVBoxLayout, QScrollArea, QMessageBox
from PyQt4.QtCore import Qt, QRect, SIGNAL
from UiBuddyElement import UiBuddyElement

class UiBuddyList(QWidget):
    def __init__(self, parent=None):
        QWidget.__init__(self, parent)
        self.setFixedWidth(200)
        self.setFixedHeight(300)
        self.buddyElementWidgets = list()

        self.setupLayout()
        self.setupScrollArea()

        self.addNewBuddy("1", "TestName")
        self.addNewBuddy("ABCD",  "ABC")
        self.addNewBuddy("3",  "TestName3")
        self.addNewBuddy("4",  "TestName4")
        self.addNewBuddy("5",  "TestName5")
        self.addNewBuddy("6",  "TestName6")
        self.addNewBuddy("7",  "TestName7")
        self.addNewBuddy("8",  "TestName8")
        self.addNewBuddy("9",  "TestName9")
        self.addNewBuddy("10",  "TestName10")
        self.addNewBuddy("11",  "TestName11")

    def setupLayout(self):
        self.containerWidget = QWidget(self)
        self.widgetHeight = 0
        self.containerWidget.setGeometry(QRect(0,0,200,self.widgetHeight))

        self.layout = QVBoxLayout()
        self.containerWidget.setLayout(self.layout)

    def setupScrollArea(self):
        self.scrollArea = QScrollArea(self)
        self.scrollArea.setVerticalScrollBarPolicy(Qt.ScrollBarAsNeeded)
        self.scrollArea.setHorizontalScrollBarPolicy(Qt.ScrollBarAlwaysOff)
        self.scrollArea.setMaximumWidth(200)
        self.scrollArea.setMaximumHeight(300)
        self.scrollArea.setWidgetResizable(False)
        self.scrollArea.setWidget(self.containerWidget)

    def addNewBuddy(self, id, pseudonim):
        newBuddy = UiBuddyElement(self.containerWidget)
        newBuddy.setId(id)
        newBuddy.setName(pseudonim)
        widgetPosition = len(self.buddyElementWidgets)
        self.layout.insertWidget(widgetPosition, newBuddy)
        self.buddyElementWidgets.append(newBuddy)

        self.widgetHeight += 50
        self.containerWidget.resize(200, self.widgetHeight)

        self.connect(newBuddy,SIGNAL("selected(QString)"), self.updateSelections)

    def removeSelectedBuddy(self):
        selectedBuddyId = self.getSelectedBuddyId()
        if selectedBuddyId == None:
            return

        messageBox = QMessageBox(self)
        userReply = messageBox.question(self, "Are you sure?", "Do you want to remove selected buddy?",
                                        QMessageBox.Yes|QMessageBox.No)
        if userReply == QMessageBox.No:
            return

        widgetToRemove = None
        for buddyWidget in self.buddyElementWidgets:
            if buddyWidget.id == selectedBuddyId:
                widgetToRemove = buddyWidget

        self.layout.removeWidget(widgetToRemove)
        self.buddyElementWidgets.remove(widgetToRemove)
        self.widgetHeight -= 50
        self.containerWidget.resize(200, self.widgetHeight)


    def getSelectedBuddyId(self):
        buddy = self.getSelectedBuddyItem()
        if buddy is not None:
            return buddy.id
        return None

    def getSelectedBuddyItem(self):
        for buddy in self.buddyElementWidgets:
            if buddy.selected:
                return buddy
        return None

    def getBuddyItemById(self, id):
        for buddy in self.buddyElementWidgets:
            if buddy.id == id:
                return buddy
        return None

    def updateSelections(self, id):
        for buddy in self.buddyElementWidgets:
            if buddy.id != id:
                buddy.selected = False
                buddy.setStyleSheet("background: white;")