#include "PlainTextDocumentLayout.h"
#include "TextDocument.h"

PlainTextDocumentLayout::PlainTextDocumentLayout( TextDocument* document )
    : QPlainTextDocumentLayout( document )
{
}

PlainTextDocumentLayout::~PlainTextDocumentLayout()
{
}
