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
	//UGString workspacePath = _U("D:\\Program Files\\SuperMap iDesktop 9D\\SampleData\\China\\China100\\China.smwu");
	//UGString workspacePath = _U("a.smwu");
	UGString workspacePath = _U("H:\\Tiexin-data\\tr.smwu");
	if (!workspace.Open(workspacePath))
	{
		cout << "工作空间打开失败，可能被其他程序占用！" << endl;
		return;
	}
	cout << "工作空间共包含：" << endl;
	cout << workspace.m_DataSources.GetCount() << "个数据源" << endl;
	cout << workspace.m_MapStorages.GetCount() << "张地图" << endl;
	cout << endl;

	UGDataSource *dataSource = workspace.GetDataSource(0);
	if (!dataSource->Open())
	{
		cout << "数据源打开失败，可能被其他程序占用！" << endl;
		return;
	}
	cout << "打开第一个数据源，共包含" << dataSource->GetDatasetCount() << "个数据集" << endl;
	cout << "各个数据集信息：" << endl;
	UGDatasets *datasets = dataSource->GetDatasets();
	UGDataset *dataset;
	int i;
	cout << "编号\t类型\t名称" << endl;
	for (i = 0; i < dataSource->GetDatasetCount(); i++)
	{
		dataset = (*datasets)[i];
		cout << i << "\t";
		wcout.imbue(locale("chs"));
		wcout << dataset->GetType() <<"\t"
			<< dataset->GetName().Cstr()
			<< endl;
	}
	/*
	i = 5;
	dataset = dataSetsP[i];
	if (!dataSet->Open())
	{
		cout << "数据集打开失败！" << endl;
		return;
	}
	cout << "打开索引为" << i << "的数据集（" << (dataSet->IsVector() ? "是" : "不是") << "矢量）" << endl;

	UGDatasetVector *dataSetVector = (UGDatasetVector *)dataSet;
	cout << "对象个数为：" << dataSetVector->GetObjectCount() << endl;
	cout << "记录集个数为：" << dataSetVector->GetRecordsetCount() << endl;
	UGQueryDef query;
	UGRecordset *recordset = dataSetVector->Query(query);
	cout << "查询数据集，记录个数为：" << recordset->GetRecordCount() << endl;
	cout << "记录集个数为：" << dataSetVector->GetRecordsetCount() << endl;
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

	UGPoint2D point(0, 1);
	cout << "修改坐标，" << (pRegion->SetPoint(1, point) ? "成功" : "失败") << endl;
	cout << "修改后坐标分别为：" << endl;
	for (i = 0; i < pRegion->GetSubPntCount(0); i++)
		cout << '(' << pPoint2D[i].x << ", " << pPoint2D[i].y << ')' << endl;

	// 打开数据集后生成一个一级内存副本
	// 查询得到记录集后又会生成一个二级内存副本
	// 得到的指针也是指向二级副本的
	// 一级副本在对应的记录集调用Edit之后才可以被修改
	// 调用SetGeometry以修改一级副本
	// 调用Update将一级副本写回文件
	recordset->Edit();
	recordset->SetGeometry(*pRegion);
	cout << "更新记录集，结果为：" << (recordset->Update() ? "成功" : "失败") << endl;

	delete pGeometry;
	*/
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
		cout << "文件打开失败！" << endl;
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

	// CJsonObject的Array是用链表实现，遍历速度慢
	int i, j;
	vector<vector<vector<float>>> plist;

	clock_t t = clock();
	/***** 计算部分 *****/
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
	cout << "Json遍历耗时" << (clock() - t) * 1.0 / CLOCKS_PER_SEC << 's' << endl; // 109s, 79s

	t = clock();
	/***** 计算部分 *****/
	for (i = 0; i < plist.size(); i++)
	{
		for (j = 0; j < plist[i].size(); j++)
		{
			x = plist[i][j][0];
			y = plist[i][j][1];
		}
	}
	/********************/
	cout << "vector遍历耗时" << (clock() - t) * 1.0 / CLOCKS_PER_SEC << 's' << endl; // <0.1s
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

	// TODO: 此处应检查格式
	// TODO: 考虑给CJsonObject添加迭代方法，否则遍历太慢
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

