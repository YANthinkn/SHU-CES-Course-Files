from PyQt5.QtWidgets import QApplication, QMainWindow
from ChatWindow import Ui_ChatWindow
from LoginWindow import Ui_LoginWindow
import sys


class ChatUI(QMainWindow, Ui_ChatWindow):
    def __init__(self, parent=None):  # 构造方法
        super(ChatUI, self).__init__(parent)  # 运行父类的构造方法
        self.setupUi(self)  # 传递自己


class LoginUI(QMainWindow, Ui_LoginWindow):
    def __init__(self, parent=None):  # 构造方法
        super(LoginUI, self).__init__(parent)  # 运行父类的构造方法
        self.setupUi(self)  # 传递自己


if __name__ == '__main__':
    app = QApplication(sys.argv)  # 创建GUI
    Login = LoginUI()  # 创建PyQt设计的窗体对象
    Login.show()  # 显示窗体
    sys.exit(app.exec_())  # 程序关闭时退出进程
