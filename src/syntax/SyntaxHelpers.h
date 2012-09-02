/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.1 (1.9.0.1)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com> and The QodeEdit development team
** Project   : QodeEdit
** FileName  : SyntaxHelpers.h
** Date      : 2012-09-02T23:04:46
** License   : LGPL3
** Comment   : A source code component editor based on QPlainTextEdit/QTextDocument/QSyntaxHighlighter and Kate xml language definition files.
** Home Page : https://github.com/pasnox/qodeedit
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
#ifndef SYNTAXHELPERS_H
#define SYNTAXHELPERS_H

#define QE_DECL_SHARED_CLASS( className ) \
    className(); \
    className( const Syntax::className& other ); \
    className( Syntax::className##Data* other ); \
    virtual ~className(); \
    virtual bool operator==( const Syntax::className& other ) const; \
    virtual bool operator!=( const Syntax::className& other ) const; \
    virtual Syntax::className& operator=( const Syntax::className& other );

#define QE_IMPL_SHARED_CLASS( className ) \
    Syntax::className::className() : d( new Syntax::className##Data ) {} \
    Syntax::className::className( const Syntax::className& other ) : d( other.d ) {} \
    Syntax::className::className( Syntax::className##Data* other ) : d( other ) {} \
    bool Syntax::className::operator==( const Syntax::className& other ) const { return d == other.d; } \
    bool Syntax::className::operator!=( const Syntax::className& other ) const { return !operator==( other ); } \
    Syntax::className& Syntax::className::operator=( const Syntax::className& other ) { if ( this != &other && d != other.d ) { d = other.d; } return *this; }

#define QE_IMPL_SHARED_CLASS_WITH_DEFAULT_DESTRUCTOR( className ) \
    Syntax::className::className() : d( new Syntax::className##Data ) {} \
    Syntax::className::className( const Syntax::className& other ) : d( other.d ) {} \
    Syntax::className::className( Syntax::className##Data* other ) : d( other ) {} \
    Syntax::className::~className() {} \
    bool Syntax::className::operator==( const Syntax::className& other ) const { return d == other.d; } \
    bool Syntax::className::operator!=( const Syntax::className& other ) const { return !operator==( other ); } \
    Syntax::className& Syntax::className::operator=( const Syntax::className& other ) { if ( this != &other && d != other.d ) { d = other.d; } return *this; }

#define QE_IMPL_HERITED_SHARED_CLASS( className, heritsClassName ) \
    Syntax::className::className() : Syntax::heritsClassName(), d( new Syntax::className##Data ) {} \
    Syntax::className::className( const Syntax::className& other ) : Syntax::heritsClassName( other.d ) {} \
    Syntax::className::className( Syntax::className##Data* other ) : Syntax::heritsClassName( other ) {} \
    bool Syntax::className::operator==( const Syntax::className& other ) const { return d == other.d; } \
    bool Syntax::className::operator!=( const Syntax::className& other ) const { return !operator==( other ); } \
    Syntax::className& Syntax::className::operator=( const Syntax::className& other ) { if ( this != &other && d != other.d ) { d = other.d; } return *this; }

#define QE_IMPL_HERITED_SHARED_CLASS_WITH_DEFAULT_DESTRUCTOR( className, heritsClassName ) \
    Syntax::className::className() : Syntax::heritsClassName( new Syntax::className##Data ) {} \
    Syntax::className::className( const Syntax::className& other ) : Syntax::heritsClassName( other ) {} \
    Syntax::className::className( Syntax::className##Data* other ) : Syntax::heritsClassName( other ) {} \
    Syntax::className::~className() {} \
    bool Syntax::className::operator==( const Syntax::className& other ) const { return d == other.d; } \
    bool Syntax::className::operator!=( const Syntax::className& other ) const { return !operator==( other ); } \
    Syntax::className& Syntax::className::operator=( const Syntax::className& other ) { if ( this != &other && d != other.d ) { d = other.d; } return *this; }

#define QE_DECL_MEMBER( type, name ) \
    const type& name() const; \
    type& name();

#define QE_IMPL_MEMBER( type, name, className ) \
    const type& Syntax::className::name() const { return static_cast<Syntax::className##Data*>( d.data() )->name; } \
    type& Syntax::className::name() { return static_cast<Syntax::className##Data*>( d.data() )->name; }

#define QE_OTHER_INIT( name ) name( other.name )

#endif // SYNTAXHELPERS_H
