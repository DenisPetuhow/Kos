#include "progressbar.h"

CProgressBar::CProgressBar(QWidget *parent) :
	QWidget(parent)
{
	this->setWindowTitle(QObject::trUtf8("Выполнение расчетов"));
	progressBar = new QProgressBar(this);
	label = new QLabel(this);
    label->setSizeIncrement(400,60);
    progressBar->setSizeIncrement(400,50);
    setFixedSize(400, 90);
	vBoxLayout = new QVBoxLayout(this);
	vBoxLayout->addWidget(label);
	vBoxLayout->addWidget(progressBar);
	progressBar->setValue(0);
	connect(progressBar, SIGNAL(valueChanged(int)), this, SLOT(setValue(int)));
	setWindowModality(Qt::ApplicationModal);
	setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint
			| Qt::SubWindow);
	installEventFilter(this);
	moveWindowToCenter();
}

void CProgressBar::setValue(int tt)
{
	progressBar->setValue(tt);
}

void CProgressBar::setText(QString st)
{
	label->setText(st);
}

void CProgressBar::moveWindowToCenter()
{
	QRect frect = frameGeometry();
	frect.moveCenter(QDesktopWidget().availableGeometry().center());
	setGeometry(frect);
}
