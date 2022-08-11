#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>
#include <QMainWindow>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setFixedSize(600,410);
    setWindowTitle("【Dll注入器】 code by ngiokweng");
}

Widget::~Widget()
{
    delete ui;
}


//選擇要注入哪個Dll
void Widget::on_selDllBtn_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this,"選擇要注入哪個Dll ^.^");
    QStringList list = filePath.split("/");
    QString fileName = list[list.length()-1];
    list = fileName.split(".");
    if(list.length() == 1 || list[1] != "dll"){
        QMessageBox::critical(this,"提示","請選擇Dll文件");
        return;
    }

    ui->showSelDll->setText(filePath);
}

void Widget::on_updateProcBtn_clicked()
{
    //清空表格
    ui->procTable->clear();
    //清空數據
    peInfoArr.clear();
    //開放進程搜索框
    ui->procSearchEdit->setEnabled(1);
    HANDLE hProcAll = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32 pe = { 0 };
    pe.dwSize = sizeof(pe);

    //獲取所有進程，並存在peInfoArr中
    while (Process32Next(hProcAll, &pe)) {
        PEInfo curPeInfo;
        curPeInfo.pName = QString("%1").arg(wcstok(pe.szExeFile,L"\u0000"));
        curPeInfo.pID = pe.th32ProcessID;
        peInfoArr.emplace_back(curPeInfo);
        qDebug()<<curPeInfo.pName<<' '<<curPeInfo.pID;

    }
    CloseHandle(hProcAll);

    //按進程名排序(小到大)
    sort(peInfoArr.begin(),peInfoArr.end(),[&](PEInfo& a,PEInfo&b){
        return a.pName<b.pName;
    });

    //設置procTable
    ui->procTable->setColumnCount(1);
    ui->procTable->setColumnWidth(0,531);
    ui->procTable->horizontalHeader()->setVisible(false);
    ui->procTable->setRowCount(peInfoArr.size());
    ui->procTable->setEditTriggers(QAbstractItemView::NoEditTriggers); //將表格設為"只讀"

    for(int i = 0;i<peInfoArr.size();i++){
        QTableWidgetItem* item = new QTableWidgetItem(QString("進程名:%1  |  進程PID:%2").arg(peInfoArr[i].pName).arg(peInfoArr[i].pID));
        ui->procTable->setItem(i,0,item);
    }

}

//計算選中item的進程索引
void Widget::on_procTable_itemClicked(QTableWidgetItem *item)
{
    string itemStr = item->text().toStdString();
    int j = 0;
    selectPid = 0;
    for(int i = itemStr.length()-1;itemStr[i]!=':';i--){
        selectPid+=pow(10,j++)*(itemStr[i]-'0');
    }
}


void Widget::on_submitBtn_clicked()
{
    if(ui->showSelDll->toPlainText() == "" || selectPid == -1){
        QMessageBox::critical(this,"提示","請選擇【Dll】和【注入進程】後再注入");
        return;
    }

    /** 類型轉換：將QString -> const wchar_t* **/
    std::wstring wStr = ui->showSelDll->toPlainText().toStdWString();
    const wchar_t* DLL_PATH = wStr.c_str();

    DWORD dwPID = selectPid;
    HANDLE hProcess = NULL;
    HANDLE hThread = NULL;
    HMODULE hMod = NULL;
    LPVOID pRemoteBuf = NULL;
    DWORD dwBufSize = (DWORD)(_tcslen(DLL_PATH) + 1) * sizeof(TCHAR);
    LPTHREAD_START_ROUTINE pThreadProc;
    if (!dwPID) {
        qDebug() << "取不到指定進程PID，可能是進程未打開" << endl;
        return;
    }

    if (!(hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPID))) {
        _tprintf(L"OpenProcess(%d) failed!!! [%d]\n", dwPID, GetLastError());
        return;
    }

    pRemoteBuf = VirtualAllocEx(hProcess, NULL, dwBufSize, MEM_COMMIT, PAGE_READWRITE);  // 在目標進程空間中申請內存

    WriteProcessMemory(hProcess, pRemoteBuf, (LPVOID)DLL_PATH, dwBufSize, NULL);  // 向在目標進程申請的內存空間中寫入DLL文件的路徑

    hMod = GetModuleHandle(L"kernel32.dll"); //LoadLibrary函數在kernel32.dll中
    pThreadProc = (LPTHREAD_START_ROUTINE)GetProcAddress(hMod, "LoadLibraryW");  // 取得LoadLibraryW()函數的地址

    hThread = CreateRemoteThread(hProcess, NULL, 0, pThreadProc, pRemoteBuf, 0, NULL); //遠程注入Dll的核心代碼，使目標進程調用LoadLibrary加載你寫好的Dll
    if (hThread != NULL) {
        qDebug() << "注入成功!!!" << endl;
    }
    QMessageBox::information(this,"提示","注入中~~");
    WaitForSingleObject(hThread, INFINITE);
    CloseHandle(hThread);
    CloseHandle(hProcess);


}

void Widget::on_procSearchEdit_textChanged(const QString &arg1)
{

    newPeInfoArr.clear();
    for(int i = 0;i<peInfoArr.size();i++){
        if(peInfoArr[i].pName.startsWith(arg1,Qt::CaseInsensitive)){ //不區分大小寫
            newPeInfoArr.emplace_back(peInfoArr[i]);
        }
    }
    if(newPeInfoArr.size() == 0)return;

    //清空表格
    ui->procTable->clear();
    //設置procTable
    ui->procTable->setRowCount(newPeInfoArr.size());

    for(int i = 0;i<newPeInfoArr.size();i++){
        QTableWidgetItem* item = new QTableWidgetItem(QString("進程名:%1  |  進程PID:%2").arg(newPeInfoArr[i].pName).arg(newPeInfoArr[i].pID));
        ui->procTable->setItem(i,0,item);
    }

}
