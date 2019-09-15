#include <iostream>
#include <Workspace/UGWorkspace.h>
using namespace UGC;

int main()
{
	UGWorkspace workspace;
	UGString workspacePath = _U("D:\\Program Files\\SuperMap iDesktop 9D\\SampleData\\China\\China100\\China.smwu");
	if (!workspace.Open(workspacePath))
	{
		cout << "�����ռ��ʧ�ܣ�" << endl;
		return -1;
	}
	cout << "�����ռ乲������" << endl;
	cout << workspace.m_MapStorages.GetCount() << "�ŵ�ͼ" << endl;
	cout << workspace.m_DataSources.GetCount() << "������Դ" << endl << endl;

	UGDataSource* dataSource = workspace.GetDataSource(0);
	if (!dataSource->Open())
	{
		cout << "����Դ��ʧ�ܣ�" << endl;
		return -1;
	}
	cout << "�򿪵�һ������Դ����������" << endl;
	cout << dataSource->GetDatasetCount() << "�����ݼ�" << endl << endl;

	UGDatasets* dataSets = dataSource->GetDatasets();
	UGDataset** dataSetsP = dataSets->GetData();
	UGDataset* dataSet;
	int i;
	cout << "�������ݼ���Ϣ��" << endl;
	for (i = 0; i < dataSource->GetDatasetCount(); i++)
	{
		dataSet = dataSetsP[i];
		wcout << i << "������Ϊ" << dataSet->GetType()
			<< "������Ϊ" << dataSet->GetName().Cstr()
			<< "������Ϊ" << dataSet->GetTableName().Cstr()
			<< endl;
	}

	i = 6;
	dataSet = dataSetsP[i];
	if (!dataSet->Open())
	{
		cout << "���ݼ���ʧ�ܣ�" << endl;
		return -1;
	}
	cout << "������Ϊ" << i << "�����ݼ�" << (dataSet->IsVector() ? "��" : "����") << "ʸ��" << endl;

	return 0;
}