# Arena Of Archer

### A RPG Game made with SDL2 and C++
### Introduction video: https://www.youtube.com/watch?v=_WKrTkLdPdo

## Build
g++ -o RPGGame main.cpp BaseObject.cpp bullet.cpp Button.cpp Collision.cpp commonfunc.cpp enemy.cpp explosion.cpp game_map.cpp items.cpp menu.cpp mouse.cpp player.cpp Point.cpp TextObject.cpp timer.cpp Vector2D.cpp -ID:\Github\ProjectGroup21\RPGGame\LibSdl2\SDL2-2.0.8\include -ID:\Github\ProjectGroup21\RPGGame\LibSdl2\SDL2-2.0.8\lib\x86 -ID:\Github\ProjectGroup21\RPGGame\LibSdl2\SDL2_image-2.0.3\include -ID:\Github\ProjectGroup21\RPGGame\LibSdl2\SDL2_image-2.0.3\lib\x86 -ID:\Github\ProjectGroup21\RPGGame\LibSdl2\SDL2_mixer-2.0.2\include -ID:\Github\ProjectGroup21\RPGGame\LibSdl2\SDL2_mixer-2.0.2\lib\x86 -ID:\Github\ProjectGroup21\RPGGame\LibSdl2\SDL2_ttf-2.0.14\include -ID:\Github\ProjectGroup21\RPGGame\LibSdl2\SDL2_ttf-2.0.14\lib\x86


## Phân công công việc

### Nguyễn Minh Quân: Xử lý nhân vật, đường đạn, lưu trữ dữ liệu, các thông số game: hp, level, score

### Đinh Trung Kiên: Xử lí hiển thị text, xử lí các menu và giao diện, làm video demo

### Trần Hữu Thành: Xử lí collision: map, nhân vật, đạn bắn,...

