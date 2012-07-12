#include "QodeEditTextDocument.h"
#include "QodeEditUserData.h"

#include <QPlainTextDocumentLayout>
#include <QTextBlock>
#include <QDebug>

QodeEditTextDocument::QodeEditTextDocument( QObject* parent )
    : QTextDocument( parent )
{
    setDocumentLayout( new QPlainTextDocumentLayout( this ) );
    setDocumentMargin( 0 );
    
    connect( this, SIGNAL( contentsChange( int, int, int ) ), this, SLOT( contentsChange( int, int, int ) ) );
    connect( this, SIGNAL( modificationChanged( bool ) ), this, SLOT( modificationChanged( bool ) ) );
}

QodeEditTextDocument::~QodeEditTextDocument()
{
}

void QodeEditTextDocument::contentsChange( int position, int charsRemoved, int charsAdded )
{
    const bool modified = charsRemoved || charsAdded;
    
    if ( modified != isModified() ) {
        /*qWarning() << "SKIPPING";
        return;*/
    }
    
    if ( modified ) {
        QTextBlock block = findBlock( position );
        QodeEditUserData* data = 0;
        
        Q_ASSERT( block.isValid() );
        
        data = static_cast<QodeEditUserData*>( block.userData() );
        
        if ( !data ) {
            data = new QodeEditUserData;
            block.setUserData( data );
        }
        
        qWarning() << isModified() << block.blockNumber() << block.revision() << data->savedRevision;
        
        data->modified = true;
    }
}

void QodeEditTextDocument::modificationChanged( bool changed )
{
    if ( changed ) {
        return;
    }
    
    qWarning() << "-----------";
    
    QTextBlock block = begin();
    
    while ( block.isValid() ) {
        QodeEditUserData* data = static_cast<QodeEditUserData*>( block.userData() );
        
        if ( data ) {
            data->savedRevision << block.revision();
            data->modified = false;
            qWarning() << "Updated data for line" << block.blockNumber() << block.revision() << data->savedRevision;
        }
        
        block = block.next();
    }
}
