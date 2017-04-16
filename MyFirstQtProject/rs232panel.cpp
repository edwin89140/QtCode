#include "rs232panel.h"

#include <QHeaderView>
#include <QSerialPort>
#include <QSerialPortInfo>

RS232Panel::RS232Panel(QWidget *parent) : QTreeWidget(parent){
    initPanel();
    setPanel();
}

RS232Panel::~RS232Panel(){
    this->destroy(true,true);
}

void RS232Panel::initPanel(){
    this->setStyleSheet( "QHeaderView::section { "
                                    "background-color : #3399ff;"
                                    "font : 12px Cambria;  }");
    this->setHeaderLabels(QStringList() << "Property" << "Value");
    this->setMinimumSize(QSize(180,175));
    this->setIndentation(0);
    this->setColumnCount(2);
    this->setColumnWidth(0,80);
    this->setColumnWidth(1,90);

    NameItem = new QTreeWidgetItem(this);
    BaudRateItem = new QTreeWidgetItem(this);
    StopBitItem = new QTreeWidgetItem(this);
    ParityItem = new QTreeWidgetItem(this);
    DataBitItem = new QTreeWidgetItem(this);
    FlowControlItem = new QTreeWidgetItem(this);

    NameList = new QComboBox();
    BaudRateList = new QComboBox();
    StopBitList = new QComboBox();
    ParityList = new QComboBox();
    DataBitList = new QComboBox();
    FlowControlList = new QComboBox();
}

void RS232Panel::setPanel(){

    NameItem->setText(0, "PortName");
    BaudRateItem->setText(0, "BaudRate");
    StopBitItem->setText(0, "StopBit");
    ParityItem->setText(0, "Parity");
    DataBitItem->setText(0, "DataBit");
    FlowControlItem->setText(0, "FlowControl");

    setCombox();

    this->setItemWidget(NameItem, 1, NameList);
    this->setItemWidget(BaudRateItem, 1, BaudRateList);
    this->setItemWidget(StopBitItem, 1, DataBitList);
    this->setItemWidget(ParityItem, 1, ParityList);
    this->setItemWidget(DataBitItem, 1, StopBitList);
    this->setItemWidget(FlowControlItem, 1, FlowControlList);

}

void RS232Panel::setCombox(){

    //----port name
    NameList->setFixedSize(100,25);
    foreach(auto &name, detectSerialPort()){
        NameList->addItem(name, name);
    }

    //----baud rate
    BaudRateList->setFixedSize(100,25);
    BaudRateList->addItem("115200", QSerialPort::Baud115200);
    BaudRateList->addItem("57600", QSerialPort::Baud57600);
    BaudRateList->addItem("38400", QSerialPort::Baud38400);
    BaudRateList->addItem("9600", QSerialPort::Baud9600);
    //----data bit
    DataBitList->setFixedSize(100,25);
    DataBitList->addItem("8", QSerialPort::Data8);
    DataBitList->addItem("7", QSerialPort::Data7);
    DataBitList->addItem("6", QSerialPort::Data6);
    DataBitList->addItem("5", QSerialPort::Data5);
    //----parity
    ParityList->setFixedSize(100,25);
    ParityList->addItem("None", QSerialPort::NoParity);
    ParityList->addItem("Even", QSerialPort::EvenParity);
    ParityList->addItem("Odd", QSerialPort::OddParity);
    ParityList->addItem("Mark", QSerialPort::MarkParity);
    ParityList->addItem("Space", QSerialPort::SpaceParity);
    //----stop bit
    StopBitList->setFixedSize(100,25);
    StopBitList->addItem("1", QSerialPort::OneStop);
    StopBitList->addItem("2", QSerialPort::TwoStop);
    //----flow control
    FlowControlList->setFixedSize(100,25);
    FlowControlList->addItem("None", QSerialPort::NoFlowControl);
    FlowControlList->addItem("RTS/CTS", QSerialPort::HardwareControl);
    FlowControlList->addItem("XON/XOFF", QSerialPort::SoftwareControl);

    NameList->setCurrentIndex(0);
    BaudRateList->setCurrentIndex(0);
    DataBitList->setCurrentIndex(0);
    ParityList->setCurrentIndex(0);
    StopBitList->setCurrentIndex(0);
    FlowControlList->setCurrentIndex(0);
}

QStringList RS232Panel::detectSerialPort(){
    bool isFirst = true;
    QStringList PortNameList;
    QSerialPort *Comport = new QSerialPort();

    foreach(auto &PortInfo, QSerialPortInfo::availablePorts()){
        if(isFirst){
            Comport->setPortName(PortInfo.portName());
            Comport->open(QSerialPort::ReadWrite);
            if(Comport->isOpen()){
                PortNameList.prepend(PortInfo.portName());
            }
        }
        PortNameList.append(PortInfo.portName());
    }

    return PortNameList;
}

QVariantList RS232Panel::getPanelValue(){
    QVariantList PortParameter;

    PortParameter << NameList->currentData() << BaudRateList->currentData()
                            << DataBitList->currentData() << ParityList->currentData()
                            << StopBitList->currentData() << FlowControlList->currentData();
    return PortParameter;
}
