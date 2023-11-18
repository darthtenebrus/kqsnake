#include <QApplication>
#include <QCommandLineParser>
#include <QTranslator>
#include <iostream>
#include <QDir>
#include <KCrash>
#include <QSystemSemaphore>
#include <QSharedMemory>
#include <QMessageBox>

#include "mainwindow.h"
#include "version.h"

#ifdef _DEBUG

#include <QDebug>

#endif

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);
    QTranslator mainTranslator;
    // look up e.g. :/i18n/myapp_de.qm
    if (mainTranslator.load(
            QLocale(),
            QLatin1String("mainwindow"),
            QLatin1String("_"),
            QLatin1String(":/i18n"))) {
        QApplication::installTranslator(&mainTranslator);
    }

    try {
        const QStringList &cmd_args = QCoreApplication::arguments();
        if (!cmd_args.empty() && cmd_args.size() > 1) {
            const QString &firstArg = cmd_args.value(0);
            const QString &progName = firstArg.contains(QDir::separator()) ?
                                      firstArg.section(QDir::separator(), -1, -1) : firstArg;
            std::cout << progName.toStdString() << " " << QObject::tr("Simple Snake Game realization").toStdString()
                      << "\n";
            std::cout << QObject::tr("Created by: ")
                    .toStdString() << "Eugene E. Sorochinskiy <manager@darkguard.net>\n\n";
            const QString &optVal = cmd_args.value(1);
            if (optVal.toLower() == "-h" || optVal == "--help") {
                std::cout << QObject::tr("Usage %1 [options]")
                        .arg(progName).toStdString() << "\n";
                std::cout << QObject::tr("Valid options:").toStdString() << "\n";
                std::cout << "-h, -H, --help\t\t" << QObject::tr("show this help").toStdString() << "\n";
                std::cout << "-v, -V, --version\t" << QObject::tr("display version").toStdString() << "\n\n";

            } else if (optVal.toLower() == "-v" || optVal == "--version") {
                std::cout << progName.toStdString() << " v." << APP_VERSION << "\n\n";
            } else {
                std::cout << QObject::tr("Unknown option %1").arg(cmd_args.value(1)).toStdString() << "\n";
                std::cout << QObject::tr("Launch %1 -h or %1 --help for help")
                        .arg(progName).toStdString() << "\n\n";

            }
            std::cout << QObject::tr("Launch this application without any parameters to see its main functional")
                    .toStdString() << "\n\n";
            return 0;
        }
    } catch (const std::exception &ex) {
        return 1;
    }


    const QString &semaph_id = "kqsnake_semaphore";
    const QString &shared_id = "kqsnake_shared_mem";
    QSystemSemaphore semaphore(semaph_id, 1);
    semaphore.acquire();

#ifndef Q_OS_WIN32
    QSharedMemory nix_fix_shared_memory(shared_id);
    if (nix_fix_shared_memory.attach()) {
        nix_fix_shared_memory.detach();
    }
#endif

    QSharedMemory sharedMemory(shared_id);
    bool is_running = false;
    if (sharedMemory.attach()) {
        is_running = true;
    } else {
        sharedMemory.create(1);
    }
    semaphore.release();

    if (is_running) {


        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setWindowTitle(QObject::tr("Already Running"));
        msgBox.setText(QObject::tr("Application Already Running"));
        msgBox.exec();
        return 1;

    } else {

        KAboutData aboutData(QStringLiteral("KQsnake"),
                             QObject::tr("Snake Game"), APP_VERSION,
                             QObject::tr("Another Game Of Snake under KDE"),
                             KAboutLicense::GPL_V3, "© 2023 E.Sorochinskiy",
                             QObject::tr("Control the snake and collect as many apples as you can"),
                             "https://www.darkguard.net");

        aboutData.addAuthor("Eugene E. Sorochinskiy", "Design & code",
                            "manager@darkguard.net",
                            "https://darkguard.net");
        aboutData.setTranslator("Eugene E. Sorochinskiy",
                                "webmaster@darkguard.net");
        KAboutData::setApplicationData(aboutData);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/desktop/64x64/kqsnake.png"), QSize(), QIcon::Normal, QIcon::Off);
        QApplication::setWindowIcon(icon);
        KCrash::initialize();

        QCommandLineParser parser;
        aboutData.setupCommandLine(&parser);
        parser.process(app);
        aboutData.processCommandLine(&parser);

        auto *w(new MainWindow());
        w->showMaximized();
        return QApplication::exec();
    }

}
