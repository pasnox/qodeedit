#ifndef SYNTAXHELPERS_H
#define SYNTAXHELPERS_H

#define SYNTAX_DECL_MEMBER( type, name ) \
    const type& name() const; \
    type& name()

#define SYNTAX_IMPL_MEMBER( type, name, className ) \
    const type& Syntax::className::name() const { return d->name; } \
    type& Syntax::className::name() { return d->name; }

#define SYNTAX_OTHER_INIT( name ) name( other.name )

#define SYNTAX_DECL_OPERATORS( className ) \
    virtual bool operator==( const Syntax::className& other ) const; \
    virtual bool operator!=( const Syntax::className& other ) const; \
    virtual Syntax::className& operator=( const Syntax::className& other )

#define SYNTAX_IMPL_OPERATORS( className ) \
    bool Syntax::className::operator==( const Syntax::className& other ) const { return d == other.d; } \
    bool Syntax::className::operator!=( const Syntax::className& other ) const { return !operator==( other ); } \
    Syntax::className& Syntax::className::operator=( const Syntax::className& other ) { if ( this != &other ) { d = other.d; } return *this; }

#endif // SYNTAXHELPERS_H
