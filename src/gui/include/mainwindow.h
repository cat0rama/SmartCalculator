#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QMessageBox>
#include <QMovie>
#include <QPair>
#include <QVector>

#ifdef __cplusplus
extern "C" {
#endif

#include "include/defines.h"
#include "include/executer.h"
#include "include/parse_infix.h"
#include "include/stack.h"
#include "include/utils.h"

#ifdef __cplusplus
}
#endif

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
    using Range = QPair<double, double>;

  public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

  private slots:
    enum eError calculate(double& result, int x) const noexcept;

    void setElementDouble(double& to_set, QLineEdit* from_set) noexcept;

    void on_edit_expr_editingFinished() noexcept;

    void on_edit_x_textChanged(const QString& x_str) noexcept;

    void on_pushButton_clicked();

    void on_edit_rx_textEdited(const QString& rx_str_min) noexcept;

    void on_edit_ry_textEdited(const QString& ry_str_min) noexcept;

    void on_pushButton_2_clicked() noexcept;

    void on_edit_rx_max_textEdited(const QString& ry_str_max) noexcept;

    void on_edit_ry_max_textEdited(const QString& ry_str_max) noexcept;

  private:
    QVector<double> vec_x, vec_y;
    Ui::MainWindow* ui;
    double m_notation_x;
    QMessageBox box;
    Range m_x, m_y;
    double m_hstep;
    QMovie movie;
};
#endif // MAINWINDOW_H
