#include <stdio.h>
#include <map>
#include <string>

int main(int argc, char const *argv[])
{
    std::map<std::string, int> testMap;
    int i = testMap["1"];
    printf("map size:%d\n", testMap.size());
    i = testMap["1"];
    printf("map size:%d\n", testMap.size());
    printf("map i:%d\n", i);
    
    return 0;
}
