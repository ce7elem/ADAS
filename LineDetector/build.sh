echo "BUILDING Main.cpp"
g++ $(pkg-config --cflags --libs opencv) -Ofast -march=native -std=c++11 main.cpp -o main
echo "END"
