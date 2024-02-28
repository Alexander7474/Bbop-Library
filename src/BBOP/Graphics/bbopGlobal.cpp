#include "../../../include/BBOP/Graphics/bbopGlobal.h"

using namespace std;

int BBOP_SHADER_MODE_TEXTURE = 0;
int BBOP_SHADER_MODE_COLOR = 1;
int BBOP_SHADER_MODE_MIX = 2;
Vector2i BBOP_WINDOW_SIZE(1920, 1080); 

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods){
  
}

// Lecture du fichier text et sortie en string
string getFileData(const char* filename)
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
