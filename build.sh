g++ main.cpp AllegroUtil.cpp -o linux/app \
$(pkg-config --cflags --libs allegro-5 allegro_primitives-5)