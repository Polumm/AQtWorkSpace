#ifndef DIGITALCLOCK_H
#define DIGITALCLOCK_H

#include <QDialog>
#include <QLCDNumber>

namespace Ui {
class DigitalClock;
}

class DigitalClock : public QDialog
{
    Q_OBJECT

public:
    explicit DigitalClock(QWidget *parent = nullptr);
    ~DigitalClock();
    void showTime();

private:
    Ui::DigitalClock *ui;
};

#endif // DIGITALCLOCK_H
