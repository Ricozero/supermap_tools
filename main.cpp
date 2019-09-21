#include <iostream>
#include <Workspace/UGWorkspace.h>
#include <Geometry/UGGeometry.h>
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
	cout << workspace.m_DataSources.GetCount() << "个数据源" << endl;
	cout << workspace.m_MapStorages.GetCount() << "张地图" << endl;
	cout << endl;

	UGDataSource *dataSource = workspace.GetDataSource(0);
	if (!dataSource->Open())
	{
		cout << "数据源打开失败！" << endl;
		return -1;
	}
	cout << "打开第一个数据源，共包含：" << endl;
	cout << dataSource->GetDatasetCount() << "个数据集" << endl;
	cout << endl;

	UGDatasets *dataSets = dataSource->GetDatasets();
	UGDataset **dataSetsP = dataSets->GetData();
	UGDataset *dataSet;
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

	i = 5;
	dataSet = dataSetsP[i];
	if (!dataSet->Open())
	{
		cout << "数据集打开失败！" << endl;
		return -1;
	}
	cout << "打开索引为" << i << "的数据集（" << (dataSet->IsVector() ? "是" : "不是") << "矢量）" << endl;

	UGDatasetVector *dataSetVector = (UGDatasetVector *)dataSet;
	cout << "对象个数为：" << dataSetVector->GetObjectCount() << endl;
	UGQueryDef query;
	UGRecordset *recordset = dataSetVector->Query(query);
	cout << "查询数据集，记录个数为：" << recordset->GetRecordCount() << endl;
	//wcout << query.ToXML(0).Cstr() << endl;

	UGGeometry *pGeometry = NULL;
	recordset->GetGeometry(pGeometry);
	cout << "获取第一个记录，对应的几何体类型为：" << pGeometry->GetType() << endl;

	UGGeoRegion *pRegion = (UGGeoRegion *)pGeometry;
	cout << "面的顶点数为：" << pRegion->GetPointCount() << endl;
	cout << "面的子对象数为：" << pRegion->GetSubCount() << endl;
	cout << "第一个子对象顶点数为：" << pRegion->GetSubPntCount(0) << endl;
	const UGPoint2D *pPoint2D = pRegion->GetPoints(0);
	cout << "坐标分别为：" << endl;
	for (i = 0; i < pRegion->GetSubPntCount(0); i++)
		cout << '(' << pPoint2D[i].x << ", " << pPoint2D[i].y << ')' << endl;
	
	UGPoint2D point(0, 0);
	cout << "修改坐标，" << (pRegion->SetPoint(1, point) ? "成功" : "失败") << endl;
	cout << "修改后坐标分别为：" << endl;
	for (i = 0; i < pRegion->GetSubPntCount(0); i++)
		cout << '(' << pPoint2D[i].x << ", " << pPoint2D[i].y << ')' << endl;

	cout << "更新数据集，结果为：" << (recordset->Update() != -1 ? "成功" : "失败") << endl;
	// 并没有更新文件

	delete pGeometry;
	return 0;
}