#include "labelmainwindow.h"
#include "ui_labelmainwindow.h"
#include "MyLabel/dcm2image.h"
#include <iostream>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QScrollBar>


LabelMainWindow::LabelMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LabelMainWindow)
{
    ui->setupUi(this);

    QIcon  *edit = new QIcon("./Resources/edit.png");
    ui->edit->setIcon(*edit);

    QIcon  *big = new QIcon("./Resources/big.png");
    ui->big->setIcon(*big);

    QIcon  *small = new QIcon("./Resources/small.png");
    ui->small->setIcon(*small);

    QIcon  *save = new QIcon("./Resources/save.png");
    ui->save->setIcon(*save);


    _initFocusLabel();

    this->setWindowState(Qt::WindowMaximized);
    //m_mainAccountWindow = new MainAccountWindow();

    m_add = new QAction("add", this);
 //   m_delete = new QAction("delete", this);

    ui->focuslabel->setItemsExpandable(false);
    ui->listWidget->setViewMode(QListView::IconMode);
    //设置QListWidget中单元项的图片大小
    //ui->listWidget->setIconSize(QSize(ui->listWidget->width() / 10, ui->listWidget->height() / 2));
    //设置QListWidget中单元项的间距
    ui->listWidget->setSpacing(3);
    m_isNULLImage = true;
    m_isSaved  = false;

    ui->focuslabel->setHorizontalScrollBarPolicy (Qt::ScrollBarAlwaysOn);
    QScrollBar *HBar1 = new QScrollBar;
    ui->focuslabel->setHorizontalScrollBar(HBar1);
    ui->focuslabel -> header() -> setMinimumSectionSize(300);


    connect(ui->listWidget, SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem*)), this, SLOT(showImage(QListWidgetItem*, QListWidgetItem*)));
    connect(ui->donot, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)), this, SLOT(changeNOPatient(QListWidgetItem*, QListWidgetItem*)));
    connect(ui->already, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(changeALPatient(QListWidgetItem*)));
    connect(ui->donot, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(changePatient(QListWidgetItem*)));
    connect(ui->label_8, SIGNAL(changeImageSize(float)), this, SLOT(changeSize(float)));
    connect(ui->label_8, SIGNAL(addLabel(int)), this, SLOT(treeAddLabel(int)));
    connect(ui->label_8, SIGNAL(currentLabel(int)), this, SLOT(setcurrentLabel(int)));
    connect(ui->label_8, SIGNAL(removeLabel(int)), this, SLOT(treeRemoveLabel(int)));
    connect(ui->donot, SIGNAL(itemPressed(QListWidgetItem*)), this, SLOT(itemPressedSlot(QListWidgetItem*)));
    connect(m_add,SIGNAL(triggered()), this, SLOT(on_LoadImage()));
   // connect(m_delete,SIGNAL(triggered()), this, SLOT(deletePatient()));
    connect(ui->focuslabel,SIGNAL(itemChanged(QTreeWidgetItem*,int)),this,SLOT(treeItemChanged(QTreeWidgetItem*,int)));

    _loadDir("./json/no", 0);
    _loadDir("./json/yes", 1);
}

LabelMainWindow::~LabelMainWindow()
{

    delete ui;
}

void LabelMainWindow::_loadDir(QString path, int flag)
{
    QDir dir(path);
    foreach(QFileInfo mfi ,dir.entryInfoList())
    {
      if(mfi.isFile())
      {
          QString ID = mfi.absoluteFilePath().section("/", -1).section('.', 0, 0);
          QStringList IDlist;
          m_patientImageList.insert(ID, IDlist);
          _parse(mfi.absoluteFilePath(), ID);
          if(flag == 0)
          {
              for(int i = 0; i < ui->donot->count(); i++)
              {
                  if(ID == ui->donot->item(i)->text())
                  {
                      return;
                  }
              }
              QListWidgetItem* name = new QListWidgetItem(ui->donot);
              name->setText(ID);
			  name->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			  name->setFlags(name->flags() & (~Qt::ItemIsEditable));
             // _createPatient(ID);
          }
          else
          {
              for(int i = 0; i < ui->already->count(); i++)
              {
                  if(ID == ui->already->item(i)->text())
                  {
                      return;
                  }
              }
              QListWidgetItem* name = new QListWidgetItem(ui->already);
              name->setText(ID);
			  name->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			  name->setFlags(name->flags() & (~Qt::ItemIsEditable));
            //  _createPatient(ID);
          }
      }
    }
}

void LabelMainWindow::_parse(QString path, QString ID)
{
    QStringList list = m_patientImageList.value(ID);
    QString val;
    QFile file;
    file.setFileName(path);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();
    QJsonDocument doc = QJsonDocument::fromJson(val.toUtf8());
    if (doc.isObject())
    {
        QJsonObject Tree = doc.object();
        QJsonObject::iterator TreeIt = Tree.begin();
        while(TreeIt != Tree.end())
        {
            list.push_back(TreeIt.key());
            _parseImg(TreeIt.value());
            TreeIt++;
        }

    }
    m_patientImageList[ID] = list;
}

