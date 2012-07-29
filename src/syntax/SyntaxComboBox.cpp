#include "SyntaxComboBox.h"
#include "SyntaxFactory.h"
#include "SyntaxModel.h"

Syntax::ComboBox::ComboBox( QWidget* parent )
    : QComboBox( parent )
{
    setModel( Syntax::Factory::model( this ) );
}

Syntax::ComboBox::~ComboBox()
{
}

QString Syntax::ComboBox::currentSyntax() const
{
    return itemData( currentIndex(), Syntax::Model::InternalName ).toString();
}

void Syntax::ComboBox::setCurrentSyntax( const QString& name )
{
    setCurrentIndex( findData( name, Syntax::Model::InternalName ) );
}
