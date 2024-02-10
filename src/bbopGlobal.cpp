#include "../include/bbopGlobal.h"
#include <GLFW/glfw3.h>

int BIBIBOP_SHADER_MODE_TEXTURE = 0;
int BIBIBOP_SHADER_MODE_COLOR = 1;
int BIBIBOP_SHADER_MODE_MIX = 2;
Vector2i BIBIBOP_WINDOW_SIZE(956, 1044); 

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

