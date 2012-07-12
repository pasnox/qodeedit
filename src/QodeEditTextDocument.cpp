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
    //QAbstractTextDocumentLayout::updateBlock ( const QTextBlock & block )
}

QodeEditTextDocument::~QodeEditTextDocument()
{
}

void QodeEditTextDocument::contentsChange( int position, int charsRemoved, int charsAdded )
{
    const bool modified = charsRemoved || charsAdded;
    
    qWarning() << Q_FUNC_INFO << position << charsRemoved << charsAdded;
    
    if ( !modified ) {
        return;
    }
    
    QTextBlock block = findBlock( position );
    const int pos = position -block.position();
    const int length = -charsRemoved +charsAdded;
    const QString changeString = block.text().mid( pos, length );
    QodeEditUserData* data = 0;
    
    Q_ASSERT( block.isValid() );
    
    // update current block
    data = static_cast<QodeEditUserData*>( block.userData() );
    
    if ( !data ) {
        data = new QodeEditUserData;
        block.setUserData( data );
    }
    
    data->modified = true;
    
    qWarning() << "blockInfo1" << block.blockNumber() << block.revision() << data->savedRevision;
    
    // update new inserted block
    if ( changeString.length() == 0 && length == 1 ) {
        block = block.next();
        data = static_cast<QodeEditUserData*>( block.userData() );
        
        if ( !data ) {
            data = new QodeEditUserData;
            block.setUserData( data );
        }
        
        data->modified = true;
        
        qWarning() << "blockInfo2" << block.blockNumber() << block.revision() << data->savedRevision;
    }
}

void QodeEditTextDocument::modificationChanged( bool changed )
{
    qWarning() << Q_FUNC_INFO << changed;
    
    if ( changed ) {
        return;
    }
    
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
