#ifndef LABELMAINWINDOW_H
#define LABELMAINWINDOW_H

#include <QMainWindow>
#include "AccountManagement/mainaccountwindow.h"
#include "Patient/createnew.h"
#include "imageinfo.h"
#include <QMap>
#include <QStringList>
#include <QListWidgetItem>
#include <QTreeWidget>
#include <QJsonObject>
#include <QPolygonF>
#include <QJsonDocument>
#include <QCloseEvent>

namespace Ui {
class LabelMainWindow;
}

class LabelMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LabelMainWindow(QWidget *parent = 0);

    ~LabelMainWindow();

    void addFocusItem(QString parent, QString child);

    bool removeFolderContent(const QString &folderDir);

protected:
    void closeEvent(QCloseEvent *e);

private:
    void _initFocusLabel();

    void _createPatient(QString ID);

    void _quitAndSave(QString ID, int flag);

    void _saveImageInfo(QJsonObject *jsonObject, QString imagename);

    void _loadDir(QString path, int flag);

    void _parse(QString path, QString ID);

    void _parseImg(QJsonValue childObj);

private slots:
  //  void on_AccountManagement_triggered();

    void on_createnew_triggered();

    void createPatient(CreateNew *it);

    void showImage(QListWidgetItem *, QListWidgetItem *);

    void changeNOPatient(QListWidgetItem*, QListWidgetItem*);

    void changeALPatient(QListWidgetItem*);

    void changePatient(QListWidgetItem*);

    void itemPressedSlot(QListWidgetItem *);

    void treeItemChanged(QTreeWidgetItem *, int);

    void on_LoadImage();

    void deletePatient();

    void changeSize(float size);

    void treeAddLabel(int index);

    void setcurrentLabel(int index);

    void treeRemoveLabel(int index);

    void on_big_clicked();

    void on_small_clicked();

    void on_save_clicked();

    void on_last_clicked();

    void on_next_clicked();

//    void on_load_triggered();

private:
    Ui::LabelMainWindow *ui;
   // MainAccountWindow *m_mainAccountWindow;
    CreateNew *m_createNew;
    QMap<QString, QStringList> m_patientImageList;
    QMap<QString, ImageInfo> m_imageInfo;
    QMap<QString, QString> m_checked;
    QMap<QString, QMap<QString, QString>> m_OneLabelChecked;
    QMap<QString, QJsonObject> m_jsonMap;
    int m_currentIndex;
    QPixmap *m_pixmap;
    QPixmap *m_origin;
    QAction *m_add;
    QAction *m_delete;
    bool m_isNULLImage;
    bool m_isSaved;

};

#endif // LABELMAINWINDOW_H

