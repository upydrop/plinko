g++ ^
engine.cpp main.cpp field/Circle.cpp consts.hpp field/WinBox.cpp generator.cpp controls/Button.cpp controls/InputField.cpp controls/Dropdown.cpp controls/ParameterBox.cpp field/LastWins.cpp ^
-o bin/app ^
-std=c++17 -Iallegro/include -Lallegro/lib ^
-lallegro -lallegro_main -lallegro_primitives ^
-lallegro_image ^
-lallegro_font ^
-lallegro_ttf ^