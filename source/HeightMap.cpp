#include "HeightMap.h"
#include "WorldGen.h"
#include <algorithm>

namespace World {

    void HeightMap::setSize(int s) {
        size = s;
        size2 = size * size;
    }

    void HeightMap::create() {
        array = new int[size2];
        std::fill_n(array, size2, -1);
    }

    void HeightMap::destroy() {
        delete[] array;
        array = nullptr;
    }

    void HeightMap::move(int xd, int zd) {
        int* arrTemp = new int[size2];
        for (int x = 0; x < size; x++) {
            for (int z = 0; z < size; z++) {
                if (x + xd >= 0 && z + zd >= 0 && x + xd<size && z + zd<size)
                    arrTemp[x*size + z] = array[(x + xd)*size + (z + zd)];
                else arrTemp[x*size + z] = -1;
            }
        }
        delete[] array;
        array = arrTemp;
        originX += xd; originZ += zd;
    }

    void HeightMap::moveTo(int x, int z) {
        move(x - originX, z - originZ);
    }

    int HeightMap::getHeight(int x, int z) {
        x -= originX; z -= originZ;
        if (x < 0 || z < 0 || x >= size || z >= size)
            return WorldGen::getHeight(x + originX, z + originZ);
        if (array[x*size + z] == -1)
            array[x*size + z] = WorldGen::getHeight(x + originX, z + originZ);
        return array[x*size + z];
    }
}