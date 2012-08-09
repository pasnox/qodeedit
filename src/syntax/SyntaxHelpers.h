#ifndef SYNTAXHELPERS_H
#define SYNTAXHELPERS_H

#define SYNTAX_OPERATORS( className ) \
    virtual bool operator==( const Syntax::className& other ) const { return d == other.d; } \
    virtual bool operator!=( const Syntax::className& other ) const { return !operator==( other ); }

#define SYNTAX_OTHER_INIT( name ) name( other.name )
#define SYNTAX_D_INIT( name ) name( d->name )
#define SYNTAX_D_COPY( name ) name = d->name

#endif // SYNTAXHELPERS_H
