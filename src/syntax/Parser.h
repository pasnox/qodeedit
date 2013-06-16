/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.1 (1.9.0.1)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com> and The QodeEdit development team
** Project   : QodeEdit
** FileName  : Parser.h
** Date      : 2012-09-02T23:04:46
** License   : LGPL3
** Comment   : A source code component editor based on QPlainTextEdit/QTextDocument/QSyntaxHighlighter and Kate xml language definition files.
** Home Page : https://github.com/pasnox/qodeedit
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
#ifndef PARSER_H
#define PARSER_H

#include <QXmlSimpleReader>
#include <QXmlDefaultHandler>

namespace Syntax {

class Document;
class ParserPrivate;

class Reader : public QXmlSimpleReader
{
public:
    bool parse( Syntax::Document* document, const QXmlInputSource& input );
};

class Parser : public QXmlDefaultHandler
{
    friend class Syntax::Reader;

public:
    Parser();
    virtual ~Parser();

    virtual bool attributeDecl( const QString& eName, const QString& aName, const QString& type, const QString& valueDefault, const QString& value );
    virtual bool comment( const QString& ch );
    virtual bool endCDATA();
    virtual bool endDTD();
    virtual bool fatalError( const QXmlParseException& exception );
    virtual bool characters( const QString& ch );
    virtual bool startDocument();
    virtual bool endDocument();
    virtual bool startElement( const QString& namespaceURI, const QString& localName, const QString& qName, const QXmlAttributes& atts );
    virtual bool endElement( const QString& namespaceURI, const QString& localName, const QString& qName );
    virtual bool endEntity( const QString& name );
    virtual bool endPrefixMapping( const QString& prefix );
    virtual bool error( const QXmlParseException& exception );
    virtual QString errorString() const;
    virtual bool externalEntityDecl( const QString& name, const QString& publicId, const QString& systemId );
    virtual bool ignorableWhitespace( const QString& ch );
    virtual bool internalEntityDecl( const QString& name, const QString& value );
    virtual bool notationDecl( const QString& name, const QString& publicId, const QString& systemId );
    virtual bool processingInstruction( const QString& target, const QString& data );
    virtual bool resolveEntity( const QString& publicId, const QString& systemId, QXmlInputSource*& ret );
    virtual void setDocumentLocator( QXmlLocator* locator );
    virtual bool skippedEntity( const QString& name );
    virtual bool startCDATA();
    virtual bool startDTD( const QString& name, const QString& publicId, const QString& systemId );
    virtual bool startEntity( const QString& name );
    virtual bool startPrefixMapping( const QString& prefix, const QString& uri );
    virtual bool unparsedEntityDecl( const QString& name, const QString& publicId, const QString& systemId, const QString& notationName );
    virtual bool warning( const QXmlParseException& exception );

#if !defined( QT_NO_DEBUG )
    void debug() const;
#endif

private:
    ParserPrivate* d;
};

} // Syntax

#endif // PARSER_H
