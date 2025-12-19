#ifndef SPEECHTOTEXT_H
#define SPEECHTOTEXT_H

#include <QMainWindow>
#include <QQueue>
#include <QMutex>
#include <QTimer>
namespace Ui {
class SpeechToText;
}

class SpeechToText : public QMainWindow
{
    Q_OBJECT

public:
    explicit SpeechToText(QWidget *parent = nullptr);
    ~SpeechToText();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::SpeechToText *ui;
    static QString g_stt_text;
    QTimer timer_;
public:
    static QMutex g_mutx;
    static QQueue<QString> g_queue;
};

#endif // SPEECHTOTEXT_H
