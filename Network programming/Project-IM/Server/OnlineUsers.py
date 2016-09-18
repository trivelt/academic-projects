
class OnlineUsers:
    users = list()

    @staticmethod
    def addUser(user):
        OnlineUsers.users.append(user)

    @staticmethod
    def removeUser(name):
        user = OnlineUsers.findUser(name)
        if user is not None:
            OnlineUsers.users.remove(user)

    @staticmethod
    def isOnline(name):
        user = OnlineUsers.findUser(name)
        isOnline = user is not None
        return isOnline

    @staticmethod
    def getSocket(name):
        user = OnlineUsers.findUser(name)
        return user.getSocket()

    @staticmethod
    def findUser(name):
        for user in OnlineUsers.users:
            if user.username == name:
                return user
        return None