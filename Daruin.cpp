#include "Daruin.h"
#include <QTextEdit>

Daruin::Daruin(void)
{
	text = new QTextEdit;

	setCentralWidget(text);
}
