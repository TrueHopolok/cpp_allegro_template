g++ src/example_engine_3.cpp src/engine.cpp \
-o build/linux/program \
-std=c++17 \
$(pkg-config --cflags --libs allegro-5 allegro_primitives-5 allegro_image-5 allegro_font-5 allegro_ttf-5)