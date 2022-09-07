#include <stdlib.h>
#include <stdio.h>
#include <unordered_map>



using point_id = std::pair<int, int>;
using map_t = std::unordered_map<std::pair<int, int>, int>;

int main()
{
    int number_of_requests = 0;
    int kind_of_request = 0;
    scanf("%d", &number_of_requests);
    
    
    std::unordered_map<std::pair<int, int>, int> point_map{{{-1, -1}, -1}};
    int counter = 0; 

    int x, y, col;
    for (int i = 0; i < number_of_requests; i++)
    {
        scanf("%d", &kind_of_request);
        switch (kind_of_request)
        {
            case 1:
                scanf("%d %d %d", &x, &y, &col);
                add_point(point_map, x, y, col);
                break;

            case 2:
                scanf("%d %d", &x, &y);
                int color = find_point(point_map, x, y);
                printf("%c", color);
                break;

            default:
                printf("invalid input");
                break;
        }
    }
    return 0;
}
//----------------------------------------------------------
void add_point(map_t point_map, int x, int y, int col)
{
    point_id point{x, y};
    point_map.insert({point, col});
}
//--------------------------------------------------------------
int find_point(map_t point_map, int x, int y)
{
    point_id point{x, y};
    return point_map.find(point)->second;
}