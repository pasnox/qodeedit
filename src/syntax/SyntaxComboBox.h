#ifndef SYNTAXCOMBOBOX_H
#define SYNTAXCOMBOBOX_H

#include <QComboBox>

namespace Syntax {

class ComboBox : public QComboBox
{
    Q_OBJECT
    
public:
    ComboBox( QWidget* parent = 0 );
    virtual ~ComboBox();
    
    QString currentSyntax() const;

public slots:
    void setCurrentSyntax( const QString& name );
};

}; // Syntax

#endif // SYNTAXCOMBOBOX_H
