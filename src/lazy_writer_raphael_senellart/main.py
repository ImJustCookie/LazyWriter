import sys
import os
from PyQt6.QtWidgets import QApplication
from PyQt6.QtCore import QFile, QTextStream
from lazy_writer_raphael_senellart.window import MainWindow

def load_stylesheet(file_path):
    """Load a stylesheet from an external CSS file."""
    if getattr(sys, 'frozen', False):  # Running as a bundled executable
        file_path = os.path.join(sys._MEIPASS, file_path)
    file = QFile(file_path)
    if not file.open(QFile.OpenModeFlag.ReadOnly | QFile.OpenModeFlag.Text):
        print(f"Failed to open stylesheet: {file_path}")
        return ""
    stream = QTextStream(file)
    stylesheet = stream.readAll()
    file.close()
    return stylesheet

def main():
    app = QApplication(sys.argv)
    # Ensure the path matches what we specified in the spec (static folder)
    stylesheet = load_stylesheet("static/style.css")
    app.setStyleSheet(stylesheet)
    window = MainWindow()
    window.show()
    sys.exit(app.exec())

if __name__ == "__main__":
    main()
