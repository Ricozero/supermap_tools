#include <iostream>
#include <Workspace/UGWorkspace.h>
using namespace UGC;

int main()
{
	UGWorkspace workspace;
	UGString workspacePath = _U("D:\\Program Files\\SuperMap iDesktop 9D\\SampleData\\China\\China100\\China.smwu");
	if (!workspace.Open(workspacePath))
	{
		cout << "工作空间打开失败！" << endl;
		return -1;
	}
	cout << "工作空间共包含：" << endl;
	cout << workspace.m_MapStorages.GetCount() << "张地图" << endl;
	cout << workspace.m_DataSources.GetCount() << "个数据源" << endl << endl;

	UGDataSource* dataSource = workspace.GetDataSource(0);
	if (!dataSource->Open())
	{
		cout << "数据源打开失败！" << endl;
		return -1;
	}
	cout << "打开第一个数据源，共包含：" << endl;
	cout << dataSource->GetDatasetCount() << "个数据集" << endl << endl;

	UGDatasets* dataSets = dataSource->GetDatasets();
	UGDataset** dataSetsP = dataSets->GetData();
	UGDataset* dataSet;
	int i;
	cout << "各个数据集信息：" << endl;
	for (i = 0; i < dataSource->GetDatasetCount(); i++)
	{
		dataSet = dataSetsP[i];
		wcout << i << "：类型为" << dataSet->GetType()
			<< "，名称为" << dataSet->GetName().Cstr()
			<< "，表名为" << dataSet->GetTableName().Cstr()
			<< endl;
	}

	i = 6;
	dataSet = dataSetsP[i];
	if (!dataSet->Open())
	{
		cout << "数据集打开失败！" << endl;
		return -1;
	}
	cout << "打开索引为" << i << "的数据集" << (dataSet->IsVector() ? "是" : "不是") << "矢量" << endl;

	return 0;
}