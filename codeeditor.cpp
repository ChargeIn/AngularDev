#include "codeeditor.h"

#include <QPainter>

#include "parser/angular/angularformatter.h"
#include "parser/angular/typescript/lexer.h"
#include "formatter.h"

#include <string>

CodeEditor::CodeEditor(QFile *file, QWidget *parent)
        : QWidget{parent}, win{0, 0, 0, 8.5, 10, 40} {
    // styles
    setAttribute(Qt::WA_StyledBackground, true);
    setStyleSheet("background: #1b1b22; font-size: 14px; font-weight: 500; color: #bbbbbb");

    QFont mono = QFont("Monospace");
    mono.setFixedPitch(true);
    mono.setStyleHint(QFont::Monospace);
    setFont(mono); // terminal is based on monospace fonts
    win.lineheight = fontMetrics().lineSpacing();

    if (file != nullptr) {
        openFile(file);
    }

    formatter = new AngularFormatter();
    text = new FormattedText(formatter);
}

CodeEditor::~CodeEditor() {
    delete text;
    delete formatter;
}

void CodeEditor::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    double yPos = win.lineheight;
    int count = 0;
    double offset = win.textOffset;

    int bgColor = -1;
    int fgColor = -1;

    QString currentLine = QString();

    bool changed = false;

    for (int i = 0; i < text->blockCount; i++) {
        FormattedBlock *block = &text->blocks[i];
        for (int j = 0; j < block->size; j++) {
            FormattedLine *line = &block->lines[j];

            for (int j = 0; j < line->size; j++) {
                FormattedString str = line->strings[j];

                if (str.fg != fgColor) {
                    fgColor = str.fg;
                    changed = true;
                }

                if (str.bg != bgColor) {
                    bgColor = str.bg;
                    changed = true;
                }

                if (changed) {
                    changed = false;
                    painter.drawText(QPointF(offset, yPos), currentLine);
                    offset += currentLine.length() * win.charWidth;
                    currentLine = "";

                    // update painter to new color
                    painter.setPen(colors[fgColor]);
                    painter.setBackground(QBrush(colors[bgColor]));
                }

                currentLine += str.text;
            }
            painter.drawText(QPointF(offset, yPos), currentLine);
            currentLine = "";
            yPos += win.lineheight;
            offset = win.textOffset;
            count++;
        }
        painter.drawText(QPointF(500, yPos - win.lineheight), "------");
    }
    // draw line number
    painter.setPen(numberLine);
    painter.drawLine(win.textOffset - 10, 0, win.textOffset - 10, event->rect().height());

    yPos = win.lineheight;
    painter.setPen(colors[1]);
    painter.setBackground(QBrush(colors[0]));
    for (int i = 0; i < count; i++) {
        painter.drawText(QPointF(win.numberOffset, yPos), QString::number(i));
        yPos += win.lineheight;
    }


    // draw cursor
    double cursorY = 0, cursorX = 0;
    for (int i = 0; i < text->cursor.block; i++) {
        cursorY += text->blocks[i].size * win.lineheight;
    }

    cursorY += (text->cursor.line + 1) * win.lineheight;
    cursorX = win.textOffset + text->cursor.character * win.charWidth;

    painter.setBackgroundMode(Qt::TransparentMode);
    painter.drawText(QPointF(cursorX, cursorY), cursorChar);

    /** QPainter painter(this);
     painter.setBackgroundMode(Qt::BGMode::OpaqueMode);

     int bgColor = -1;
     int fgColor = -1;
     double offset = 0;
     double yPos = win.lineheight;
     bool changed = false;
     QString text = "";

     for(int i = 0; i < win.lastline; i++){
         FormattedLine line = lines[i];

         for(int j = 0; j < line.size; j++){
             FormattedString str = line.parts[j];

             if(str.fg != fgColor){
                 fgColor = str.fg;
                 painter.setPen(colors[fgColor]);
                 changed = true;
             }

             if(str.bg != bgColor){
                 bgColor = str.bg;
                 painter.setBackground(QBrush(colors[bgColor]));
                 changed = true;
             }

             if(changed){
                 changed = false;
                 painter.drawText(QPointF(offset, yPos), text);
                 offset += text.size()*win.charWidth;
                 text = "";
             }

             text += str.text;
         }
         painter.drawText(QPointF(offset, yPos), text);
         offset = 0;
         yPos += win.lineheight;
     }*/
}


void CodeEditor::openFile(QFile *file) {

}


void CodeEditor::keyPressEvent(QKeyEvent *event) {
    if ((event->key() == Qt::Key_Enter) || (event->key() == Qt::Key_Return)) {
        text->addLine();
    } else if (event->key() == Qt::Key_Backspace) {
        if (event->modifiers().testFlag(Qt::KeyboardModifier::ControlModifier)) {
            text->removeLastWord();
        } else {
            text->removeLastChar();
        }
    } else if (event->key() == Qt::Key_Left) {
        text->moveLeft();
    } else if (event->key() == Qt::Key_Right) {
        text->moveRight();
    } else if (event->key() == Qt::Key_Up) {
        text->moveUp();
    } else if (event->key() == Qt::Key_Down) {
        text->moveDown();
    } else if (event->text() != "") {
        text->writeText(event->text());
    }

    update();
}

void CodeEditor::resizeEvent(QResizeEvent *event) {
}

void CodeEditor::wheelEvent(QWheelEvent *event) {

}

void CodeEditor::focusOutEvent(QFocusEvent *event) {

}

void CodeEditor::mousePressEvent(QMouseEvent *event) {
    setFocus();
}

void CodeEditor::mouseDoubleClickEvent(QMouseEvent *event) {

}

void CodeEditor::mouseReleaseEvent(QMouseEvent *event) {

}

void CodeEditor::mouseMoveEvent(QMouseEvent *event) {

}

// --------------------------- Editor Functions ----------------------------

