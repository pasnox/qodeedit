#include "QodeEditTextDocument.h"

#include <QPlainTextDocumentLayout>

QodeEditTextDocument::QodeEditTextDocument( QObject* parent )
    : QTextDocument( parent )
{
    setDocumentLayout( new QPlainTextDocumentLayout( this ) );
    setDocumentMargin( 0 );
}

QodeEditTextDocument::~QodeEditTextDocument()
{
}
