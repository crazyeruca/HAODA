#include "stdafx.h"
#include "OverlayWidget.h"

OverlayWidget::OverlayWidget(QWidget *parent)
	: QWidget(parent)
{
	if (parent)
	{
		parent->installEventFilter(this);
	}
}

OverlayWidget::~OverlayWidget()
{
}

bool OverlayWidget::event(QEvent* event)
{
	if (!parent())
	{
		return QWidget::event(event);
	}
	switch (event->type())
	{
	case QEvent::ParentChange:
	{
		parent()->installEventFilter(this);
		setGeometry(overlayGeometry());
		break;
	}
	case QEvent::ParentAboutToChange:
	{
		parent()->removeEventFilter(this);
		break;
	}
	default:
		break;
	}
	return QWidget::event(event);
}
bool OverlayWidget::eventFilter(QObject* obj, QEvent* event)
{
	switch (event->type())
	{
		//will fix 
	case QEvent::Move:
	case QEvent::Resize:
		setGeometry(overlayGeometry());
		break;
	default:
		break;
	}
	return QWidget::eventFilter(obj, event);
}
QRect OverlayWidget::overlayGeometry() const
{
	QWidget* widget = parentWidget();
	if (!widget)
	{
		return QRect();
	}
	return widget->rect();
}