void LabelMainWindow::_parseImg(QJsonValue root)
{

    QJsonObject childObj = root.toObject();
    QString imgName;
    float step;
    int index;
    QVector<QPointF> pointVec;
    QMap<int, QPolygonF> polyPool;
        if(childObj.contains("step"))
        {
            step = childObj.value("step").toDouble();
        }

        if(childObj.contains("index"))
        {
            index = childObj.value("index").toDouble();
        }

        if(childObj.contains("path"))
        {
            imgName = childObj.value("path").toString();
        }

        if(childObj.contains("region"))
        {

            QJsonValue childvalue = childObj.value("region");
            QJsonObject child2Obj = childvalue.toObject();
            QJsonObject::Iterator it;
            for(it = child2Obj.begin(); it != child2Obj.end(); it++)
            {
                QJsonObject child3Obj = it.value().toObject();
                if(child3Obj.contains("name"))
                {
                    QJsonObject child4Obj = child3Obj.value("name").toObject();
                    if(child4Obj.contains(QStringLiteral("结构")))
                    {
                        m_checked.insert(QStringLiteral("结构"), child4Obj.value(QStringLiteral("结构")).toString());
                    }

                    if(child4Obj.contains(QStringLiteral("回声类型")))
                    {

                        m_checked.insert(QStringLiteral("回声类型"), child4Obj.value(QStringLiteral("回声类型")).toString());
                    }

                    if(child4Obj.contains(QStringLiteral("形态")))
                    {

                        m_checked.insert(QStringLiteral("形态"), child4Obj.value(QStringLiteral("形态")).toString());
                    }

                    if(child4Obj.contains(QStringLiteral("边缘")))
                    {

                        m_checked.insert(QStringLiteral("边缘"), child4Obj.value(QStringLiteral("边缘")).toString());
                    }

                    if(child4Obj.contains(QStringLiteral("局灶性强回声")))
                    {

                        m_checked.insert(QStringLiteral("局灶性强回声"), child4Obj.value(QStringLiteral("局灶性强回声")).toString());
                    }

                    if(child4Obj.contains(QStringLiteral("良恶性")))
                    {

                        m_checked.insert(QStringLiteral("良恶性"), child4Obj.value(QStringLiteral("良恶性")).toString());
                    }

                    m_OneLabelChecked.insert(QString::fromStdString(it.key().toStdString()), m_checked);
                    m_checked.clear();
                }

                if(child3Obj.contains("coordinate"))
                {
                    //qDebug() << "coordinate";
                    QJsonValue codvalue = child3Obj.value("coordinate");
                    QJsonObject  codobj = codvalue.toObject();
                    int j = 1;
                    while(j)
                    {
                        if(!codobj.contains(QString::number(j, 10)))
                        {
                            //qDebug() << j;
                            break;
                        }
                        QJsonValue pointValue = codobj.value(QString::number(j, 10));
                        QJsonObject pointObj = pointValue.toObject();

                        pointVec.push_back(QPointF(pointObj.value("x:").toDouble(), pointObj.value("y:").toDouble()));
                        QVector<QPointF> tempVec = pointVec;
                       // qDebug() << tempVec;
                        QPolygonF *poly = new QPolygonF(tempVec);
                        polyPool.insert(it.key().toInt(), *poly);
                        delete poly;
                        j++;

                    }
                    pointVec.clear();
                }
            }

        }


        ImageInfo info;
        info.setFocusInfo(m_OneLabelChecked);
        info.setStep(step);
        info.setPoly(polyPool);
        info.setIndex(index);

        QString dcm = imgName.section(".", -1);
        if(dcm == "dcm")
        {
            QImage *image = new QImage(*Dcm2Image(imgName).getImage());
             m_pixmap = new QPixmap(QPixmap::fromImage(*image));
            delete image;
        }
        else
        {
            m_pixmap = new QPixmap(imgName);
        }

        *m_pixmap = m_pixmap->scaled(1000, 666);
        m_origin = new QPixmap(*m_pixmap);
        info.setOrigin(*m_origin);

        m_imageInfo.insert(imgName.section('/', -1), info);
        m_OneLabelChecked.clear();
}

