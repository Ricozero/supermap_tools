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

	cout << "�����ռ乲����" << workspace.m_MapStorages.GetCount() << "�ŵ�ͼ" << endl;

	return 0;

}