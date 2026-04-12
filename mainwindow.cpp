#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , resultShown(false)
{
    ui->setupUi(this);

    /*=====================================================================
                                цифры и точка
    =====================================================================*/
    connect(ui->btn0, &QPushButton::clicked, this, &MainWindow::onDigitClicked);
    connect(ui->btn1, &QPushButton::clicked, this, &MainWindow::onDigitClicked);
    connect(ui->btn2, &QPushButton::clicked, this, &MainWindow::onDigitClicked);
    connect(ui->btn3, &QPushButton::clicked, this, &MainWindow::onDigitClicked);
    connect(ui->btn4, &QPushButton::clicked, this, &MainWindow::onDigitClicked);
    connect(ui->btn5, &QPushButton::clicked, this, &MainWindow::onDigitClicked);
    connect(ui->btn6, &QPushButton::clicked, this, &MainWindow::onDigitClicked);
    connect(ui->btn7, &QPushButton::clicked, this, &MainWindow::onDigitClicked);
    connect(ui->btn8, &QPushButton::clicked, this, &MainWindow::onDigitClicked);
    connect(ui->btn9, &QPushButton::clicked, this, &MainWindow::onDigitClicked);
    connect(ui->btnDot, &QPushButton::clicked, this, &MainWindow::onDigitClicked);

    /*=====================================================================
                                операторы
    =====================================================================*/
    connect(ui->btnPlus, &QPushButton::clicked, this, &MainWindow::onOperatorClicked);
    connect(ui->btnMinus, &QPushButton::clicked, this, &MainWindow::onOperatorClicked);
    connect(ui->btnMult, &QPushButton::clicked, this, &MainWindow::onOperatorClicked);
    connect(ui->btnDiv, &QPushButton::clicked, this, &MainWindow::onOperatorClicked);


    /*=====================================================================
                                скобочки
    =====================================================================*/
    connect(ui->btnOpen, &QPushButton::clicked, this, &MainWindow::onParenClicked);
    connect(ui->btnClose, &QPushButton::clicked, this, &MainWindow::onParenClicked);

    /*=====================================================================
                            равно/очистка/удаление
    =====================================================================*/
    connect(ui->btnEqual, &QPushButton::clicked, this, &MainWindow::onEqualClicked);
    connect(ui->btnClear, &QPushButton::clicked, this, &MainWindow::onClearClicked);
    connect(ui->btnDel, &QPushButton::clicked, this, &MainWindow::onDeleteClicked);

    /*=====================================================================
                                функции
    =====================================================================*/
    connect(ui->btnSin, &QPushButton::clicked, this, &MainWindow::onFunctionClicked);
    connect(ui->btnCos, &QPushButton::clicked, this, &MainWindow::onFunctionClicked);
    connect(ui->btnTg, &QPushButton::clicked, this, &MainWindow::onFunctionClicked);
    connect(ui->btnCtg, &QPushButton::clicked, this, &MainWindow::onFunctionClicked);
    connect(ui->btnSqrt, &QPushButton::clicked, this, &MainWindow::onFunctionClicked);
    connect(ui->btnRecip, &QPushButton::clicked, this, &MainWindow::onReciprocalClicked);

    /*=====================================================================
                            память(M+, M-, MR, MC)
    =====================================================================*/
    connect(ui->btnMPlus, &QPushButton::clicked, this, &MainWindow::onMPlusClicked);
    connect(ui->btnMMinus, &QPushButton::clicked, this, &MainWindow::onMMinusClicked);
    connect(ui->btnMR, &QPushButton::clicked, this, &MainWindow::onMRClicked);
    connect(ui->btnMC, &QPushButton::clicked, this, &MainWindow::onMCClicked);

    /*=====================================================================
                                undo & redo
    =====================================================================*/
    connect(ui->btnUndo, &QPushButton::clicked, this, &MainWindow::onUndoClicked);
    connect(ui->btnRedo, &QPushButton::clicked, this, &MainWindow::onRedoClicked);

}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::formatResult(double value) const {
    QString result;
    if (value == std::floor(value) && std::abs(value) < 1e15)
        result = QString::number(static_cast<long long>(value));
    else
        result = QString::number(value, 'g', 15);
    return result;
}

void MainWindow::appendToDisplay(const QString& text)
{
    ui->display->setText(ui->display->text() + text);
}

