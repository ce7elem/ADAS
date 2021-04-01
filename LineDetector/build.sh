echo "BUILDING Main.cpp"
g++ $(pkg-config --cflags --libs opencv) -std=c++11  main.cpp -o main
echo "END"
