#include "../../../include/BBOP/Performance/benchmark.h"
#include <GLFW/glfw3.h>
#include <random>

vector<Sprite> spriteList;
vector<RectangleShape> rectList;
double lastTime;
random_device rd;
mt19937 gen(rd());
uniform_int_distribution<int> distribx(0, BBOP_WINDOW_SIZE.x);
uniform_int_distribution<int> distriby(0, BBOP_WINDOW_SIZE.y);
uniform_int_distribution<int> distribs(0,255);

bool bbopBenchMark(Scene& sceneToUse)
{
  spriteList.push_back(Sprite("nope"));
  rectList.push_back(RectangleShape());
  sceneToUse.Use();
  lastTime = glfwGetTime();
  for(unsigned int i = 0; i< spriteList.size(); i ++){
    spriteList[i].setPosition(Vector2f(distribx(gen),distriby(gen)));
    spriteList[i].setSize(Vector2f(distribs(gen),distribs(gen)));
    sceneToUse.Draw(spriteList[i]);
    rectList[i].setColor(Vector3i(distribs(gen),distribs(gen),distribs(gen)));
    rectList[i].setPosition(Vector2f(distribx(gen),distriby(gen)));
    rectList[i].setSize(Vector2f(distribs(gen),distribs(gen)));
    sceneToUse.Draw(rectList[i]);
  }
  cout << "BENCHMARK RUNNING" << endl << "Number of sprite: " << spriteList.size()*2 << " delta time: " << glfwGetTime()-lastTime << endl;
  if (glfwGetTime() - lastTime > 1.0){
    cout << "BENCHMARK FINISHED" << endl << "Total of sprite: " << spriteList.size()*2 << endl;
    return true;
  }
  return false;
}
