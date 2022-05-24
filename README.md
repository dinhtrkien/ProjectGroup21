# Arena Of Archer

### A RPG Game made with SDL2 and C++
### Introduction video: https://www.youtube.com/watch?v=_WKrTkLdPdo

## Build
g++ -IMinGW/SDL2/include/SDL2 -IMinGW/SDL2_image/include/SDL2 -IMinGW/SDL2_ttf/include/SDL2 -Iheaders -LMinGW/SDL2/lib -LMinGW/SDL2_image/lib -LMinGW/SDL2_ttf/lib src/*.cpp -lSDL2 -lSDL2_image -lSDL2_ttf -lmingw32 -o arenaofarche


## Phân công công việc

### Nguyễn Minh Quân: Xử lý nhân vật, đường đạn, lưu trữ dữ liệu, các thông số game: hp, level, score

### Đinh Trung Kiên: Xử lí hiển thị text, xử lí các menu và giao diện, làm video demo

### Trần Hữu Thành: Xử lí collision: map, nhân vật, đạn bắn,...

