#include <vector>

#define BLOCK_I_TYPE 1
#define BLOCK_O_TYPE 2
#define BLOCK_T_TYPE 3
#define BLOCK_J_TYPE 4
#define BLOCK_L_TYPE 5
#define BLOCK_S_TYPE 6
#define BLOCK_Z_TYPE 7

const std::vector<std::vector<int>> block_I = {
    {0,0,0,0},
    {1,1,1,1},
    {0,0,0,0},
    {0,0,0,0}
};

const std::vector<std::vector<int>> block_O = {
    {0,0,0,0},
    {0,1,1,0},
    {0,1,1,0},
    {0,0,0,0}
};

const std::vector<std::vector<int>> block_T = {
    {0,0,0,0},
    {1,1,1,0},
    {0,1,0,0},
    {0,0,0,0}
};

const std::vector<std::vector<int>> block_J = {
    {0,0,0,0},
    {1,1,1,0},
    {0,0,1,0},
    {0,0,0,0}
};

const std::vector<std::vector<int>> block_L = {
    {0,0,0,0},
    {1,1,1,0},
    {1,0,0,0},
    {0,0,0,0}
};

const std::vector<std::vector<int>> block_S = {
    {0,0,0,0},
    {0,1,1,0},
    {1,1,0,0},
    {0,0,0,0}
};

const std::vector<std::vector<int>> block_Z = {
    {0,0,0,0},
    {1,1,0,0},
    {0,1,1,0},
    {0,0,0,0}
};
