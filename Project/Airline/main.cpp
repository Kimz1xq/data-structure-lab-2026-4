#include <QApplication>
#include "MainWindow.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    QFont font = app.font();
    font.setFamily("Malgun Gothic");
    app.setFont(font);
    MainWindow w;
    w.show();
    return app.exec();
}