void LabelMainWindow::_initFocusLabel()
{
   // ui->focuslabel->clear();
    QTreeWidgetItem* name_1 = new QTreeWidgetItem(ui->focuslabel);
    name_1->setText(0,QStringLiteral("结构"));    //树形控件显示的文本信息


    QTreeWidgetItem* name_1_1 = new QTreeWidgetItem(name_1);
    name_1_1->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    name_1_1->setText(0,QStringLiteral("囊性或几乎完全囊性"));  //设置子项显示的文本
    name_1_1->setCheckState(0,Qt::Unchecked); //设置子选项的显示格式和状态

    QTreeWidgetItem* name_1_2 = new QTreeWidgetItem(name_1);
    name_1_2->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    name_1_2->setText(0,QStringLiteral("海绵状"));  //设置子项显示的文本
    name_1_2->setCheckState(0,Qt::Unchecked); //设置子选项的显示格式和状态

    QTreeWidgetItem* name_1_3 = new QTreeWidgetItem(name_1);
    name_1_3->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    name_1_3->setText(0,QStringLiteral("囊实性"));  //设置子项显示的文本
    name_1_3->setCheckState(0,Qt::Unchecked); //设置子选项的显示格式和状态

    QTreeWidgetItem* name_1_4 = new QTreeWidgetItem(name_1);
    name_1_4->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    name_1_4->setText(0,QStringLiteral("实性或几乎完全实性"));  //设置子项显示的文本
    name_1_4->setCheckState(0,Qt::Unchecked); //设置子选项的显示格式和状态

    QTreeWidgetItem* name_2 = new QTreeWidgetItem(ui->focuslabel);
    name_2->setText(0,QStringLiteral("回声类型"));    //树形控件显示的文本信息


    //眼別子项
    QTreeWidgetItem* name_2_1 = new QTreeWidgetItem(name_2);
    name_2_1->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    name_2_1->setText(0,QStringLiteral("无回声"));  //设置子项显示的文本
    name_2_1->setCheckState(0,Qt::Unchecked); //设置子选项的显示格式和状态

    QTreeWidgetItem* name_2_2 = new QTreeWidgetItem(name_2);
    name_2_2->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    name_2_2->setText(0,QStringLiteral("等回声或高回声"));
    name_2_2->setCheckState(0,Qt::Unchecked);

    QTreeWidgetItem* name_2_3 = new QTreeWidgetItem(name_2);
    name_2_3->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    name_2_3->setText(0,QStringLiteral("低回声"));
    name_2_3->setCheckState(0,Qt::Unchecked);

    QTreeWidgetItem* name_2_4 = new QTreeWidgetItem(name_2);
    name_2_4->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    name_2_4->setText(0,QStringLiteral("极低回声"));
    name_2_4->setCheckState(0,Qt::Unchecked);


    QTreeWidgetItem* name_3 = new QTreeWidgetItem(ui->focuslabel);
    name_3->setText(0,QStringLiteral("形态"));

    //name_3子项
    QTreeWidgetItem* name_3_1 = new QTreeWidgetItem(name_3);//指定子项属于哪一个父项
    name_3_1->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    name_3_1 ->setText(0,QStringLiteral("A/T<1"));
    name_3_1 ->setCheckState(0,Qt::Unchecked);

    QTreeWidgetItem* name_3_2 = new QTreeWidgetItem(name_3);
    name_3_2->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    name_3_2->setText(0,QStringLiteral("A/T>1"));
    name_3_2->setCheckState(0,Qt::Unchecked);


    QTreeWidgetItem* name_4 = new QTreeWidgetItem(ui->focuslabel);
    name_4->setText(0,QStringLiteral("边缘"));

    //name_4子项
    QTreeWidgetItem* name_4_1 = new QTreeWidgetItem(name_4);//指定子项属于哪一个父项
    name_4_1->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    name_4_1->setText(0,QStringLiteral("光滑"));
    name_4_1->setCheckState(0,Qt::Unchecked);

    QTreeWidgetItem* name_4_2 = new QTreeWidgetItem(name_4);
    name_4_2->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    name_4_2->setText(0,QStringLiteral("模糊"));
    name_4_2->setCheckState(0,Qt::Unchecked);

    QTreeWidgetItem* name_4_3 = new QTreeWidgetItem(name_4);
    name_4_3->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    name_4_3->setText(0,QStringLiteral("分叶状或不规则"));
    name_4_3->setCheckState(0,Qt::Unchecked);

    QTreeWidgetItem* name_4_4 = new QTreeWidgetItem(name_4);
    name_4_4->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    name_4_4->setText(0,QStringLiteral("向甲状腺外延伸"));
    name_4_4->setCheckState(0,Qt::Unchecked);

    QTreeWidgetItem* name_5 = new QTreeWidgetItem(ui->focuslabel);   //指定子项属于哪一个父项
    name_5->setText(0,QStringLiteral("局灶性强回声"));

    //name_5子项
    QTreeWidgetItem* name_5_1 = new QTreeWidgetItem(name_5);   //指定子项属于哪一个父项
    name_5_1->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    name_5_1->setText(0,QStringLiteral("无局灶性强回声或大彗星尾伪像"));
    name_5_1->setCheckState(0,Qt::Unchecked);

    QTreeWidgetItem* name_5_2 = new QTreeWidgetItem(name_5);   //指定子项属于哪一个父项
    name_5_2->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    name_5_2->setText(0,QStringLiteral("粗钙化"));
    name_5_2->setCheckState(0,Qt::Unchecked);

    QTreeWidgetItem* name_5_3 = new QTreeWidgetItem(name_5);   //指定子项属于哪一个父项
    name_5_3->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    name_5_3->setText(0,QStringLiteral("周边钙化"));
    name_5_3->setCheckState(0,Qt::Unchecked);

    QTreeWidgetItem* name_5_4 = new QTreeWidgetItem(name_5);   //指定子项属于哪一个父项
    name_5_4->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    name_5_4->setText(0,QStringLiteral("点状强回声"));
    name_5_4->setCheckState(0,Qt::Unchecked);

    QTreeWidgetItem* name_6 = new QTreeWidgetItem(ui->focuslabel);   //指定子项属于哪一个父项
    name_6->setText(0,QStringLiteral("良恶性"));

    QTreeWidgetItem* name_6_1 = new QTreeWidgetItem(name_6);   //指定子项属于哪一个父项
    name_6_1->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    name_6_1->setText(0,QStringLiteral("良性"));
    name_6_1->setCheckState(0,Qt::Unchecked);

    QTreeWidgetItem* name_6_2 = new QTreeWidgetItem(name_6);   //指定子项属于哪一个父项
    name_6_2->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    name_6_2->setText(0,QStringLiteral("恶性"));
    name_6_2->setCheckState(0,Qt::Unchecked);

    ui->focuslabel->expandAll();
}

void LabelMainWindow::_createPatient(QString ID)
{
    ui->listWidget->clear();
    QStringList tempList = m_patientImageList.value(ID);
    for (int i = 0; i < tempList.count(); i++)
    {
        QListWidgetItem *imageItem = new QListWidgetItem;
        QString dcm = tempList.at(i).section(".", -1);
        if (dcm == "dcm")
        {
            QImage *image = new QImage(*Dcm2Image(tempList.at(i)).getImage());
            imageItem->setIcon(QIcon(QPixmap::fromImage(*image)));
        }
        else
        {
            imageItem->setIcon(QIcon(tempList.at(i)));
        }
        imageItem->setText(tempList.at(i));
        imageItem->setSizeHint(QSize(100, 50));
        ui->listWidget->addItem(imageItem);


		if (!m_imageInfo.contains(imageItem->text().section('/', -1)))
		{
			ImageInfo imageinfo;
			m_OneLabelChecked.clear();

			QPixmap *pixmap = new QPixmap(imageItem->icon().pixmap(1000, 666));
			QPixmap *origin = new QPixmap(*pixmap);


			*pixmap = imageItem->icon().pixmap(1000, 666);
			*pixmap = pixmap->scaled(QSize(1000, 666), Qt::KeepAspectRatio);
			*origin = pixmap->copy();
			imageinfo.setOrigin(*origin);
			imageinfo.setFocusInfo(m_OneLabelChecked);
			m_imageInfo.insert(imageItem->text().section('/', -1), imageinfo);
			delete pixmap;
			delete origin;
		}


    }


}