/*=====================================================================
                            цифры и точка
=====================================================================*/
void MainWindow::onDigitClicked() {
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    if (btn) {
        appendToDisplay(btn->text());
        resultShown = false;
    }
}

/*=====================================================================
        операторы, как будто можно соед с верх, но мало ли измен
=====================================================================*/

void MainWindow::onOperatorClicked() {
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    if (btn) {
        appendToDisplay(btn->text());
        resultShown = false;
    }
}

/*=====================================================================
                            скобочки
=====================================================================*/
void MainWindow::onParenClicked() {
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    if (!btn) return;

    if (resultShown && btn->text() == "(")
        ui->display->clear();

    appendToDisplay(btn->text());
    resultShown = false;
}

/*=====================================================================
                        равно/очистка/удаление
=====================================================================*/
void MainWindow::onEqualClicked() {
    QString expression = ui->display->text().trimmed();
    if (!expression.isEmpty()) {
        try {
            facade.compute(expression.toStdString());
            double result = facade.getCurrentResult();
            ui->display->setText(formatResult(result));
            resultShown = true;
        } catch (const std::exception& e) {
            QMessageBox::warning(this, QString::fromUtf8("Error"), QString::fromStdString(e.what()));
        }
    }
}

void MainWindow::onClearClicked() {
    ui->display->clear();
    resultShown = false;
}

void MainWindow::onDeleteClicked() {
    if (resultShown) {
        ui->display->clear();
        resultShown = false;
    } else {
        QString text = ui->display->text();
        if (!text.isEmpty()) {
            text.chop(1);
            ui->display->setText(text);
        }
    }
}

/*=====================================================================
                                функции
=====================================================================*/
void MainWindow::onFunctionClicked() {
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    if (!btn) return;

    if (resultShown) {
        QString current = ui->display->text();
        ui->display->setText(btn->text() + "(" + current + ")");
        resultShown = false;
        onEqualClicked();

    } else
        appendToDisplay(btn->text() + "(");
}

void MainWindow::onReciprocalClicked() {
    QString current = ui->display->text().trimmed();
    if (!current.isEmpty()) {

        bool isCorrect = false;
        current.toDouble(&isCorrect);
        if (!isCorrect)
            QMessageBox::warning(this, QString::fromUtf8("Error"),
                                 QString::fromUtf8("The 1/x operation applies only to a number"));
        else {

            try {
                facade.compute(("1/(" + current + ")").toStdString());
                double result = facade.getCurrentResult();
                ui->display->setText(formatResult(result));
                resultShown = true;

            } catch (const std::exception& e) {
                QMessageBox::warning(this, QString::fromUtf8("Error"),
                                     QString::fromStdString(e.what()));
            }
        }
    }
}

/*=====================================================================
                            память(M+, M-, MR, MC)
=====================================================================*/
void MainWindow::onMPlusClicked() {
    QString current = ui->display->text().trimmed();
    bool isCorrect = false;
    double value = current.toDouble(&isCorrect);
    if (!isCorrect)
        QMessageBox::warning(this, QString::fromUtf8("Error"),
                             QString::fromUtf8("Unable to save value: an expression has been entered on the screen"));
    else
        facade.addToMemory(value);

}

void MainWindow::onMMinusClicked() {
    QString current = ui->display->text().trimmed();
    bool isCorrect = false;
    double value = current.toDouble(&isCorrect);
    if (!isCorrect)
        QMessageBox::warning(this, QString::fromUtf8("Error"),
                             QString::fromUtf8("Unable to save value: an expression has been entered on the screen"));
    else
        facade.subtractFromMemory(value);

}

void MainWindow::onMRClicked() {
    double memValue = facade.memoryRecall();
    ui->display->setText(formatResult(memValue));
    resultShown = true;
}

void MainWindow::onMCClicked() {
    facade.clearMemory();
}

/*=====================================================================
                                undo & redo
=====================================================================*/
void::MainWindow::onUndoClicked() {
    if (facade.canUndo()) {
        facade.undo();
        double result = facade.getCurrentResult();
        ui->display->setText(formatResult(result));
        resultShown = true;
    }
}

void MainWindow::onRedoClicked() {
    if (facade.canRedo()) {
        facade.redo();
        double result = facade.getCurrentResult();
        ui->display->setText(formatResult(result));
        resultShown = true;
    }
}
