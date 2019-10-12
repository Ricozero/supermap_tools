#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
#include <Workspace/UGWorkspace.h>
#include <Geometry/UGGeometry.h>
#include "json/CJsonObject.hpp"
using namespace UGC;

void testSuperMap()
{
	UGWorkspace workspace;
	UGString workspacePath = _U("D:\\Program Files\\SuperMap iDesktop 9D\\SampleData\\China\\China100\\China.smwu");
	if (!workspace.Open(workspacePath))
	{
		cout << "�����ռ��ʧ�ܣ����ܱ���������ռ�ã�" << endl;
	}
	cout << "�����ռ乲������" << endl;
	cout << workspace.m_DataSources.GetCount() << "������Դ" << endl;
	cout << workspace.m_MapStorages.GetCount() << "�ŵ�ͼ" << endl;
	cout << endl;

	UGDataSource *dataSource = workspace.GetDataSource(0);
	if (!dataSource->Open())
	{
		cout << "����Դ��ʧ�ܣ����ܱ���������ռ�ã�" << endl;
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
	}
	cout << "������Ϊ" << i << "�����ݼ���" << (dataSet->IsVector() ? "��" : "����") << "ʸ����" << endl;

	UGDatasetVector *dataSetVector = (UGDatasetVector *)dataSet;
	cout << "�������Ϊ��" << dataSetVector->GetObjectCount() << endl;
	cout << "��¼������Ϊ��" << dataSetVector->GetRecordsetCount() << endl;
	UGQueryDef query;
	UGRecordset *recordset = dataSetVector->Query(query);
	cout << "��ѯ���ݼ�����¼����Ϊ��" << recordset->GetRecordCount() << endl;
	cout << "��¼������Ϊ��" << dataSetVector->GetRecordsetCount() << endl;
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

	UGPoint2D point(0, 1);
	cout << "�޸����꣬" << (pRegion->SetPoint(1, point) ? "�ɹ�" : "ʧ��") << endl;
	cout << "�޸ĺ�����ֱ�Ϊ��" << endl;
	for (i = 0; i < pRegion->GetSubPntCount(0); i++)
		cout << '(' << pPoint2D[i].x << ", " << pPoint2D[i].y << ')' << endl;

	// �����ݼ�������һ��һ���ڴ渱��
	// ��ѯ�õ���¼�����ֻ�����һ�������ڴ渱��
	// �õ���ָ��Ҳ��ָ�����������
	// һ�������ڶ�Ӧ�ļ�¼������Edit֮��ſ��Ա��޸�
	// ����SetGeometry���޸�һ������
	// ����Update��һ������д���ļ�
	recordset->Edit();
	recordset->SetGeometry(*pRegion);
	cout << "���¼�¼�������Ϊ��" << (recordset->Update() ? "�ɹ�" : "ʧ��") << endl;

	delete pGeometry;
}

void testJson()
{
	int iValue;
	double fTimeout;
	std::string strValue;
	neb::CJsonObject oJson("{\"refresh_interval\":60,"
		"\"test_float\":[18.0, 10.0, 5.0],"
		"\"timeout\":12.5,"
		"\"dynamic_loading\":["
		"{"
		"\"so_path\":\"plugins/User.so\", \"load\":false, \"version\":1,"
		"\"cmd\":["
		"{\"cmd\":2001, \"class\":\"neb::CmdUserLogin\"},"
		"{\"cmd\":2003, \"class\":\"neb::CmdUserLogout\"}"
		"],"
		"\"module\":["
		"{\"path\":\"im/user/login\", \"class\":\"neb::ModuleLogin\"},"
		"{\"path\":\"im/user/logout\", \"class\":\"neb::ModuleLogout\"}"
		"]"
		"},"
		"{"
		"\"so_path\":\"plugins/ChatMsg.so\", \"load\":false, \"version\":1,"
		"\"cmd\":["
		"{\"cmd\":2001, \"class\":\"neb::CmdChat\"}"
		"],"
		"\"module\":[]"
		"}"
		"]"
		"}");
	std::cout << oJson.ToString() << std::endl;
	std::cout << "-------------------------------------------------------------------" << std::endl;
	std::cout << oJson["dynamic_loading"][0]["cmd"][1]("class") << std::endl;
	oJson["dynamic_loading"][0]["cmd"][0].Get("cmd", iValue);
	std::cout << "iValue = " << iValue << std::endl;
	oJson["dynamic_loading"][0]["cmd"][0].Replace("cmd", -2001);
	oJson["dynamic_loading"][0]["cmd"][0].Get("cmd", iValue);
	std::cout << "iValue = " << iValue << std::endl;
	oJson.Get("timeout", fTimeout);
	std::cout << "fTimeout = " << fTimeout << std::endl;
	oJson["dynamic_loading"][0]["module"][0].Get("path", strValue);
	std::cout << "strValue = " << strValue << std::endl;
	std::cout << "-------------------------------------------------------------------" << std::endl;
	oJson.AddEmptySubObject("depend");
	oJson["depend"].Add("nebula", "https://github.com/Bwar/Nebula");
	oJson["depend"].AddEmptySubArray("bootstrap");
	oJson["depend"]["bootstrap"].Add("BEACON");
	oJson["depend"]["bootstrap"].Add("LOGIC");
	oJson["depend"]["bootstrap"].Add("LOGGER");
	oJson["depend"]["bootstrap"].Add("INTERFACE");
	oJson["depend"]["bootstrap"].Add("ACCESS");
	std::cout << oJson.ToString() << std::endl;
	std::cout << "-------------------------------------------------------------------" << std::endl;
	std::cout << oJson.ToFormattedString() << std::endl;

	std::cout << "-------------------------------------------------------------------" << std::endl;
	neb::CJsonObject oCopyJson = oJson;
	if (oCopyJson == oJson)
	{
		std::cout << "json equal" << std::endl;
	}
	oCopyJson["depend"]["bootstrap"].Delete(1);
	oCopyJson["depend"].Replace("nebula", "https://github.com/Bwar/CJsonObject");
	std::cout << oCopyJson.ToString() << std::endl;
	std::cout << "-------------------------key traverse------------------------------" << std::endl;
	std::string strTraversing;
	while (oJson["dynamic_loading"][0].GetKey(strTraversing))
	{
		std::cout << "traversing:  " << strTraversing << std::endl;
	}
	std::cout << "---------------add a new key, then key traverse---------------------" << std::endl;
	oJson["dynamic_loading"][0].Add("new_key", "new_value");
	while (oJson["dynamic_loading"][0].GetKey(strTraversing))
	{
		std::cout << "traversing:  " << strTraversing << std::endl;
	}

	std::cout << oJson["test_float"].GetArraySize() << std::endl;
	float fTestValue = 0.0;
	for (int i = 0; i < oJson["test_float"].GetArraySize(); ++i)
	{
		oJson["test_float"].Get(i, fTestValue);
		std::cout << fTestValue << std::endl;
	}
	oJson.AddNull("null_value");
	std::cout << oJson.IsNull("test_float") << "\t" << oJson.IsNull("null_value") << std::endl;
	oJson["test_float"].AddNull();
	std::cout << oJson.ToString() << std::endl;
}

