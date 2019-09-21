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
		cout << "�����ռ��ʧ�ܣ�" << endl;
		return -1;
	}
	cout << "�����ռ乲������" << endl;
	cout << workspace.m_DataSources.GetCount() << "������Դ" << endl;
	cout << workspace.m_MapStorages.GetCount() << "�ŵ�ͼ" << endl;
	cout << endl;

	UGDataSource *dataSource = workspace.GetDataSource(0);
	if (!dataSource->Open())
	{
		cout << "����Դ��ʧ�ܣ�" << endl;
		return -1;
	}
	cout << "�򿪵�һ������Դ����������" << endl;
	cout << dataSource->GetDatasetCount() << "�����ݼ�" << endl;
	cout << endl;

	UGDatasets *dataSets = dataSource->GetDatasets();
	UGDataset **dataSetsP = dataSets->GetData();
	UGDataset *dataSet;
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

	i = 5;
	dataSet = dataSetsP[i];
	if (!dataSet->Open())
	{
		cout << "���ݼ���ʧ�ܣ�" << endl;
		return -1;
	}
	cout << "������Ϊ" << i << "�����ݼ���" << (dataSet->IsVector() ? "��" : "����") << "ʸ����" << endl;

	UGDatasetVector *dataSetVector = (UGDatasetVector *)dataSet;
	cout << "�������Ϊ��" << dataSetVector->GetObjectCount() << endl;
	UGQueryDef query;
	UGRecordset *recordset = dataSetVector->Query(query);
	cout << "��ѯ���ݼ�����¼����Ϊ��" << recordset->GetRecordCount() << endl;
	//wcout << query.ToXML(0).Cstr() << endl;

	UGGeometry *pGeometry = NULL;
	recordset->GetGeometry(pGeometry);
	cout << "��ȡ��һ����¼����Ӧ�ļ���������Ϊ��" << pGeometry->GetType() << endl;

	UGGeoRegion *pRegion = (UGGeoRegion *)pGeometry;
	cout << "��Ķ�����Ϊ��" << pRegion->GetPointCount() << endl;
	cout << "����Ӷ�����Ϊ��" << pRegion->GetSubCount() << endl;
	cout << "��һ���Ӷ��󶥵���Ϊ��" << pRegion->GetSubPntCount(0) << endl;
	const UGPoint2D *pPoint2D = pRegion->GetPoints(0);
	cout << "����ֱ�Ϊ��" << endl;
	for (i = 0; i < pRegion->GetSubPntCount(0); i++)
		cout << '(' << pPoint2D[i].x << ", " << pPoint2D[i].y << ')' << endl;
	
	UGPoint2D point(0, 0);
	cout << "�޸����꣬" << (pRegion->SetPoint(1, point) ? "�ɹ�" : "ʧ��") << endl;
	cout << "�޸ĺ�����ֱ�Ϊ��" << endl;
	for (i = 0; i < pRegion->GetSubPntCount(0); i++)
		cout << '(' << pPoint2D[i].x << ", " << pPoint2D[i].y << ')' << endl;

	cout << "�������ݼ������Ϊ��" << (recordset->Update() != -1 ? "�ɹ�" : "ʧ��") << endl;
	// ��û�и����ļ�

	delete pGeometry;
	return 0;
}