void LabelMainWindow::_quitAndSave(QString ID, int flag)
{
    QJsonObject *PatientID = new QJsonObject;
    QStringList list = m_patientImageList.value(ID);
    for(int i = 0; i < list.count(); i++)
    {
        _saveImageInfo(PatientID, list[i]);
    }
    QJsonDocument jsonDoc(*PatientID);
    QByteArray ba = jsonDoc.toJson();
	QString allName;
    if(flag == 0)
    {
        allName = "./json/no/" + ID + ".json";
    }
    else
    {
         allName = "./json/yes/" + ID + ".json";
    }
    QFile file(allName);
    if(!file.open(QIODevice::WriteOnly))
    {
        //qDebug() << "write json file failed";
        return ;
    }
    file.write(ba);
    file.close();

}

void LabelMainWindow::_saveImageInfo(QJsonObject *PatientID, QString imagename)
{
    ImageInfo info = m_imageInfo[imagename.section('/', -1)];
    QJsonObject *json = new QJsonObject;
    QJsonObject *region  = new QJsonObject;
    QMap<QString, QMap<QString, QString>> focusInfo = info.getFocusInfo();
//    QMap<QString, QString>::iterator foucusIt = focusInfo.begin();
//    while(foucusIt != focusInfo.end())
//    {
//        json->insert(foucusIt.key(), foucusIt.value());
//        foucusIt++;
//    }
    json->insert("path", imagename);
    QMap<int, QPolygonF> poly = info.getPoly();
    QMap<int, QPolygonF>::iterator it = poly.begin();
    while(it != poly.end())
    {
        char a[11];
        const char *p = itoa(it.key(), a, 10);
        QString stringP = p;

        QMap<QString, QString> labelcheck = focusInfo[stringP];

        QJsonObject *tempJson  = new QJsonObject;
        QJsonObject *labelname  = new QJsonObject;
        QJsonObject *cod = new QJsonObject;
        QJsonObject *codObj = new QJsonObject;
        QPolygonF polygonF = it.value();
        int codNum = 1;
        for(int j = 0; j < polygonF.count(); j++)
        {
            codObj->insert("x:", polygonF[j].x());
            codObj->insert("y:", polygonF[j].y());
            cod->insert(QString::number(codNum++, 10), *codObj);
        }

        QMap<QString, QString>::iterator foucusIt = labelcheck.begin();
        while(foucusIt != labelcheck.end())
        {
            labelname->insert(foucusIt.key(), foucusIt.value());
            foucusIt++;
        }


        tempJson->insert("coordinate", *cod);
        tempJson->insert("name", *labelname);
        region->insert(p, *tempJson);
        it++;
        delete cod;
        delete codObj;
        delete tempJson;
    }
    json->insert("region", *region);
    json->insert("step", info.getStep());
    json->insert("index", info.getIndex());
    PatientID->insert(imagename, *json);
    delete region;
    delete json;
}

void LabelMainWindow::on_createnew_triggered()
{
    QStringList IDList;
    for(int i = 0; i < ui->donot->count(); i++)
    {
        IDList.push_back(ui->donot->item(i)->text());
    }
    for(int i = 0; i < ui->already->count(); i++)
    {
        IDList.push_back(ui->already->item(i)->text());
    }
    m_createNew = new CreateNew();
    m_createNew->show();
    m_createNew->IDList(IDList);
    connect(m_createNew, SIGNAL(createPatient(CreateNew *)), this, SLOT(createPatient(CreateNew *)));

}

void LabelMainWindow::createPatient(CreateNew *it)
{

    m_patientImageList.insert(it->getPatientID(), it->getFileNameList());
    QListWidgetItem* name = new QListWidgetItem(ui->donot);
    name->setText(it->getPatientID());
	name->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	name->setFlags(name->flags() & (~Qt::ItemIsEditable));
    _createPatient(it->getPatientID());
    ui->donot->setCurrentItem(name);
    changePatient(name);

}

void LabelMainWindow::itemPressedSlot(QListWidgetItem * pressedItem)
{
    if(qApp->mouseButtons() == Qt::RightButton)   //判断是否为右键
    {
        QMenu *menu = new QMenu(ui->donot);
        menu->addAction(m_add);
       // menu->addAction(m_delete);
        menu->exec(QCursor::pos());//菜单弹出位置为鼠标点击位置

    }
}

void LabelMainWindow::treeItemChanged(QTreeWidgetItem *item, int column)
{
    if(item->parent() == NULL)
        return;
    if(Qt::Checked == item->checkState(0))
    {
         QTreeWidgetItem* parent = item->parent();
         int count = parent->childCount(); //返回子项的个数
         {
             for(int i = 0; i < count; i++)
             {
                 if(parent->child(i)->checkState(0) == Qt::Checked && parent->child(i) != item)
                 {
                     parent->child(i)->setCheckState(0, Qt::Unchecked);
                 }
             }
         }
    }

}

