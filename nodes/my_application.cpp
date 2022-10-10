#include <QApplication>
#include <QIcon>
#include "main_window.h"


int main(int argc, char *argv[])
{

  QApplication a(argc, argv);

  MainWindow w;

  // set the window title as the node name
  w.setWindowTitle("My Application");

  // load the icon from our qrc file and set it as the application icon
  QIcon icon(":/icons/my_gui_icon.png");
  w.setWindowIcon(icon);

  w.show();
  return a.exec();
}
