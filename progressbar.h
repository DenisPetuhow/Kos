#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H
#include <QProgressBar>
#include <QDesktopWidget>
#include <QWidget>
#include <QLabel>
#include <QEvent>
#include <QKeyEvent>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QString>

class CProgressBar: public QWidget
{
Q_OBJECT
public:
	//! \brief Конструктор по умолчанию.
 	explicit CProgressBar(QWidget *parent = 0);

 	/*!
 	 * \brief Устанавливает тип выполняемого действия.
 	 * \param st - текст описываемого действия действия.
 	 */
	void setText(QString st);

public slots:
	/*!
	 * \brief Устанавливает текуще сначение выполняемого действия.
	 *
	 * \param tt - процент выполнения.
	 */
	void setValue(int tt);

private:
	//! \brief Перемещает окно на цент экрана.
	void moveWindowToCenter();

private:
	QProgressBar *progressBar;
	QVBoxLayout *vBoxLayout;
	QLabel* label;
};

#endif // PROGRESSBAR_H
