from TimpMessage import Status

class ClientInfo:
    username = None
    status = Status.OFFLINE
    statusDesc = ""
    buddies = list()

    @staticmethod
    def getStatus():
        return Status.toString(ClientInfo.status)