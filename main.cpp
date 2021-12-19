#include <QApplication>
#include <QObject>
#include <QProcess>
#include <systemtrayupdater.h>

QProcess *createProcess(const QStringList & programAndArgs) {

    QString program = programAndArgs.first(); // The first one is the program we want to execute, remove it
    QStringList programArgs = programAndArgs.mid(1); // Now what's left is the arguments for the program we want to execute

    QProcess *process = new QProcess();
    process->setProgram(program);
    process->setArguments(programArgs);
    process->setProcessChannelMode(QProcess::ForwardedChannels);
    return process;
}

int main(int argc, char *argv[])
{
    // Don't make this app's window steal the focus
    QCoreApplication::setAttribute(Qt::AA_PluginApplication, true);

    QApplication *a = new QApplication(argc, argv);

    const QStringList programAndArgs = a->arguments().mid(1); // The first one is this app, ignore it

    QString toolTip = programAndArgs.join(" ");

    QProcess * process = createProcess(programAndArgs);

    SystemTrayUpdater *systemTrayUpdater = new SystemTrayUpdater(toolTip);
    systemTrayUpdater->start();

    QObject::connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),a,
                     [=](int exitCode, QProcess::ExitStatus){
        systemTrayUpdater->stop();
        a->exit(exitCode);
    });

    process->start();

    return a->exec();
}
