#include "QodeEditTextDocument.h"
#include "QodeEditUserData.h"

#include <QPlainTextDocumentLayout>
#include <QTextBlock>
#include <QDebug>

QodeEditTextDocument::QodeEditTextDocument( QObject* parent )
    : QTextDocument( parent )
{
    mLastSavedRevision = 0;
    
    setDocumentLayout( new QPlainTextDocumentLayout( this ) );
    setDocumentMargin( 0 );
    
    connect( this, SIGNAL( modificationChanged( bool ) ), this, SLOT( modificationChanged( bool ) ) );
    connect( this, SIGNAL( contentsChange( int, int, int ) ), this, SLOT( contentsChange( int, int, int ) ) );
}

QodeEditTextDocument::~QodeEditTextDocument()
{
}

int QodeEditTextDocument::lastSavedRevision() const
{
    return mLastSavedRevision;
}

void QodeEditTextDocument::synchronizeBlocksRevision()
{
    mLastSavedRevision = revision();
    QTextBlock block = begin();
    
    while ( block.isValid() ) {
        block.setRevision( mLastSavedRevision );
        block = block.next();
    }
}

void QodeEditTextDocument::contentsChange( int position, int charsRemoved, int charsAdded )
{
    const bool modified = charsRemoved || charsAdded;
    
    if ( !modified ) {
        return;
    }
    
    QTextBlock block = findBlock( position );

    if ( block.isValid() ) {
        if ( block.revision() < 0 ) {
            block.setRevision( -block.revision() -1 );
        }
    }
}

void QodeEditTextDocument::modificationChanged( bool changed )
{
    if ( changed ) {
        return;
    }

    const int oldLastSavedRevision = mLastSavedRevision;
    mLastSavedRevision = revision();

    if ( oldLastSavedRevision != mLastSavedRevision ) {
        QTextBlock block = begin();
        
        while ( block.isValid() ) {
            if ( block.revision() < 0 || block.revision() != oldLastSavedRevision ) {
                block.setRevision( -mLastSavedRevision -1 );
            }
            else {
                block.setRevision( mLastSavedRevision );
            }
            
            block = block.next();
        }
    }
}
