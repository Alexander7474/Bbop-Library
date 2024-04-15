#include "../../../include/BBOP/Graphics/bbopGlobal.h"

using namespace std;

Vector2i BBOP_WINDOW_SIZE(0, 0); 
Vector2i BBOP_WINDOW_RESOLUTION(0, 0); 

// Lecture du fichier text et sortie en string
string bbopGetFileData(const char* filename)
{
	ifstream in(filename, ios::binary);
	if (in)
	{
		string contents;
		in.seekg(0, ios::end);
		contents.resize(in.tellg());
		in.seekg(0, ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}
