/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.1 (1.9.0.1)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com> and The QodeEdit development team
** Project   : QodeEdit
** FileName  : CodeEditor.h
** Date      : 2012-09-02T23:04:46
** License   : LGPL3
** Comment   : A source code component editor based on QPlainTextEdit/QTextDocument/QSyntaxHighlighter and Kate xml language definition files.
** Home Page : https://github.com/pasnox/qodeedit
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QPlainTextEdit>

#include "QodeEdit.h"

class CodeEditorPrivate;
class TextDocument;
class MarginStacker;

class CodeEditor : public QPlainTextEdit
{
    Q_OBJECT
    Q_ENUMS(IndentationPolicy)
    friend class CodeEditorPrivate;
    friend class MarginStacker;
    friend class MarginStackerPrivate;

public:
    CodeEditor( QWidget* parent = 0 );
    virtual ~CodeEditor();

    enum IndentationPolicy {
        UseTabs,
        UseSpaces
    };
    
    TextDocument* textDocument() const;
    void setTextDocument( TextDocument* document );
    
    MarginStacker* marginStacker() const;
    void setMarginStacker( MarginStacker* marginStacker );
    
    QString text() const;
    QString text(int line) const;

    CodeEditor::IndentationPolicy indentationPolicy();
    int indentationWidth();

    
    QPoint cursorPosition() const;
    int lines() const;
    int currentLine() const;
    int currentColumn() const;
    QodeEdit::Ruler rulerMode() const;
    int rulerWidth() const;
    
    QBrush paper() const;
    QBrush pen() const;
    QBrush selectionBackground() const;
    QBrush selectionForeground() const;
    QBrush caretLineBackground() const;
    QBrush caretLineForeground() const;
    
    bool hasBookmark( const QTextBlock& block ) const;
    bool hasBookmark( int line ) const;
    
    QRect blockRect( const QTextBlock& block ) const;
    QRect lineRect( int line ) const;

public slots:
    void setText( const QString& text );
    void setText( int line, const QString &text );
    void setInitialText( const QString& text );
    
    void setCursorPosition( const QPoint& pos );
    void setCurrentLine( int line );
    void setCurrentColumn( int column );
    void setRulerMode( QodeEdit::Ruler mode );
    void setRulerWidth( int width );
    
    void setPaper( const QBrush& brush );
    void setPen( const QBrush& brush );
    void setSelectionBackground( const QBrush& brush );
    void setSelectionForeground( const QBrush& brush );
    void setCaretLineBackground( const QBrush& brush );
    void setCaretLineForeground( const QBrush& brush );
    
    void setBookmark( const QTextBlock& block, bool set );
    void setBookmark( int line, bool set );
    void toggleBookmark( const QTextBlock& block );
    void toggleBookmark( int line );

    void indent();
    void unindent();

    void setTabWidth(int size);

    void setIndentationPolicy(CodeEditor::IndentationPolicy policy);
    void setIndentationWidth(int width);

    void insertTab();
    void removeTab();

    void insertLine(int after = -1);
    void removeLine(int line = -1);
    void duplicateLine(int line = -1);

    void expandSelectionToLine();
    void expandSelectionToWord();

    void joinLines();
    void swapLines(int first, int second);
    void swapLineUp();
    void swapLineDown();

protected:
    virtual bool event( QEvent* event );
    virtual void paintEvent( QPaintEvent* event );
    virtual void keyPressEvent(QKeyEvent *event);

private:
    CodeEditorPrivate* d;
};

#endif // CODEEDITOR_H
