#ifndef QODEEDITTEXTDOCUMENT_H
#define QODEEDITTEXTDOCUMENT_H

#include <QTextDocument>

class QodeEditUserData;

class QodeEditTextDocument : public QTextDocument
{
    Q_OBJECT
    
public:
    QodeEditTextDocument( QObject* parent = 0 );
    virtual ~QodeEditTextDocument();
    
    int lastSavedRevision() const;
    QodeEditUserData* userData( const QTextBlock& block ) const;
    QodeEditUserData* userData( QTextBlock& block ) const;
    
    void synchronizeBlocksRevision();

protected:
    int mLastSavedRevision;
    
protected slots:
    void contentsChange( int position, int charsRemoved, int charsAdded );
    void modificationChanged( bool changed );
};

#endif // QODEEDITTEXTDOCUMENT_H
