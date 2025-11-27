#ifndef _EDITOR_H_
#define _EDITOR_H_

#include <QObject>
#include <QWidget>
#include <QFile>
#include <QFileInfo>
#include <QPlainTextEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QToolBar>
#include <QMessageBox>
#include <QDebug>
#include <QPainter>
#include <QPushButton>
#include <QTextBlock>
#include <QTextFormat>
#include <QDialog>
#include <QFileDialog>


class LineNumberArea;

class EditArea : public QPlainTextEdit {
    Q_OBJECT
public:
    EditArea(QWidget * parent = nullptr):QPlainTextEdit(parent){};
    ~EditArea(){};

    void set_linenumber_widget(LineNumberArea * linenumber){
        line_number_ = linenumber;
    }

    void hightlightCurrentLine(){
        qDebug()<<">>>>>>> hight light line";
        QList<QTextEdit::ExtraSelection> selections;
        if(!isReadOnly()){
            QTextEdit::ExtraSelection selection;
            selection.format.setBackground(QColor("#1a1a1aff"));
            // //   // 关键设置：禁用透明度混合
            // selection.format.setProperty(QTextFormat::BackgroundBrush,
            //                        QBrush(QColor("#8b2626ff"), Qt::SolidPattern));
            selection.format.setProperty(QTextFormat::FullWidthSelection,true);
            // selection.format.setProperty(QTextFormat::, 1000); // 最高渲染层级

            auto cursor = textCursor();
            cursor.clearSelection();
            selection.cursor = cursor;

            selections.append(selection);
        }

        this->setExtraSelections(selections);
        QTextCharFormat cf(this->currentCharFormat());
        debugBrushSettings(cf);
    }

    void debugBrushSettings(const QTextCharFormat& format) {
        qDebug() << "Background brush properties:";

        if (format.hasProperty(QTextFormat::BackgroundBrush)) {
            QBrush brush = format.background();
            qDebug() << "  Style:" << brush.style();
            qDebug() << "  Color:" << brush.color().name(QColor::HexArgb);
            qDebug() << "  Is opaque:" << brush.isOpaque();
        } else {
            qDebug() << "  No background brush set";
        }

        if (format.hasProperty(QTextFormat::FullWidthSelection)) {
            qDebug() << "  FullWidthSelection:" << format.boolProperty(QTextFormat::FullWidthSelection);
        }
    }

    void paintLineNumber(){

        QFont font = this->font();
        QFontMetrics fm(font);
        int line_height = fm.height();
        int top = viewport()->geometry().top();
        QTextDocument *doc =  document();
        qDebug()<<"block count:"<< doc->blockCount();
        // block.is
        // QTextBlock block = doc->firstBlock();
        QTextBlock block = firstVisibleBlock();

        if(line_number_){

            QPainter painter((QWidget*)line_number_);

            while(block.isValid()){
                // qDebug()<<"block:"<<block.text()<< "block number:"<<block.blockNumber()<<geometry();
                QString linenumber =QString::number(block.blockNumber());
                painter.drawText(0,top,fm.width(linenumber),line_height,Qt::AlignRight,linenumber);
                int block_height = blockBoundingRect(block).height();
                top += block_height;
                block = block.next();

            }

        }
        int last_block_number = doc->lastBlock().blockNumber();
        int last_block_number_width = fm.width(QString::number(last_block_number));
        emit updateLineNumberWidth(last_block_number_width);
    }


protected:
    void paintEvent(QPaintEvent *e) override{

        qDebug()<<"EditArea Paint";

        QPlainTextEdit::paintEvent(e);
    }

signals:
    void updateLineNumberWidth(int w);

private:
    LineNumberArea * line_number_{nullptr};

};

class LineNumberArea : public QWidget {
    Q_OBJECT
public:
    LineNumberArea(QWidget * parent = nullptr):QWidget(parent){
        setAttribute(Qt::WA_StyledBackground);
        this->setAutoFillBackground(true);
    }
    ~LineNumberArea(){

    }

    void resizeEvent(QResizeEvent *event) {
        QWidget::resizeEvent(event);
        qDebug()<<"LineNumberArea resize:"<<contentsRect();
        QRect cr = contentsRect();
    }
    //  QSize sizeHint() const override {
    //     return QSize(30, 100);
    // }
    void paintEvent(QPaintEvent *event) override {
        // 绘制父控件背景
        // QPainter painter(this);
        // painter.fillRect(rect(), QColor("#3498db"));

        // painter.drawText(0,20,"H");
        if(edit_){
            edit_->paintLineNumber();
        }
        // 重要：不要调用基类paintEvent
        // 否则会覆盖子控件背景
    }




    void showEvent(QShowEvent *event) {
        qDebug() << "CustomWidget shown";
        qDebug() << "Geometry:" << geometry();
        qDebug() << "Visible:" << isVisible();
        qDebug() << "Parent:" << parentWidget();
        qDebug() << "Size:" << size();
        QWidget::showEvent(event);
    }

    void set_edit(EditArea * edit) {
        edit_ = edit;
    }

private:
    EditArea * edit_{nullptr};
};

#define DEFAULT_LINE_NUMBER_WIDTH 30

class Editor : public QWidget {
    Q_OBJECT
public:
    explicit Editor(QWidget * parent = nullptr);
    Editor(const QString&file,QWidget*parent = nullptr);
    ~Editor();

    void resizeEvent(QResizeEvent *event);
    void updateRect();


private:
    QVBoxLayout main_layout_;
    QHBoxLayout edit_layout_;
    EditArea edit_;
    QToolBar toolbar_;
    QString file_;

    LineNumberArea line_number_;

    int toolbar_height_{30};
    int line_number_width_{DEFAULT_LINE_NUMBER_WIDTH};
};

#endif // _EDITOR_H_
