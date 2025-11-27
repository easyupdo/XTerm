#include "editor.h"

Editor::Editor(QWidget * parent):QWidget(parent){

}


void Editor::updateRect(){
    QRect cr = contentsRect();
    toolbar_.setGeometry(QRect(0, 0, cr.width(), toolbar_height_));

    int new_linenumber_width = 0;
    if(line_number_width_<=DEFAULT_LINE_NUMBER_WIDTH){
        new_linenumber_width = DEFAULT_LINE_NUMBER_WIDTH;
    }else {
        new_linenumber_width = line_number_width_;
    }
    line_number_.setGeometry(QRect(0, toolbar_height_, new_linenumber_width, cr.height()));
    edit_.setGeometry(QRect(new_linenumber_width,toolbar_height_,cr.width()-new_linenumber_width,cr.height()-toolbar_height_));
}

void Editor::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    qDebug()<<"resize:"<<contentsRect();
    updateRect();
}


Editor::Editor(const QString&file,QWidget*parent):file_(file) {
    setMinimumSize(QSize(800, 600));
    connect(&edit_,&QPlainTextEdit::blockCountChanged,this,[&](){
        qDebug()<<"block count changed";
        updateRect();
    });

    connect(&edit_,&QPlainTextEdit::cursorPositionChanged,&edit_,&EditArea::hightlightCurrentLine);

    connect(&edit_,&EditArea::updateLineNumberWidth,[&](int w){
        qDebug()<<"update line width:"<<line_number_width_;
        line_number_width_ = w;
        updateRect();
    });
    toolbar_.setParent(this);
    // line_number_.setParent(this);
    toolbar_.setContentsMargins(0,0,0,0);
    // toolbar_.setStyleSheet("border: 2px solid red;");

    line_number_.setParent(this);
    line_number_.setStyleSheet("background-color: lightgrey;");

    edit_.setParent(this);
    // edit_.setStyleSheet("border: 2px solid blue;");

    line_number_.set_edit(&edit_);
    edit_.set_linenumber_widget(&line_number_);
    edit_.hightlightCurrentLine();
    connect(&edit_,&QPlainTextEdit::updateRequest,this,[&](const QRect&r,int dy){
        qDebug()<<"RECT:"<<r<<" dy:"<<dy;
        QWidget * w = (QWidget*)&line_number_;
        w->update();
    });




    main_layout_.setContentsMargins(0, 0, 0, 0);
    main_layout_.setSpacing(0);


    edit_layout_.addWidget(&line_number_);
    edit_layout_.addWidget(&edit_);



    edit_layout_.setContentsMargins(30,0,0,0);

    QAction * newa = toolbar_.addAction("Open");
    connect(newa,&QAction::triggered,this,[&](){
        QString filename =  QFileDialog::getOpenFileName();
        qDebug()<<">>>>>> filename:"<<filename;
        QFile f(filename);
        if(f.open(QIODevice::ReadWrite)){
            edit_.setPlainText(f.readAll());
        }
    });

    QAction * save = toolbar_.addAction("Save");
    save->setShortcut(QKeySequence::Save);


    connect(save,&QAction::triggered,this,[&](){
        QString text = edit_.toPlainText();
        QFile f(file_);
        if(f.open(QIODevice::WriteOnly)){
            qint32 r_size =  f.write(text.toLatin1());
            if(r_size > 0){
                QMessageBox::information(this,"save","saved!");
            }
        }
        f.flush();
        f.close();
    });

    // main_layout_.addWidget(&toolbar_);
    // main_layout_.addLayout(&edit_layout_);

    // main_layout_.addWidget(new QPushButton("OK"));
    // this->setLayout(&main_layout_);

    QFile f(file);
    if(f.open(QIODevice::ReadOnly)) {
        edit_.setPlainText(f.readAll());
    }
    f.flush();
    f.close();

    this->setGeometry(100,10,30,60);


}

Editor::~Editor(){

}

