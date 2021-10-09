#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <unistd.h>
void add(std::string s)
{
	std::ofstream data;
	data.open("data.txt",std::ios::app);
	for(int i=0;i<s.length();i++)
	{
		if(s[i]==',') data<<std::endl;
		else data<<s[i];
	}
	data.close();	
}
void show()
{
	int counter=1;
	std::string line;
	std::ifstream data;
	data.open("data.txt");
	while(data>>line)
	{
		std::cout<<counter<<". "<<line<<std::endl;
		counter++;
	}
	data.close();
}
void remove(int index)
{
	int counter=1;
	std::string line,content;
	std::ifstream datar;
	datar.open("data.txt");
	while(datar>>line)
	{
		if(counter==index)
		{
			counter++;
			continue;
		}
		content+=line;
		content+='\n';
		counter++;
	}
	datar.close();
	std::ofstream dataw;
	dataw.open("data.txt");
	dataw<<content;
	dataw.close();

}
void help()
{
	std::cout<<"-a adds items to the list, seperate multipile values with commas"<<std::endl;
	std::cout<<"-s shows all the items in the list"<<std::endl;
	std::cout<<"-r removes items in the list by specifying the index, seperate multiple values with commas"<<std::endl;
	std::cout<<"-h display this help message"<<std::endl;
}
int main(int argc,char* argv[])
{
	int run=0;
	char ch;
	while((ch=getopt(argc,argv,"a: s r: h"))!=EOF)
	{
		run=1;
		switch(ch)
		{
			case 'a':
				add(optarg);
				break;
			case 's':
				show();
				break;
			case 'r':
				for(int i=0;i<strlen(optarg);i++)
				{
					if(optarg[i]==',') continue;
					remove(atoi(optarg));
				}
				std::cout<<"Updated list:"<<std::endl;
				show();
				break;
			case 'h':
				help();
				break;
			default:
				return 1;
		}
	}
	if(run==0) help();
	return 0;
}
