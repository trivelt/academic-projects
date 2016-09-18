from TimpMessage import MessageType

class MessagesStack:
    """
    Store 10 last received messages
    """

    sizeOfStack = 10
    messages = list()

    @staticmethod
    def push(message):
        if len(MessagesStack.messages) == MessagesStack.sizeOfStack:
            del MessagesStack.messages[0]
        MessagesStack.messages.append(message)

    @staticmethod
    def getMessageByCSeq(cseq):
        for message in MessagesStack.messages:
            if message.cseq() == cseq:
                return message
        return None

    @staticmethod
    # Zamiast tego: getResponsMessageByCseq - szukamy tylko w SUCCESS i NOT_OK
    def getMessageByCSeqAndType(cseq, type):
        for message in MessagesStack.messages:
            if message.cseq() == cseq and message.type() == type:
                return message
        return None

    @staticmethod
    def getResponseMessageByCseq(cseq):
        for message in MessagesStack.messages:
            if message.cseq() == cseq and (message.type() is MessageType.SUCCESS or message.type() is MessageType.NOT_OK):
                return message
        return None