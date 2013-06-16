/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.1 (1.9.0.1)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com> and The QodeEdit development team
** Project   : QodeEdit
** FileName  : Helpers.h
** Date      : 2012-09-02T23:04:46
** License   : LGPL3
** Comment   : A source code component editor based on QPlainTextEdit/QTextDocument/QSyntaxHighlighter and Kate xml language definition files.
** Home Page : https://github.com/pasnox/qodeedit
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
#ifndef HELPERS_H
#define HELPERS_H

#include <QExplicitlySharedDataPointer>

#define QE_DECL_SHARED_CLASS( className, nameSpace ) \
    className(); \
    className( const nameSpace::className& other ); \
    className( nameSpace::className##Data* other ); \
    virtual ~className(); \
    virtual bool operator==( const nameSpace::className& other ) const; \
    virtual bool operator!=( const nameSpace::className& other ) const; \
    virtual nameSpace::className& operator=( const nameSpace::className& other )

#define QE_IMPL_SHARED_CLASS( className, nameSpace ) \
    nameSpace::className::className() : d( new nameSpace::className##Data ) {} \
    nameSpace::className::className( const nameSpace::className& other ) : d( other.d ) {} \
    nameSpace::className::className( nameSpace::className##Data* other ) : d( other ) {} \
    bool nameSpace::className::operator==( const nameSpace::className& other ) const { return d == other.d; } \
    bool nameSpace::className::operator!=( const nameSpace::className& other ) const { return !operator==( other ); } \
    nameSpace::className& nameSpace::className::operator=( const nameSpace::className& other ) { if ( this != &other && d != other.d ) { d = other.d; } return *this; }

#define QE_IMPL_SHARED_CLASS_WITH_DEFAULT_DESTRUCTOR( className, nameSpace ) \
    nameSpace::className::className() : d( new nameSpace::className##Data ) {} \
    nameSpace::className::className( const nameSpace::className& other ) : d( other.d ) {} \
    nameSpace::className::className( nameSpace::className##Data* other ) : d( other ) {} \
    nameSpace::className::~className() {} \
    bool nameSpace::className::operator==( const nameSpace::className& other ) const { return d == other.d; } \
    bool nameSpace::className::operator!=( const nameSpace::className& other ) const { return !operator==( other ); } \
    nameSpace::className& nameSpace::className::operator=( const nameSpace::className& other ) { if ( this != &other && d != other.d ) { d = other.d; } return *this; }

#define QE_IMPL_HERITED_SHARED_CLASS( className, heritsClassName, nameSpace ) \
    nameSpace::className::className() : nameSpace::heritsClassName(), d( new nameSpace::className##Data ) {} \
    nameSpace::className::className( const nameSpace::className& other ) : nameSpace::heritsClassName( other.d ) {} \
    nameSpace::className::className( nameSpace::className##Data* other ) : nameSpace::heritsClassName( other ) {} \
    bool nameSpace::className::operator==( const nameSpace::className& other ) const { return d == other.d; } \
    bool nameSpace::className::operator!=( const nameSpace::className& other ) const { return !operator==( other ); } \
    nameSpace::className& nameSpace::className::operator=( const nameSpace::className& other ) { if ( this != &other && d != other.d ) { d = other.d; } return *this; }

#define QE_IMPL_HERITED_SHARED_CLASS_WITH_DEFAULT_DESTRUCTOR( className, heritsClassName, nameSpace ) \
    nameSpace::className::className() : nameSpace::heritsClassName( new nameSpace::className##Data ) {} \
    nameSpace::className::className( const nameSpace::className& other ) : nameSpace::heritsClassName( other ) {} \
    nameSpace::className::className( nameSpace::className##Data* other ) : nameSpace::heritsClassName( other ) {} \
    nameSpace::className::~className() {} \
    bool nameSpace::className::operator==( const nameSpace::className& other ) const { return d == other.d; } \
    bool nameSpace::className::operator!=( const nameSpace::className& other ) const { return !operator==( other ); } \
    nameSpace::className& nameSpace::className::operator=( const nameSpace::className& other ) { if ( this != &other && d != other.d ) { d = other.d; } return *this; }

#define QE_DECL_MEMBER( type, name ) \
    const type& name() const; \
    type& name()

#define QE_IMPL_MEMBER( type, name, className, nameSpace ) \
    const type& nameSpace::className::name() const { return static_cast<nameSpace::className##Data*>( d.data() )->name; } \
    type& nameSpace::className::name() { return static_cast<nameSpace::className##Data*>( d.data() )->name; }

#define QE_OTHER_INIT( name ) name( other.name )

#endif // HELPERS_H
