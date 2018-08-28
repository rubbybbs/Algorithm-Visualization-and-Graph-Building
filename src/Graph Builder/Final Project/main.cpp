#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>


using namespace std;


class movie {

public:
	string Name;
	vector<string> Director;
	vector<string> Actor;
	vector<string> Type;
	vector<string> Nation;


};						//定义电影类，作为一个结点。

class Edge {

public:
	int source;
	int target;
	int value;
	string source_s;
	string target_s;
};

vector<movie> Node_origin;	//结点集合
vector<Edge> Edge_origin;	//边集合

int main()
{
	ifstream inFile("movies.csv", ios::in);
	string lineStr;
	while (getline(inFile, lineStr))
	{
		// 存储进vector中  
		stringstream ss(lineStr);
		string str;
		movie tmpCsvIn;
		int tmp = 0;
		// 按照逗号分隔  
		while (getline(ss, str, ','))
		{
			if (tmp == 0)
				tmpCsvIn.Name = str;
			if (tmp == 1)
			{
				vector <int> pos;
				for (int i = 0; i < str.size(); i++)
				{
					if (str[i] == ';')
						pos.push_back(i);
				}
				pos.push_back(str.size());
				if (pos.size() == 1)
					tmpCsvIn.Director.push_back(str);
				else
				{
					tmpCsvIn.Director.push_back(str.substr(0, pos[0]));
					for (int i = 0; i < pos.size() - 1; i++)
					{
						tmpCsvIn.Director.push_back(str.substr(pos[i] + 1, pos[i + 1] - pos[i] - 1));
					}
				}
			}
			if (tmp == 2)
			{
				vector <int> pos;
				for (int i = 0; i < str.size(); i++)
				{
					if (str[i] == ';')
						pos.push_back(i);
				}
				pos.push_back(str.size());
				if (pos.size() == 1)
					tmpCsvIn.Actor.push_back(str);
				else
				{
					tmpCsvIn.Actor.push_back(str.substr(0, pos[0]));
					for (int i = 0; i < pos.size() - 1; i++)
					{
						tmpCsvIn.Actor.push_back(str.substr(pos[i] + 1, pos[i + 1] - pos[i] - 1));
					}
				}
			}

			if (tmp == 3)
			{
				vector <int> pos;
				for (int i = 0; i < str.size(); i++)
				{
					if (str[i] == ';')
						pos.push_back(i);
				}
				pos.push_back(str.size());
				if (pos.size() == 1)
					tmpCsvIn.Type.push_back(str);
				else
				{
					tmpCsvIn.Type.push_back(str.substr(0, pos[0]));
					for (int i = 0; i < pos.size() - 1; i++)
					{
						tmpCsvIn.Type.push_back(str.substr(pos[i] + 1, pos[i + 1] - pos[i] - 1));
					}
				}
			}


			if (tmp == 4)
			{
				vector <int> pos;
				for (int i = 0; i < str.size(); i++)
				{
					if (str[i] == ';')
						pos.push_back(i);
				}
				pos.push_back(str.size());
				if (pos.size() == 1)
					tmpCsvIn.Nation.push_back(str);
				else
				{
					tmpCsvIn.Nation.push_back(str.substr(0, pos[0]));
					for (int i = 0; i < pos.size() - 1; i++)
					{
						tmpCsvIn.Nation.push_back(str.substr(pos[i] + 1, pos[i + 1] - pos[i] - 1));
					}
				}
			}

			tmp++;
		}
		Node_origin.push_back(tmpCsvIn);
	}

	for (int i = 1; i < Node_origin.size() - 1; i++)
	{
		for (int j = i + 1; j < Node_origin.size(); j++)
		{
			int flag1 = 0;
			int flag2 = 0;
			int flag3 = 0;
			int flag4 = 0;
			Edge *tmpEdge = nullptr;
			for(int m = 0; m< Node_origin[i].Type.size(); m++)
				for (int n = 0; n < Node_origin[j].Type.size(); n++)
				{

					if (Node_origin[i].Type[m] == Node_origin[j].Type[n])
					{
						flag1++;
					}
				}									//有相同类型的处理方式
			for (int a = 0; a < Node_origin[i].Director.size(); a++)
				for (int b = 0; b < Node_origin[j].Director.size(); b++)
				{
					if (Node_origin[i].Director[a] == Node_origin[j].Director[b])
						flag2++;
				}									//有相同导演的处理方式

			for (int a = 0; a < min(2, (int)Node_origin[i].Actor.size()); a++)
				for (int b = 0; b < min(2, (int)Node_origin[j].Actor.size()); b++)
				{
					if (Node_origin[i].Actor[a] == Node_origin[j].Actor[b])
						flag3++;
				}								//有相同演员的处理方式


			for (int a = 0; a < Node_origin[i].Nation.size(); a++)
				for (int b = 0; b < Node_origin[j].Nation.size(); b++)
				{
					if (Node_origin[i].Nation[a] == Node_origin[j].Nation[b])
						flag4++;
				}								//有相同国家的处理方式
			if (flag1 + flag2 + flag3 + flag4 >= 4)
			{
				if (tmpEdge == nullptr)
					tmpEdge = new Edge();
				tmpEdge->source = i - 1;
				tmpEdge->target = j - 1;
				tmpEdge->source_s = Node_origin[i].Name;
				tmpEdge->target_s = Node_origin[j].Name;
				tmpEdge->value = 50 - flag1 * 4 - flag2 * 3 - flag3 * 2 - flag4 * 3;
			}
			if (tmpEdge != nullptr)
			{
				Edge_origin.push_back(*tmpEdge);
				delete tmpEdge;
			}

		}
	}

	
	ofstream ofile;

	ofile.open("Edge1.csv", ios::out | ios::trunc);       //判断.csv文件是否存在，不存在则建立

	ofile << "source" << ',' << "target" << ',' << "value" << ',' << "sourceI" << ',' << "targetI" << ',' << "flag" <<  endl;
	for (int i = 0; i < Edge_origin.size(); i++)
	{
		ofile << Edge_origin[i].source_s << ',' << Edge_origin[i].target_s << ',' << Edge_origin[i].value << ',' << Edge_origin[i].source << ',' << Edge_origin[i].target << ',' << "0" << endl;
	}
	

	
	return 0;
}