#include <stdio.h>
#include "../farl/mappings.h"

int main(void)
{
    printf("TEST: running\n");

    printf("TEST: logfile: \"%s\"\n", getenv("FARL_LOG"));
    printf("TEST: mappings: \"%s\"\n", getenv("FARL_MAPPINGS"));

    printf("TEST: loading mappings...\n");

    load_mappings();

    printf("TEST: done, checking paths...\n");

    map_path("/some/random/path/a_virt.txt");
    map_path("/some/random/path/b_fake.txt");

    printf("TEST: finished, quitting\n");

    exit(EXIT_SUCCESS);
}
