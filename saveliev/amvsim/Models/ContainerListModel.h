#ifndef CONTAINERLISTMODEL_H
#define CONTAINERLISTMODEL_H

#include <vector>
#include <QString>
#include <QAbstractListModel>

#include "../api/IDevice.h"
#include "../api/ContainerInfo.h"

class ContainerListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit ContainerListModel(IDevice* device, QObject* parent = 0);

    QVariant data(const QModelIndex& index, int role) const;
    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    int columnCount(const QModelIndex& parent = QModelIndex()) const;

    int createContainer(const QString& name, StorageDescriptor& descriptor);
    int destroyContainer(const QString& name);
    int switchToContainer(const QString& name);
    int startContainer(const QString& name);
    int stopContainer(const QString& name);

    ContainerInfo getContainerInfo(const QString& name);
    
    void parameterChanged(int parameterId, Value newValue);      
    const std::vector<Parameter*> &getContainerParametersList() const;
    const std::vector<Parameter*> &getDeviceParametersList() const;     
    std::vector<Value*> getContainerParametersValues(const std::string& containerId) const;   
    std::vector<Value*> getDeviceParametersValues() const;   

 // QModelIndex index(int row, int column, const QModelIndex&parent) const;
 // QModelIndex parent(const QModelIndex&child) const;

private:
    IDevice* m_device;
    std::vector<QString> m_ids;
    
    int getRow(const QString& name) const;
    
signals:
    void containersSelected(const QString& contName);
};

#endif // CONTAINERLISTMODEL_H