void testPolyJson()
{
	ifstream fin("D:\\_save\\satellite_seg\\results\\1_poly_1.json");
	if (!fin.is_open())
	{
		cout << "�ļ���ʧ�ܣ�" << endl;
	}
	stringstream buffer;
	buffer << fin.rdbuf();
	string text(buffer.str());

	neb::CJsonObject oJson;
	oJson.Parse(text);
	//cout << oJson.ToFormattedString();
	cout << oJson.IsArray() << endl;
	cout << oJson.GetArraySize() << endl;
	cout << oJson[0].IsArray() << endl;
	cout << oJson[0].GetArraySize() << endl;
	cout << oJson[0][0].IsArray() << endl;
	cout << oJson[0][0].GetArraySize() << endl;
	float x, y;
	oJson[0][0].Get(0, x);
	oJson[0][0].Get(1, y);
	cout << x << ' ' << y << endl;

	// CJsonObject��Array��������ʵ�֣������ٶ���
	int i, j;
	vector<vector<vector<float>>> plist;

	clock_t t = clock();
	/***** ���㲿�� *****/
	for (i = 0; i < oJson.GetArraySize(); i++)
	{
		plist.push_back({});
		for (j = 0; j < oJson[i].GetArraySize(); j++)
		{
			plist[i].push_back({});
			oJson[i][j].Get(0, x);
			oJson[i][j].Get(1, y);
			plist[i][j].push_back(x);
			plist[i][j].push_back(y);
		}
	}
	/********************/
	cout << "Json������ʱ" << (clock() - t) * 1.0 / CLOCKS_PER_SEC << 's' << endl; // 109s, 79s

	t = clock();
	/***** ���㲿�� *****/
	for (i = 0; i < plist.size(); i++)
	{
		for (j = 0; j < plist[i].size(); j++)
		{
			x = plist[i][j][0];
			y = plist[i][j][1];
		}
	}
	/********************/
	cout << "vector������ʱ" << (clock() - t) * 1.0 / CLOCKS_PER_SEC << 's' << endl; // <0.1s
}

int Json2Vector(const string filename, vector<vector<vector<float>>> &plist)
{
	ifstream fin(filename);
	if (!fin.is_open())
		return -1;

	stringstream buffer;
	buffer << fin.rdbuf();
	string text(buffer.str());

	neb::CJsonObject oJson;
	oJson.Parse(text);

	// TODO: �˴�Ӧ����ʽ
	float x, y;
	int i, j;
	for (i = 0; i < oJson.GetArraySize(); i++)
	{
		plist.push_back({});
		for (j = 0; j < oJson[i].GetArraySize(); j++)
		{
			plist[i].push_back({});
			oJson[i][j].Get(0, x);
			oJson[i][j].Get(1, y);
			plist[i][j].push_back(x);
			plist[i][j].push_back(y);
		}
	}
	return 0;
}

bool Vector2Region(const vector<vector<float>> &polygon, UGGeoRegion *region)
{
	if (!region)
		region = new UGGeoRegion;

	int i;
	vector<UGPoint2D> points;
	for (i = 0; i < polygon.size(); i++)
		points.push_back({ polygon[i][0],polygon[i][1] });
	UGGeoRegion *subRegion = NULL;
	cout << (region->GetSub(0, subRegion)?1:0) << endl;
	cout << region->GetSubCount() << endl;
	return region->InsertSub(0, points.data(), points.size());// �׳��쳣
}

void testV2R()
{
	vector<vector<vector<float>>> plist;
	if (Json2Vector("D:\\_save\\satellite_seg\\results\\1_small_pred_poly_1.json", plist) < 0)
		cout << "ת��ʧ��" << endl;
	UGGeoRegion *region = NULL;
	cout << Vector2Region(plist[0], region) << endl;
}

int main()
{
	int n = 0;
	cout << "������Զ���";
	while (n < 1 || n > 4)
		cin >> n;
	cin.clear();
	cin.ignore();

	switch (n)
	{
	case 1:
		testSuperMap();
		break;
	case 2:
		testJson();
		break;
	case 3:
		testPolyJson();
		break;
	case 4:
		testV2R();
		break;
	}
	return 0;
}