# Arena Of Archer

### A RPG Game made with SDL2 and C++
### Introduction video: https://www.youtube.com/watch?v=_WKrTkLdPdo

## Build
g++ -ILibSdl2/SDL2_image-2.0.3/include -ILibSdl2/SDL2-2.0.8/include -ILibSdl2/SDL2_ttf-2.0.14/include -LLibSdl2/Dll/X86 -o arenaofarcher *.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf


## Phân công công việc

### Nguyễn Minh Quân: Xử lý nhân vật, đường đạn, lưu trữ dữ liệu, các thông số game: hp, level, score

### Đinh Trung Kiên: Xử lí hiển thị text, xử lí các menu và giao diện, làm video demo

### Trần Hữu Thành: Xử lí collision: map, nhân vật, đạn bắn,...

