#include "utils.h"

struct ins *ins = NULL;
int main(int argc, char *argv[])
{
    ins = (struct ins *) malloc(sizeof(struct ins));
    int count = 0;
    while (count < 20) {
        inst_cycle();
        count ++;
    }
    free(ins);
    return 0;
}