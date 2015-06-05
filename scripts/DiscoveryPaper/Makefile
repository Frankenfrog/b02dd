CC=c++
CXX=c++
LD=c++
CFLAGS=-std=c++11 -Wno-deprecated-declarations -m64 -I/afs/cern.ch/sw/lcg/releases/LCG_69root6/ROOT/6.00.02/x86_64-slc6-gcc48-opt/include -g
CXXFLAGS=-std=c++11 -Wno-deprecated-declarations -m64 -I/afs/cern.ch/sw/lcg/releases/LCG_69root6/ROOT/6.00.02/x86_64-slc6-gcc48-opt/include -O2 -march=native -ffast-math -fno-finite-math-only -g
LDFLAGS=-L/afs/cern.ch/sw/lcg/releases/LCG_69root6/ROOT/6.00.02/x86_64-slc6-gcc48-opt/lib -lCore -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -lm -ldl -rdynamic -O2 -march=native -ffast-math -fno-finite-math-only -g

derived: derived.o b2dd.o

derived.o: derived.cpp derived.h b2dd.h

