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

	cout << "工作空间共包含" << workspace.m_MapStorages.GetCount() << "张地图" << endl;

	return 0;

}