void LabelMainWindow::on_LoadImage()
{
    QStringList list = QFileDialog::getOpenFileNames(this, tr("choose files"), tr("D:\\"), "", 0, 0);
    if(list.count( )<= 0)
    {
        QMessageBox::warning(this, tr("warning"), "choose no file!", QMessageBox::Yes);
        return ;
    }
    QStringList patient = m_patientImageList.value(ui->donot->currentItem()->text());
    for(int i = 0; i < list.count(); i++)
    {
        if( !patient.contains(list.at(i)))
        {
            patient.push_back(list.at(i));
        }
    }
    m_patientImageList.insert(ui->donot->currentItem()->text(), patient);

}

void LabelMainWindow::deletePatient()
{
    QListWidgetItem *item = ui->donot->currentItem();
    QMap<QString, QStringList>::iterator it = m_patientImageList.begin();
    while(it != m_patientImageList.end())
    {
        if(it.key() == item->text())
        {
            m_patientImageList.erase(it);
            break;
        }
        it++;
    }
    delete item;

}

void LabelMainWindow::showImage(QListWidgetItem *current, QListWidgetItem *previous)
{
    if(current == NULL)
        return;
    ui->label_3->setText(current->text().section('/',-1));

    if(previous != NULL)
    {
        ImageInfo imageinfo = m_imageInfo.value(previous->text().section('/', -1));
        imageinfo.setPoly(ui->label_8->labelInfo());
        int topCount = ui->focuslabel->topLevelItemCount();
        for (int i = 0; i < topCount; i++)
        {
            QTreeWidgetItem *item = ui->focuslabel->topLevelItem(i);
            for(int j = 0; j < item->childCount(); j++)
            {
               if(item->child(j)->checkState(0) == Qt::Checked)
               {
                   m_checked.insert(item->text(0), item->child(j)->text(0));
                   item->child(j)->setCheckState(0,Qt::Unchecked);
               }
            }
        }
        m_OneLabelChecked.insert(ui->focuslabel->headerItem()->text(0), m_checked);
        imageinfo.setStep(ui->label_8->getStep());
        imageinfo.setIndex(ui->label_8->getIndex());
        imageinfo.setFocusInfo(m_OneLabelChecked);
        m_imageInfo[previous->text().section('/', -1)] = imageinfo;
        m_checked.clear();
        m_OneLabelChecked.clear();

    }
    ui->focuslabel->setHeaderLabel("");
    for(int i = 0; i < ui->focuslabel->topLevelItemCount(); i++)
    {
        QTreeWidgetItem* parent = ui->focuslabel->topLevelItem(i);
        int count = parent->childCount();
        for(int i = 0; i < count; i++)
        {
            if(parent->child(i)->checkState(0) == Qt::Checked)
            {
                parent->child(i)->setCheckState(0, Qt::Unchecked);
            }
        }
    }

    if(!m_imageInfo.contains(current->text().section('/', -1)))
    {
        ImageInfo imageinfo;
        m_OneLabelChecked.clear();

        if(m_isNULLImage == true)
        {
            m_pixmap = new QPixmap(current->icon().pixmap(1000, 666));
            m_origin = new QPixmap(*m_pixmap);

            m_isNULLImage = false;
            ui->label_8->isNullImage(false);
        }
        *m_pixmap = current->icon().pixmap(1000, 666);
        *m_pixmap = m_pixmap->scaled(QSize(1000, 666), Qt::KeepAspectRatio);
        *m_origin = m_pixmap->copy();
        ui->label_7->resize(m_pixmap->size());
        ui->label_8->resize(m_pixmap->size());
        ui->label_7->setPixmap(*m_pixmap);
        ui->label_8->Resize(m_pixmap->size());
        ui->scrollArea->widget()->setMinimumSize(m_pixmap->size());
        ui->label_8->cleanPainter();
        ui->label_8->setStep(1.0);
        ui->label_8->cleanPolyPool();
        ui->label_8->setIndex(1);
        int x = ui->scrollArea->width() - ui->label_7->width();
        int y = ui->scrollArea->height() - ui->label_7->height();
        if(x < 0)
        {
            x = 0;
        }
        if(y < 0)
        {
            y = 0;
        }
        ui->label_7->setGeometry(x/2, y/2, ui->label_7->width(), ui->label_7->height());
        ui->label_8->setGeometry(x/2, y/2, ui->label_7->width(), ui->label_7->height());
        ui->label_7->setGeometry(x/2, y/2, ui->label_7->width(), ui->label_7->height());
        ui->label_8->setGeometry(x/2, y/2, ui->label_7->width(), ui->label_7->height());

        imageinfo.setOrigin(*m_origin);
        m_imageInfo.insert(current->text().section('/', -1), imageinfo);
    }
    else
    {
        ImageInfo imageinfo = m_imageInfo.value(current->text().section('/', -1));
        if(m_isNULLImage == true)
        {
            m_pixmap = new QPixmap(current->icon().pixmap(1000, 666));
            m_origin = new QPixmap(*m_pixmap);
            imageinfo.setOrigin(*m_origin);
            m_isNULLImage = false;
            ui->label_8->isNullImage(false);
        }

        m_origin = imageinfo.getOrigin();
        *m_pixmap = m_origin->scaled(m_origin->size() * imageinfo.getStep(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->label_7->resize(m_pixmap->size());
        ui->label_8->resize(m_pixmap->size());
        ui->label_7->setPixmap(*m_pixmap);
        ui->label_8->Resize(m_pixmap->size());
        ui->scrollArea->widget()->setMinimumSize(m_pixmap->size());
        ui->label_8->cleanPainter();
        ui->label_8->cleanPolyPool();
        ui->label_8->setStep(imageinfo.getStep());
        ui->label_8->setIndex(imageinfo.getIndex());
        int x = ui->scrollArea->width() - ui->label_7->width();
        int y = ui->scrollArea->height() - ui->label_7->height();
        if(x < 0)
        {
            x = 0;
        }
        if(y < 0)
        {
            y = 0;
        }
        ui->label_7->setGeometry(x/2, y/2, ui->label_7->width(), ui->label_7->height());
        ui->label_8->setGeometry(x/2, y/2, ui->label_7->width(), ui->label_7->height());
        ui->label_7->setGeometry(x/2, y/2, ui->label_7->width(), ui->label_7->height());
        ui->label_8->setGeometry(x/2, y/2, ui->label_7->width(), ui->label_7->height());

        QMap<int, QPolygonF> tempMap = imageinfo.getPoly();
        QMap<int, QPolygonF>::Iterator it = tempMap.begin();

        while(it != tempMap.end())
        {
            QPolygonF temp = it.value();
            ui->label_8->paint(temp, it.key());
            it++;
        }

        m_OneLabelChecked = imageinfo.getFocusInfo();
//        QMap<QString, QString>::Iterator tempIt = temp.begin();
//        while(tempIt != temp.end())
//        {
//             addFocusItem(tempIt.key(), tempIt.value());
//             tempIt++;
//        }

    }

}

void LabelMainWindow::addFocusItem(QString parent, QString child)
{

    int topCount = ui->focuslabel->topLevelItemCount();
    for (int i = 0; i < topCount; i++)
    {
        QTreeWidgetItem *item = ui->focuslabel->topLevelItem(i);
        for(int j = 0; j < item->childCount(); j++)
        {
           if(item->text(0) == parent && item->child(j)->text(0) == child)
           {
               item->child(j)->setCheckState(0,Qt::Checked);
           }
        }
    }
}

void LabelMainWindow::changeSize(float size)
{
    m_isSaved = false;
    *m_pixmap = m_origin->scaled(m_origin->width()*size, m_origin->height()*size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->scrollArea->widget()->setMinimumSize(m_pixmap->size());
    ui->label_7->resize(m_pixmap->size());
    ui->label_8->resize(m_pixmap->size());
    ui->label_7->setPixmap(*m_pixmap);
    ui->label_8->Resize(m_pixmap->size());
    int x = ui->scrollArea->width() - ui->label_7->width();
    int y = ui->scrollArea->height() - ui->label_7->height();
    if(x < 0)
    {
        x = 0;
    }
    if(y < 0)
    {
        y = 0;
    }
    ui->label_7->setGeometry(x/2, y/2, ui->label_7->width(), ui->label_7->height());
    ui->label_8->setGeometry(x/2, y/2, ui->label_7->width(), ui->label_7->height());

}

void LabelMainWindow::treeAddLabel(int index)
{
    m_isSaved = false;
    int topCount = ui->focuslabel->topLevelItemCount();
    for (int i = 0; i < topCount; i++)
    {
        QTreeWidgetItem *item = ui->focuslabel->topLevelItem(i);
        for(int j = 0; j < item->childCount(); j++)
        {
           if(item->child(j)->checkState(0) == Qt::Checked)
           {
               m_checked.insert(item->text(0), item->child(j)->text(0));
               item->child(j)->setCheckState(0,Qt::Unchecked);
           }
        }
    }
    m_OneLabelChecked[ui->focuslabel->headerItem()->text(0)] = m_checked;
    m_checked.clear();



    char a[11];
    const char *p = itoa(index,a,10);
    QString temp = p;
    QMap<QString, QString> newlabel;
    m_OneLabelChecked.insert(temp, newlabel);
    ui->focuslabel->setHeaderLabel(temp);
    for(int i = 0; i < ui->focuslabel->topLevelItemCount(); i++)
    {
        QTreeWidgetItem* parent = ui->focuslabel->topLevelItem(i);
        int count = parent->childCount();
        for(int i = 0; i < count; i++)
        {
            if(parent->child(i)->checkState(0) == Qt::Checked)
            {
                parent->child(i)->setCheckState(0, Qt::Unchecked);
            }
        }
    }

}

void LabelMainWindow::setcurrentLabel(int index)
{
    char a[11];
    const char *p = itoa(index,a,10);
    QString temp = p;

	int topCount = ui->focuslabel->topLevelItemCount();
    for (int i = 0; i < topCount; i++)
    {
        QTreeWidgetItem *item = ui->focuslabel->topLevelItem(i);
        for(int j = 0; j < item->childCount(); j++)
        {
           if(item->child(j)->checkState(0) == Qt::Checked)
           {
               m_checked.insert(item->text(0), item->child(j)->text(0));
               item->child(j)->setCheckState(0,Qt::Unchecked);
           }
        }
    }
    m_OneLabelChecked[ui->focuslabel->headerItem()->text(0)] = m_checked;
    m_checked.clear();

    ui->focuslabel->setHeaderLabel(temp);
    m_checked = m_OneLabelChecked[temp];
    QMap<QString, QString>::Iterator tempIt = m_checked.begin();
    while(tempIt != m_checked.end())
    {
         addFocusItem(tempIt.key(), tempIt.value());
         tempIt++;
    }
    m_checked.clear();

}

void LabelMainWindow::treeRemoveLabel(int index)
{
    m_isSaved = false;
    char a[11];
    const char *p = itoa(index, a, 10);
    QString temp = p;
    QMap<QString, QMap<QString, QString>>::iterator it = m_OneLabelChecked.begin();
    while(it != m_OneLabelChecked.end())
    {
        if(it.key() == p)
        {
            m_OneLabelChecked.erase(it);
            break;
        }
        it++;
    }
}

void LabelMainWindow::changeNOPatient(QListWidgetItem *item, QListWidgetItem *previous)
{

    ImageInfo imageinfo = m_imageInfo.value(ui->label_3->text());
    imageinfo.setPoly(ui->label_8->labelInfo());
    int topCount = ui->focuslabel->topLevelItemCount();
    for (int i = 0; i < topCount; i++)
    {
        QTreeWidgetItem *item = ui->focuslabel->topLevelItem(i);
        for(int j = 0; j < item->childCount(); j++)
        {
           if(item->child(j)->checkState(0) == Qt::Checked)
           {
               m_checked.insert(item->text(0), item->child(j)->text(0));
               item->child(j)->setCheckState(0,Qt::Unchecked);
           }
        }
    }


    m_OneLabelChecked.insert(ui->focuslabel->headerItem()->text(0), m_checked);
    imageinfo.setStep(ui->label_8->getStep());
    imageinfo.setIndex(ui->label_8->getIndex());

    imageinfo.setFocusInfo(m_OneLabelChecked);
    m_imageInfo[ui->label_3->text()] = imageinfo;
    m_checked.clear();
    m_OneLabelChecked.clear();


     _createPatient(item->text());
     ui->listWidget->setCurrentItem(ui->listWidget->item(0));
     ui->label_5->setText(item->text());


     if(previous == NULL)
         return;
     QStringList list = m_patientImageList[previous->text()];
	 if (list.count() == 0)
		 return;
     for(int i = 0; i < list.count(); i++)
     {
         ImageInfo info = m_imageInfo[list.at(i).section('/', -1)];
         if(info.getIndex() == 1)
             return;
     }

         QString ID = previous->text();
         for(int i = 0; i < ui->donot->count(); i++)
         {
             if(ui->donot->item(i)->text() == ID)
             {
                 delete ui->donot->item(i);
                 break;
             }
         }

             QListWidgetItem* name = new QListWidgetItem(ui->already);
             name->setText(ID);
			 name->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			 name->setFlags(name->flags() & (~Qt::ItemIsEditable));


}

void LabelMainWindow::changePatient(QListWidgetItem* item)
{
    ImageInfo imageinfo = m_imageInfo.value(ui->label_3->text());
    imageinfo.setPoly(ui->label_8->labelInfo());
    int topCount = ui->focuslabel->topLevelItemCount();
    for (int i = 0; i < topCount; i++)
    {
        QTreeWidgetItem *item = ui->focuslabel->topLevelItem(i);
        for(int j = 0; j < item->childCount(); j++)
        {
           if(item->child(j)->checkState(0) == Qt::Checked)
           {
               m_checked.insert(item->text(0), item->child(j)->text(0));
               item->child(j)->setCheckState(0,Qt::Unchecked);
           }
        }
    }

    m_OneLabelChecked.insert(ui->focuslabel->headerItem()->text(0), m_checked);
    imageinfo.setStep(ui->label_8->getStep());
    imageinfo.setIndex(ui->label_8->getIndex());

    imageinfo.setFocusInfo(m_OneLabelChecked);
    m_imageInfo[ui->label_3->text()] = imageinfo;
    m_checked.clear();
    m_OneLabelChecked.clear();


     _createPatient(item->text());
     ui->listWidget->setCurrentItem(ui->listWidget->item(0));
     ui->label_5->setText(item->text());

    ui->donot->setCurrentItem(item);
}

void LabelMainWindow::changeALPatient(QListWidgetItem *item)
{
    ImageInfo imageinfo = m_imageInfo.value(ui->label_3->text());
    imageinfo.setPoly(ui->label_8->labelInfo());
    int topCount = ui->focuslabel->topLevelItemCount();
    for (int i = 0; i < topCount; i++)
    {
        QTreeWidgetItem *item = ui->focuslabel->topLevelItem(i);
        for(int j = 0; j < item->childCount(); j++)
        {
           if(item->child(j)->checkState(0) == Qt::Checked)
           {
               m_checked.insert(item->text(0), item->child(j)->text(0));
               item->child(j)->setCheckState(0,Qt::Unchecked);
           }
        }
    }

    m_OneLabelChecked.insert(ui->focuslabel->headerItem()->text(0), m_checked);
    imageinfo.setStep(ui->label_8->getStep());
    imageinfo.setIndex(ui->label_8->getIndex());

    imageinfo.setFocusInfo(m_OneLabelChecked);
    m_imageInfo[ui->label_3->text()] = imageinfo;
    m_checked.clear();
    m_OneLabelChecked.clear();


     _createPatient(item->text());
     ui->listWidget->setCurrentItem(ui->listWidget->item(0));
     ui->label_5->setText(item->text());
}

void LabelMainWindow::on_big_clicked()
{
    ui->label_8->changeSize(1.1);
}

void LabelMainWindow::on_small_clicked()
{
    ui->label_8->changeSize(0.9);
}

void LabelMainWindow::on_save_clicked()
{

//    if(ui->donot->count() == 0)
//        return;
//    QString ID = ui->label_5->text();
//    for(int i = 0; i < ui->donot->count(); i++)
//    {
//        if(ui->donot->item(i)->text() == ID)
//        {
//            delete ui->donot->item(i);
//            break;
//        }
//    }

//    ImageInfo imageinfo = m_imageInfo.value(ui->label_3->text());
//    imageinfo.setPoly(ui->label_8->labelInfo());
//    int topCount = ui->focuslabel->topLevelItemCount();
//    for (int i = 0; i < topCount; i++)
//    {
//        QTreeWidgetItem *item = ui->focuslabel->topLevelItem(i);
//        for(int j = 0; j < item->childCount(); j++)
//        {
//           if(item->child(j)->checkState(0) == Qt::Checked)
//           {
//               m_checked.insert(item->text(0), item->child(j)->text(0));
//               item->child(j)->setCheckState(0,Qt::Unchecked);
//           }
//        }
//    }

//    m_OneLabelChecked.insert(ui->focuslabel->headerItem()->text(0), m_checked);
//    imageinfo.setStep(ui->label_8->getStep());
//    imageinfo.setIndex(ui->label_8->getIndex());
//    imageinfo.setFocusInfo(m_OneLabelChecked);
//    m_imageInfo[ui->label_3->text()] = imageinfo;
//    m_checked.clear();
//    m_OneLabelChecked.clear();



//    QListWidgetItem* name = new QListWidgetItem(ui->already);
//    name->setText(ID);
//    name->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);   //树形控件显示的文本信息
//    if(ui->donot->count() != 0)
//    {
//        ui->donot->setCurrentItem(ui->donot->item(0));
//    }
//    else
//    {
//        ui->listWidget->clear();
//    }

    ImageInfo imageinfo = m_imageInfo.value(ui->listWidget->currentItem()->text().section('/', -1));
    imageinfo.setPoly(ui->label_8->labelInfo());
    int topCount = ui->focuslabel->topLevelItemCount();
    for (int i = 0; i < topCount; i++)
    {
        QTreeWidgetItem *item = ui->focuslabel->topLevelItem(i);
        for(int j = 0; j < item->childCount(); j++)
        {
           if(item->child(j)->checkState(0) == Qt::Checked)
           {
               m_checked.insert(item->text(0), item->child(j)->text(0));
               item->child(j)->setCheckState(0,Qt::Unchecked);
           }
        }
    }
    m_OneLabelChecked.insert(ui->focuslabel->headerItem()->text(0), m_checked);
    imageinfo.setStep(ui->label_8->getStep());
    imageinfo.setIndex(ui->label_8->getIndex());
    imageinfo.setFocusInfo(m_OneLabelChecked);
    m_imageInfo[ui->listWidget->currentItem()->text().section('/', -1)] = imageinfo;
    m_checked.clear();
    m_OneLabelChecked.clear();


    removeFolderContent("./json/no/");

    int count = ui->donot->count();
    for(int i = 0; i < count; i++)
    {
        _quitAndSave(ui->donot->item(i)->text(), 0);
    }

    int count1 = ui->already->count();
    for(int i = 0; i < count1; i++)
    {
        _quitAndSave(ui->already->item(i)->text(), 1);
    }

    m_isSaved = true;
}

void LabelMainWindow::on_last_clicked()
{
   QListWidgetItem *item = ui->listWidget->currentItem();
   for(int i = 0; i < ui->listWidget->count() - 1; i++)
   {
       if(ui->listWidget->item(i+1)->text() == item->text())
       {
          ui->listWidget->setCurrentItem(ui->listWidget->item(i));
       }
   }
}

void LabelMainWindow::on_next_clicked()
{
    QListWidgetItem *item = ui->listWidget->currentItem();
    for(int i = 0; i < ui->listWidget->count(); i++)
    {
        if(ui->listWidget->item(i)->text() == item->text() && i != ui->listWidget->count() - 1)
        {
            ui->listWidget->setCurrentItem(ui->listWidget->item(i+1));
        }
    }
}

void LabelMainWindow::closeEvent(QCloseEvent *e)
{
    if(m_isSaved == true)
        return;

    QMessageBox::StandardButton button;
    button = QMessageBox::question(this, QStringLiteral("退出程序"),
            QString(QStringLiteral("警告：是否保存并退出")),
            QMessageBox::Yes | QMessageBox::No | QMessageBox::Close);

    if(button == QMessageBox::Close)
    {
        e->ignore();
    }
    else if (button == QMessageBox::Yes)
    {
         on_save_clicked();
         e->accept();//接受退出信号，程序退出
    }
    else if (button == QMessageBox::No)
    {
         e->accept();//接受退出信号，程序退出
    }

}

bool LabelMainWindow::removeFolderContent(const QString &folderDir)
{
    QDir dir(folderDir);
    QFileInfoList fileList;
    QFileInfo curFile;
    if(!dir.exists())  {return false;}//文件不存，则返回false
    fileList=dir.entryInfoList(QDir::Dirs|QDir::Files
                               |QDir::Readable|QDir::Writable
                               |QDir::Hidden|QDir::NoDotAndDotDot
                               ,QDir::Name);
    while(fileList.size()>0)
    {
        int infoNum=fileList.size();
        for(int i=infoNum-1;i>=0;i--)
        {
            curFile=fileList[i];
            if(curFile.isFile())//如果是文件，删除文件
            {
                QFile fileTemp(curFile.filePath());
                fileTemp.remove();
                fileList.removeAt(i);
            }
            if(curFile.isDir())//如果是文件夹
            {
                QDir dirTemp(curFile.filePath());
                QFileInfoList fileList1=dirTemp.entryInfoList(QDir::Dirs|QDir::Files
                                                              |QDir::Readable|QDir::Writable
                                                              |QDir::Hidden|QDir::NoDotAndDotDot
                                                              ,QDir::Name);
                if(fileList1.size()==0)//下层没有文件或文件夹
                {
                    dirTemp.rmdir(".");
                    fileList.removeAt(i);
                }
                else//下层有文件夹或文件
                {
                    for(int j=0;j<fileList1.size();j++)
                    {
                        if(!(fileList.contains(fileList1[j])))
                            fileList.append(fileList1[j]);
                    }
                }
            }
        }
    }
    return true;
}
