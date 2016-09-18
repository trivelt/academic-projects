#!/usr/bin/python
import unittest

from TimpMessage import TimpMessage, MessageType, Status
from Client.ClientMessageExchanger import ClientMessageExchanger

class TestMessages:
    textMessage = "TEXT_MESSAGE * TIMP 0.9\r\n" \
                "Date: unixTime\r\n" \
                "CSeq: 51\r\n" \
                "Sender: MyUserName\r\n" \
                "Receiver: otherUserName\r\n" \
                "MessageId: 921\r\n" \
                "Content-Length: 24\r\n\r\n" \
                "MESSAGE CONTENT Test1234\r\n"

    userStatus = "USER_STATUS * TIMP 0.9\r\n" \
                "Date: unixTime\r\n" \
                "CSeq: 9\r\n" \
                "Sender: MyUserName\r\n" \
                "NewStatus: available\r\n"

    wrongMessage = "TEST * TIMP 0.9\r\n" \
                    "FOO BAR\r\n"


class TestTimpMessage(unittest.TestCase):
    def setUp(self):
        self.textMessage = TimpMessage(TestMessages.textMessage)
        self.uStatusMessage = TimpMessage(TestMessages.userStatus)
        self.wrongMessage = TimpMessage(TestMessages.wrongMessage)

    def testGetLineByNumber(self):
        thirdLine = "Sender: MyUserName"
        self.assertEqual(self.textMessage.getLineByNumber(3), thirdLine)
        self.assertEqual(self.textMessage.getLineByNumber(41), "")

    def testGetLineByText(self):
        senderLine = "Sender: MyUserName"
        self.assertEqual(self.textMessage.getLineByText("Sender:"), senderLine)
        self.assertEqual(self.textMessage.getLineByText("Test text 12345"), "")

    def testType(self):
        self.assertEqual(self.textMessage.type(), MessageType.TEXT_MESSAGE)
        self.assertEqual(self.uStatusMessage.type(), MessageType.USER_STATUS)
        self.assertEqual(self.wrongMessage.type(), MessageType.UNKNOWN)

    def testGetCseq(self):
        self.assertEqual(self.textMessage.cseq(), 51)
        self.assertEqual(self.wrongMessage.cseq(), None)

    def testValid(self):
        self.assertEqual(self.uStatusMessage.isValid(), True)
        self.assertEqual(self.wrongMessage.isValid(), False)

    def testGetStatus(self):
        self.assertEqual(self.uStatusMessage.getStatus(), Status.AVAILABLE)
        self.assertEqual(self.textMessage.getStatus(), None)

    def testGetSender(self):
        self.assertEqual(self.uStatusMessage.getSender(), "MyUserName")
        self.assertEqual(self.wrongMessage.getSender(), "")

    def testGetReceiver(self):
        self.assertEqual(self.textMessage.getReceiver(), "otherUserName")
        self.assertEqual(self.uStatusMessage.getReceiver(), "")

    def testGetContentLength(self):
        self.assertEqual(self.textMessage.getContentLength(), 24)
        self.assertEqual(self.uStatusMessage.getContentLength(), 0)

    def testGetContent(self):
        content = "MESSAGE CONTENT Test1234"
        self.assertEqual(self.textMessage.getContent(), content)
        self.assertEqual(self.uStatusMessage.getContent(), None)

    def testHasContent(self):
        self.assertEqual(self.textMessage.hasContent(), True)
        self.assertEqual(self.uStatusMessage.hasContent(), False)

    def tearDown(self):
        pass

class TestClientMessageExchanger(unittest.TestCase):
    def setUp(self):
        ClientMessageExchanger.cseq = 1

    def testCreateRegisterMsg(self):
        login = "login"
        password = "pswd123"
        msgText = ClientMessageExchanger.createRegisterMessage(login, password)
        timpMsg = TimpMessage(msgText)
        self.assertEqual(timpMsg.cseq(), 1)
        self.assertEqual(timpMsg.getValueOfParameter("Username"), login)
        self.assertEqual(timpMsg.getValueOfParameter("Password"), password)

        nextMsg = ClientMessageExchanger.createRegisterMessage(login, password)
        self.assertEqual(TimpMessage(nextMsg).cseq(), 2)

    def tearDown(self):
        pass

if __name__ == '__main__':
    unittest.main()