UGGeoRegion *Vector2Region(const vector<vector<float>> &polygon)
{
	int i;
	vector<UGPoint2D> points;
	UGGeoRegion *region = new UGGeoRegion;

	for (i = 0; i < polygon.size(); i++)
		points.push_back({ polygon[i][0],polygon[i][1] });
	UGGeoRegion *subRegion = NULL;
	// 用InsertSub可以插入指定位置，但是无子对象时会因为找不到子对象而抛出异常
	region->AddSub(points.data(), points.size());
	return region;
}

void testV2R()
{
	vector<vector<vector<float>>> plist;
	if (Json2Vector("D:\\_save\\satellite_seg\\results\\1_small_pred_poly_1.json", plist) < 0)
		cout << "转换失败" << endl;
	UGGeoRegion *region = Vector2Region(plist[0]);
	cout << region << endl;
}

// 返回时已打开
UGWorkspace *NewWorkspace(const wchar_t *filename)
{
	UGWorkspace *ws = new UGWorkspace;
	UGWorkspaceConnection wc;
	wc.m_strServer = filename;	// wstring不能直接转；可以是相对或绝对路径
	wc.m_nVersion = UG_WORKSPACE_VERSION_20120328;
	wc.m_nWorkspaceType = UGWorkspace::WS_Version_SMWU;
	// Save只在已有文件时使用
	// SaveAs后ws表示的是新建的文件
	if (!ws->SaveAs(wc))
	{
		delete ws;
		return NULL;
	}
	return ws;
}

// 返回时已连接
UGDataSource *NewDataSource(const wchar_t *filename)
{
	UGDataSource *ds = UGDataSourceManager::CreateDataSource(UGEngineType::UDB);
	if (!ds)
		return NULL;
	UGDsConnection &con = ds->GetConnectionInfo();
	con.m_strServer = filename;
	//con.m_strAlias = filename;	// 只决定当次打开时的显示名称
	//con.m_bExclusive = true;		// 独占打开
	if (!ds->Create())
	{
		delete ds;
		return NULL;
	}
	return ds;
}

UGDatasetVector *NewDatasetVector(UGDataSource *ds, UGDataset::DatasetType type, const wchar_t *name)
{
	if (!ds)
		return NULL;
	UGDatasetVectorInfo dvi;
	dvi.m_nType = type;
	dvi.m_strName = name;
	return ds->CreateDatasetVector(dvi);
}

void testNew()
{
	UGWorkspace *ws = NewWorkspace(L"a.smwu");
	cout << "创建工作空间：" << (ws ? "成功" : "失败") << endl;
	UGDataSource *ds = NewDataSource(L"a.udb");
	cout << "创建数据源：" << (ds ? "成功" : "失败") << endl;
	//ds->Close();	// 因为独占，需要先关闭
	// 如何将数据源连接到工作空间并保存？
	//cout<<int(ws->OpenDataSource(ds->GetConnectionInfo()));

	UGDatasetVector *dv = NewDatasetVector(ds, UGDataset::Region, L"测试");
	cout << "创建面数据集：" << (dv ? "成功" : "失败") << endl;

	if (dv)
	{
		vector<vector<vector<float>>> plist;
		if (Json2Vector("D:\\_save\\satellite_seg\\results\\1_small_pred_poly_1.json", plist) < 0)
			cout << "转换失败" << endl;
		UGGeoRegion *region;
		UGGeometry *geo = NULL;
		UGQueryDef query;
		UGRecordset *rs = dv->Query(query);
		int i;
		//cout << (rs->GetGeometry(geo) ? 1 : 0) << ' ';
		//cout << geo << endl;
		for (i = 0; i < plist.size(); i++)
		{
			region = Vector2Region(plist[i]);
			// AddNew不需要先调用Edit
			// AddNew后recordset会自动更新
			rs->AddNew(region);
			// 每次AddNew都应调用Update
			delete region;
			rs->Update();
			region = NULL;
			// 测试输出
			// 如果写成(UGGeometry *)region，类型转换形成一个临时变量
			// 所以引用传进去是临时变量的引用，引用失效，会报错
			//cout << (rs->GetGeometry(geo) ? 1 : 0) << ' ';
			//cout << geo << endl;
		}
	}
}

