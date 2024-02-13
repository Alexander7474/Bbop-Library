#include "../../../include/BBOP/Performance/benchmark.h"

vector<Sprite> spriteList;
void bbopBenchMark(Scene& sceneToUse)
{
  spriteList.push_back(Sprite("nope"));
  sceneToUse.Use();
  for(unsigned int i = 0; i< spriteList.size(); i ++)
    sceneToUse.Draw(spriteList[i]);
  cout << "BENCHMARK RUNNING" << endl << "Number of sprite: " << spriteList.size() << endl;
}
