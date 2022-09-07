#include <stdlib.h>
#include <stdio.h>
#include <map>
#include <iostream>


using point_id = std::pair<int, int>;
using map_t = std::map<std::pair<int, int>, int>;

int find_point(map_t point_map, int x, int y);
void add_point(map_t &point_map, int x, int y, int col);

int main()
{
    int number_of_requests = 0;
    int kind_of_request = 0;
    scanf("%d", &number_of_requests);
    
    
    map_t point_map{};
    int counter = 0; 

    int x, y, col;
    for (int i = 0; i < number_of_requests; i++)
    {
        // scanf("%d", &kind_of_request);
        std::cin >> kind_of_request;
        
        if (kind_of_request == 1) {
            //  scanf("%d %d %d", &x, &y, &col);
            std::cin >> x >> y >> col;
            add_point(point_map, x, y, col);
        }
        else if (kind_of_request == 2) {
            // scanf("%d %d ", &x, &y);
            std::cin >> x >> y;
            col = find_point(point_map, x, y);
            std::cout << col << std::endl;
            // printf("%c", col);
        }
        else {
            std::cout << "INVALID YOU`RE DUMMY BOOOOY" << std::endl;
        }
        // switch (kind_of_request)
        // {
        //     case 1:
        //         scanf("%d %d %d", &x, &y, &col);
        //         add_point(point_map, x, y, col);
        //         break;

        //     case 2:
        //         scanf("%d %d ", &x, &y);
        //         col = find_point(point_map, x, y);
        //         std::cout << "AAAAAAAAAAAAAAAA" << std::endl;
        //         printf("%c", col);
        //         break;

        //     default:
        //         printf("invalid input");
        //         break;
        // }
    }
    return 0;
}
//----------------------------------------------------------
void add_point(map_t &point_map, int x, int y, int col)
{
    point_id point{x, y};
    point_map.insert({point, col});
}
//--------------------------------------------------------------
int find_point(map_t point_map, int x, int y)
{   
    point_id point{x, y};
    auto it = point_map.find(point);

    if (it != point_map.end()) {
        // std::cout << it->first << *it->second << std::endl;
        return it->second;
    }
    
    std::cout << "not found" << std::endl;
    return 0; 

}