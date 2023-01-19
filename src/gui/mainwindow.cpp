#include "include/mainwindow.h"

#include <string.h>

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), m_notation_x(0), m_hstep(0.1) {

    ui->setupUi(this);
    this->setWindowTitle("SmartCalcV1.0 by Retr0Wawe");

    ui->edit_x->setText("0");
    ui->edit_rx->setText("-10"), ui->edit_rx_max->setText("10");
    ui->edit_ry->setText("-10"), ui->edit_ry_max->setText("10");

    setElementDouble(m_x.first, ui->edit_rx);
    setElementDouble(m_x.second, ui->edit_rx_max);
    setElementDouble(m_y.first, ui->edit_ry);
    setElementDouble(m_y.second, ui->edit_ry_max);

    box.setIcon(QMessageBox::Information);
    box.setDefaultButton(QMessageBox::Ok);
    box.setText("Unrecognized expression!");

    ui->graph->addGraph();

    movie.setFileName("gifs/gachi.gif");
    ui->label->setMovie(&movie);

    movie.start();
}

MainWindow::~MainWindow() { delete ui; }

enum eError MainWindow::calculate(double& result, int x) const noexcept {
    enum eError err = E_UNKNOWN_ERROR;
    const char* to_out = NULL;
    double res = 0;
    int buf_len = 0;

    auto str = ui->edit_expr->text().toStdString();

    if ((err = static_cast<eError>(validate_parentheses(str.c_str()))) &&
        (err = parse_string(str.c_str(), &to_out, &buf_len)) > 0 &&
        (err = calc_expression(to_out, &res, x, buf_len)) > 0) {
        result = res;
    }

    return err;
}

void MainWindow::setElementDouble(double& to_set, QLineEdit* from_set) noexcept {
    to_set = from_set->text().toDouble();
}

void MainWindow::on_edit_expr_editingFinished() noexcept {}

void MainWindow::on_edit_x_textChanged(const QString& x_str) noexcept {
    this->m_notation_x = x_str.toDouble();
}

void MainWindow::on_pushButton_clicked() {
    const char* to_out = NULL;
    int buf_len = 0;
    double y = 0;

    ui->graph->xAxis->setRange(m_x.first, m_x.second);
    ui->graph->yAxis->setRange(m_y.first, m_y.second);

    auto expr_str = ui->edit_expr->text().toStdString();

    if (static_cast<eError>(validate_parentheses(expr_str.c_str())) &&
        parse_string(expr_str.c_str(), &to_out, &buf_len) > 0 &&
        expr_str.find('x') != std::string::npos) {
        for (double x = m_x.first; x < m_x.second; x += m_hstep) {
            if (calc_expression(to_out, &y, x, buf_len) > 0) {
                vec_x.push_back(x);
                vec_y.push_back(y);
            } else {
                break;
            }
        }
        ui->graph->graph(0)->data()->clear();
        ui->graph->graph(0)->addData(vec_x, vec_y);
        ui->graph->replot();
    } else {
        box.exec();
    }
    vec_x.clear(), vec_y.clear();
}

void MainWindow::on_edit_rx_textEdited(const QString& rx_str_min) noexcept {
    this->m_x.first = rx_str_min.toDouble();
}

void MainWindow::on_edit_ry_textEdited(const QString& ry_str_min) noexcept {
    this->m_y.first = ry_str_min.toDouble();
}

void MainWindow::on_pushButton_2_clicked() noexcept {
    double result = 0;

    if (calculate(result, m_notation_x) > 0) {
        ui->edit_result->setText(QString::number(result));
    } else {
        box.exec();
    }
}

void MainWindow::on_edit_rx_max_textEdited(const QString& rx_str_max) noexcept {
    this->m_x.second = rx_str_max.toDouble();
}

void MainWindow::on_edit_ry_max_textEdited(const QString& ry_str_max) noexcept {
    this->m_y.second = ry_str_max.toDouble();
}
