#include "stdafx.h"
#include "TitleBar.h"


TitleBar::TitleBar(QWidget *parent)
	: QWidget(parent)
{
	InitView();
	SetupEvents();
	SetupEffects();
}

void ShowNoramlMethod()
{

}
TitleBar::~TitleBar()
{
}

void TitleBar::setStatus(ButtonStatus statusx)
{
	switch (statusx)
	{
	case NORMAL:
		btnClose->changeStatus(NORMAL);
		btnMin->changeStatus(NORMAL);
		btnMax->changeStatus(NORMAL);
		break;
	case NOSTATUS:
		btnClose->changeStatus(NOSTATUS);
		btnMin->changeStatus(NOSTATUS);
		btnMax->changeStatus(NOSTATUS);
		break;
	default:
		btnClose->changeStatus(NORMAL);
		btnMin->changeStatus(NORMAL);
		btnMax->changeStatus(NORMAL);
		break;
	}
}

void TitleBar::setbtnMaxType(bool isMax)
{
	btnMax->toggleResizeButton(isMax);
	if (isMax){
		btnMax->setToolTip(QString::fromLocal8Bit("���»�ԭ"));
	}
	else{
		btnMax->setToolTip(QString::fromLocal8Bit("ȫ��"));
	}
}

void TitleBar::mouseDoubleClickEvent(QMouseEvent * event)
{
	Q_UNUSED(event);
	switch (parentWidget()->windowState())
	{
	case Qt::WindowNoState:
		parentWidget()->showMaximized();
		break;
	case Qt::WindowMaximized:
		parentWidget()->showNormal();
		break;
	case Qt::WindowFullScreen:
		parentWidget()->showNormal();
		break;
	default:
		parentWidget()->showNormal();
		break;
	}
}

void TitleBar::mousePressEvent(QMouseEvent * event)
{
	if (ReleaseCapture())
	{
		if (this->window()->isTopLevel()&& Qt::WindowFullScreen != this->window()->windowState())
		{
			SendMessage(HWND(this->window()->winId()), WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);
		}
	}
	event->ignore();
}


void TitleBar::InitView()
{
	setFixedHeight(25);
	setAutoFillBackground(true);
	SetupUI();
	btnClose->move(LeftValue, TopValue);
	btnMin->move(LeftValue + btnClose->width() + SpacingValue, TopValue);
	btnMax->move(LeftValue + btnMin->width() + btnMax->width() + 2 * SpacingValue, TopValue);
}

void TitleBar::SetupUI()
{
	btnClose = new ButtonForTitleBar(this);
	btnClose->setType(CLOSE);
	btnClose->setFixedSize(16, 16);
	btnClose->setToolTip(QString::fromLocal8Bit("�ر�"));

	btnMin = new ButtonForTitleBar(this);
	btnMin->setType(MIN);
	btnMin->setFixedSize(16, 16);
	btnMin->setToolTip(QString::fromLocal8Bit("��С��"));

	btnMax = new ButtonForTitleBar(this);
	btnMax->setType(FULLSCREEN);
	btnMax->setFixedSize(16, 16);
	btnMax->setToolTip(QString::fromLocal8Bit("ȫ��"));
}

void TitleBar::SetupEvents()
{
	connect(btnClose, &QPushButton::clicked, [=]() { qApp->exit(); });
	connect(btnMin, &QPushButton::clicked, [=]() { this->parentWidget()->showMinimized(); });
	connect(btnMax, &QPushButton::clicked, [=]()
	{ parentWidget()->isFullScreen() ? parentWidget()->showNormal() : parentWidget()->showFullScreen(); update();
	SendMessage(HWND(this->winId()), WM_LBUTTONUP, NULL, NULL); });

	connect(btnMax, &ButtonForTitleBar::RightButtonCliked, [=](){m_moon = new MOON(this);
	m_moon->move(parentWidget()->mapToGlobal(QPoint(0, 0)).x() + 60, parentWidget()->mapToGlobal(QPoint(0, 0)).y() + 30);
		m_moon->show(); });
}

void TitleBar::SetupEffects()
{
	CustomShadowEffect *bodyShadow = new CustomShadowEffect();
	bodyShadow->setBlurRadius(50.0);
	bodyShadow->setDistance(10.0);
	bodyShadow->setColor(QColor(0, 0, 0, 100));
	setGraphicsEffect(bodyShadow);
}

void TitleBar::paintEvent(QPaintEvent *event)
{
	Q_UNUSED(event);

	QPainter p(this);
	p.setRenderHint(QPainter::Antialiasing, true);
	p.fillRect(this->rect(), QColor(255, 255, 255, 100));
}