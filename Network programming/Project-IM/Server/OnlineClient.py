from TimpMessage import Status

class OnlineClient:
    def __init__(self, username, sock):
        self.username = username
        self.status = Status.AVAILABLE
        self.statusDesc = ""
        self.socket = sock

    def setStatus(self, status, desc):
        self.status = status
        self.statusDesc = desc

    def getSocket(self):
        return self.socket

    def getStatus(self):
        return Status.toString(self.status)

    def getStatusDesc(self):
        return self.statusDesc