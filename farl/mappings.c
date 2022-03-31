#include "mappings.h"

static struct btree* mapping_tree = NULL;

struct node {
    char* virtual_path;
    char* physical_path;
};

int node_compare(const void* a, const void* b, void* udata)
{
    const struct node* na = a;
    const struct node* nb = b;

    return strcmp(na->virtual_path, nb->virtual_path);
}

bool node_iter(const void* a, void* udata)
{
    const struct node* na = a;
    lprintf("%s: %s", na->virtual_path, na->physical_path);
    return true;
}

bool node_free_string_memory(const void* a, void* udata)
{
    const struct node* na = a;
    free(na->physical_path);
    free(na->virtual_path);
    return true;
}

char* resolve_path(char* path)
{
    char* output;

    if ((output = realpath(path, NULL)) == NULL)
    {
        size_t path_length = strlen(path) + 1;
        output = (char*)malloc(path_length * sizeof(char));
        strncpy(output, path, path_length);
    }

    #ifdef FARL_LOG_PATHS
    lprintf("path: \"%s\" -> \"%s\"", path, output);
    #endif

    return output;
}

void load_mappings(void)
{
    discard_mappings();

    char* mappings_path = getenv(FARL_MAPPINGS_ENVVAR);

    if (mappings_path == NULL){
        lprintf("no mappings file path provided");
        exit(EXIT_FAILURE);
    }

    mappings_path = resolve_path(mappings_path);

    lprintf("loading mappings from \"%s\"", mappings_path);

    FILE* fp;

    mapping_tree = btree_new(sizeof(struct node), 0, node_compare, NULL);

    atexit(discard_mappings);

    if ((fp = fopen(mappings_path, "r")) == NULL)
    {
        lprintf("failed to open mappings file");
        exit(EXIT_FAILURE);
    }

    char* line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, fp)) != -1)
    {
        char* separator;

        if ((separator = strstr(line, ": ")) != NULL)
        {
            // the line being parsed basically looks like:
            //  /physical/path.ext: /virtual/path.ext\n
            // |                 | |                ||
            // 0 <------------> 18 20 <----------> 37|
            //         |          |        |         |
            //     physical      sep    virtual    newline
            //        18          2        17         1     = 38
            //
            // separator index = 18
            // physical length = 18 - 0              = 18
            // virtual length  = 38 - 0 - 18 - 2 - 1 = 17

            *separator = '\0';  // replace colon with end of string
            *(line + read - 1) = '\0';  // replace newline with end of string

            struct node* temp_node = &(struct node) {
                .physical_path=resolve_path(line),
                .virtual_path=resolve_path(separator + 2)
            };

            #ifdef FARL_LOG_BUILDING
            lprintf("map: \"%s\" -> \"%s\"", temp_node->virtual_path, temp_node->physical_path);
            #endif

            // free the previous mapping node if one is found
            if ((temp_node = btree_set(mapping_tree, temp_node)) != NULL)
            {
                free(temp_node);
            }
        }
    }

    fclose(fp);

    if (line)
    {
        free(line);
    }

    lprintf("loaded %d mappings", btree_count(mapping_tree));
}

void discard_mappings(void)
{
    lprintf("discarding existing mappings");

    if (mapping_tree != NULL)
    {
        btree_descend(mapping_tree, NULL, node_free_string_memory, NULL);
        btree_free(mapping_tree);
        lprintf("mappings discarded");
    }
    else
    {
        lprintf("no mappings to discard");
    }
}

char* map_path(char* virtual_path)
{
    struct node* match = btree_get(mapping_tree, &(struct node){ .virtual_path=virtual_path });

    #ifdef FARL_LOG_RESOLVING
    lprintf("resolve: \"%s\" -> \"%s\"", virtual_path, match ? match->physical_path : NULL);
    #endif

    return match ? match->physical_path : NULL;
}
