#ifndef RS232PANEL_H
#define RS232PANEL_H

#include <QWidget>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QComboBox>

class RS232Panel : public QTreeWidget
{
    Q_OBJECT
public:
    explicit RS232Panel(QWidget *parent = 0);
    ~RS232Panel();

    void initPanel();
    void setPanel();
    void setCombox();
    QStringList detectSerialPort();
    QVariantList getPanelValue();
private:
    QTreeWidgetItem *NameItem;
    QTreeWidgetItem *BaudRateItem;
    QTreeWidgetItem *StopBitItem;
    QTreeWidgetItem *ParityItem;
    QTreeWidgetItem *DataBitItem;
    QTreeWidgetItem *FlowControlItem;

    QComboBox *NameList;
    QComboBox *BaudRateList;
    QComboBox *StopBitList;
    QComboBox *ParityList;
    QComboBox *DataBitList;
    QComboBox *FlowControlList;
signals:

public slots:
};

#endif // RS232PANEL_H
