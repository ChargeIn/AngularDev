#include "codeeditor.h"

#include <QPainter>

CodeEditor::CodeEditor(QFile *file, QWidget *parent)
    : QWidget{parent}, win{0,0,0, 8}
{
    // styles
    setAttribute(Qt::WA_StyledBackground, true);
    setStyleSheet("background-color: #181818; font-size: 12px; font-weight: 500; color: #bbbbbb");

    QFont mono = QFont("Monospace");
    mono.setFixedPitch(true);
    mono.setStyleHint(QFont::Monospace);
    setFont(mono); // terminal is based on monospace fonts
    win.lineheight = fontMetrics().lineSpacing();

    if(file != nullptr){
        openFile(file);
    } else {
        addLine();
    }

    text = new FormattedText();
}

void CodeEditor::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    double yPos = win.lineheight;
    int count = 0;

    for(int i = 0; i < text->blockCount; i++){
        FormattedBlock* block = &text->blocks[i];
        for(int j = 0; j < block->size; j++){
            FormattedLine* line = &block->lines[j];

            painter.drawText(QPointF(10, yPos), QString::number(count));
            painter.drawText(QPointF(40, yPos), *line->rawText);

            yPos+= win.lineheight;
            count++;
        }
        painter.drawText(QPointF(70, yPos - win.lineheight), "------");
    }

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


void CodeEditor::openFile(QFile* file){

}


void CodeEditor::keyPressEvent(QKeyEvent *event)
{
    if((event->key() == Qt::Key_Enter) || (event->key() == Qt::Key_Return)){
        text->addLine();
    } else if(event->key() == Qt::Key_Backspace){
        if(event->modifiers().testFlag(Qt::KeyboardModifier::ControlModifier)){
            text->removeLastWord();
        } else {
            text->removeLastChar();
        }
    } else if(event->text() != "") {
        text->writeText(event->text());
    }

    update();
}

void CodeEditor::resizeEvent(QResizeEvent *event)
{
}

void CodeEditor::wheelEvent(QWheelEvent *event)
{

}

void CodeEditor::focusOutEvent(QFocusEvent *event)
{

}

void CodeEditor::mousePressEvent(QMouseEvent *event)
{
    setFocus();
}

void CodeEditor::mouseDoubleClickEvent(QMouseEvent *event)
{

}

void CodeEditor::mouseReleaseEvent(QMouseEvent *event)
{

}

void CodeEditor::mouseMoveEvent(QMouseEvent *event)
{

}

// --------------------------- Editor Functions ----------------------------
void CodeEditor::addLine() {

}
