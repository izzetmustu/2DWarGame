add_library(lib Barrel.cpp Bullet.cpp BulletList.cpp Coord.cpp Game.cpp Object.cpp Player.cpp Sandbag.cpp)
add_executable(main main.cpp)

# Find SFML
find_package(SFML 2.5.1 COMPONENTS graphics window system REQUIRED)

target_link_libraries(main PUBLIC lib sfml-graphics sfml-window sfml-system)