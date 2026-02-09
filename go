# DISPLAY=padev013:0.0
LD_LIBRARY_PATH=$DIR_OPENGL/lib:$LD_LIBRARY_PATH
echo ./test4 -S1 -F30 $*
# ./test4 -X1 -F10 -geometry 5x5+0+0 -s $*
# ../Debug/AsteroidFighter.exe -X1 -F10 -s  $*
# valgrind -v --tool=callgrind   --dump-instr=yes --simulate-cache=yes --collect-jumps=yes
#AsteroidFighter/AsteroidFighter  -f -X5 $*
cd Run && ../Debug/AWF.exe   $*