UGWorkspace *OpenWorkspace(const wchar_t *filename)
{
	UGWorkspace *ws = new UGWorkspace;
	// 进行成员变量的设置，后面调用Save即可保存
	ws->m_WorkspaceConnection.m_strServer = filename;
	ws->m_WorkspaceConnection.m_nVersion = UG_WORKSPACE_VERSION_20120328;
	ws->m_WorkspaceConnection.m_nWorkspaceType = UGWorkspace::WS_Version_SMWU;
	ws->m_WorkspaceConnection.m_bFailIfExists = false;
	if (!ws->Open(filename))
	{
		delete ws;
		return NULL;
	}
	return ws;
}

// *此函数不可用*
// 意图是数据源和工作空间未建立联系时直接打开数据源
// 结果是无法单独打开数据源
UGDataSource *OpenDataSource(const wchar_t *filename)
{
	UGDataSource *ds = new UGDataSource;
	UGDsConnection &con = ds->GetConnectionInfo();
	con.m_nType = UGEngineType::UDB;
	con.m_strServer = filename;
	//con.m_strAlias = L"a";
	cout << (ds->Open() ? 1 : 0) << endl;
	cout << (ds->IsCanConnect() ? 1 : 0) << endl;
	if (!ds->Connect())
	{
		delete ds;
		return NULL;
	}
	else
		return ds;
}

void testSave()
{
	UGDataSource *ds = NULL;
	UGWorkspace *ws = OpenWorkspace(L"a.smwu");
	UGDsConnection con;
	con.m_nType = UGEngineType::UDB;
	con.m_strServer = L"a.udb";
	//con.m_strAlias = L"";	//决定了显示名称
	cout << "打开数据源：" << ((ds = ws->OpenDataSource(con)) ? "成功" : "失败") << endl;
	
	//cout << (ws->IsModified() ? 1 : 0) << endl;
	//ws->SetModifiedFlag(true);
	ws->m_WorkspaceConnection.m_strServer = L"a.smwu";
	ws->m_WorkspaceConnection.m_nVersion = UG_WORKSPACE_VERSION_20120328;
	ws->m_WorkspaceConnection.m_nWorkspaceType = UGWorkspace::WS_Version_SMWU;
	ws->m_WorkspaceConnection.m_bFailIfExists = false;
	// Save的逻辑是，如果bModified是false，不管m_WorkspaceConnection的信息，直接返回1
	// 如果bModified是true，通过m_WorkspaceConnection的信息保存
	cout << "保存工作空间：" << (ws->Save() ? "成功" : "失败") << endl;
}

void testRaster()
{
	UGWorkspace* ws = OpenWorkspace(_U("H:\\Tiexin-data\\tr.smwu"));
	UGDataSource* dataSource = ws->GetDataSource(0);
	UGDatasets* datasets = dataSource->GetDatasets();
	UGDataset* dataset = (*datasets)[0];
	UGDatasetRaster* rds = (UGDatasetRaster*)dataset;
	UGDatasetRasterInfo* rdsi = rds->GetInfo();
	cout << rds->GetBandCount() << endl;
	cout << rds->GetColorSpace() << endl;
	cout << rds->GetWidth() << " " << rds->GetHeight() << endl;
	rds->Open();
	int x = 0, y = 0;
	UGColor c;
	cout << "像素测试：" << endl;
	while (1)
	{
		cin >> x >> y;
		// 当0<=x<width， 0<=y<height，返回max int，其余情况返回0
		c = rds->GetPixel(x, y);
		cout << (c>>24) << " " << (c<<8>>24) << " " << (c<<16>>24) << " " << (c<<24>>24) << endl;
		UGPoint2D p;
		rds->ImgToXY(UGPoint(x, y), p);
		cout << p.x << " " << p.y << endl;
		cout << endl;
	}
	return;
}

int main()
{
	int n = 0;
	while (n < 1 || n > 7)
	{
		cout << "输入测试对象：";
		cin >> n;
	}
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
	case 5:
		testNew();
		break;
	case 6:
		testSave();
		break;
	case 7:
		testRaster();
		break;
	}
	return 0;
}