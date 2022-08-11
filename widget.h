#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTableWidgetItem>
#include <windows.h>
#include <tlhelp32.h>
#include <vector>
#include <algorithm>
#include <tchar.h>
#include <iostream>
#include <math.h>
#include <string>
using std::vector;
using std::string;

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

struct PEInfo{
    QString pName;
    DWORD pID;
    int index;
};

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_selDllBtn_clicked();

    void on_updateProcBtn_clicked();

    void on_procTable_itemClicked(QTableWidgetItem *item);

    void on_submitBtn_clicked();

    void on_procSearchEdit_textChanged(const QString &arg1);

private:
    Ui::Widget *ui;
    vector<PEInfo> peInfoArr;
    vector<PEInfo> newPeInfoArr;
    int selIndex = -1;
    int selectPid = -1;
};
#endif // WIDGET_H
