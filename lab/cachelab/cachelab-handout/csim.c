#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>
#include <getopt.h>
#include <sys/types.h>
#include <sys/wait.h> // fir WEXITSTATUS
#include <limits.h> // for INT_MAX
#include "cachelab.h"

const int uint64_size = sizeof(uint64_t) << 3;

// the answer
static int hit_count = 0, miss_count = 0, eviction_count = 0;

typedef struct 
{
    int s;
    int E;
    int b;
    char * trace_file;
} Parm;

typedef struct
{
    uint64_t line_tag; 
    int is_vaild;
    int hit_count;
} Line;

typedef struct
{
    Line * set_line;
} Set;

typedef struct
{
    Set * cache_set;
    int S;
    int E;
    int B;
} Cache;

void usage(char *argv[]){
    printf("Usage: %s [-hv] -s <num> -E <num> -b <num> -t <file> \n", argv[0]);
    printf("Options:\n");
    printf("  -h         Print this help message. \n");
    printf("  -v         Optional verbose flag. \n");
    printf("  -s <num>   Number of set index bits. \n");
    printf("  -E <num>   Number of lines per set. \n");
    printf("  -b <num>   Number of block offset bits. \n");
    printf("  -t <file>  Trace file. \n\n");
    printf("Examples:\n");       
    printf("linux>  ./csim-ref -s 4 -E 1 -b 4 -t traces/yi.trace \n");       
    printf("linux>  ./csim-ref -v -s 8 -E 2 -b 4 -t traces/yi.trace \n");       
}

// Get option val and assgin to the struct Parm
void ReadOption(int argc, char * argv[], Parm * parm_value)
{
    char c;
    while ((c = getopt(argc,argv,"s:E:b:t:hv")) != -1) {
        switch(c) {
        case 's':
            parm_value->s = atoi(optarg);
            break;
        case 'E':
            parm_value->E = atoi(optarg);
            break;
        case 'b':
            parm_value->b = atoi(optarg);
            break;
        case 't':
            parm_value->trace_file = optarg;
            break;
        case 'v':
            usage(argv);
            exit(0);
        case 'h':
            usage(argv);
            exit(0);
        default:
            usage(argv);
            exit(1);
        }
    }
  
    if (parm_value->s == 0 || parm_value->b == 0 || parm_value->E == 0 || parm_value->trace_file == NULL) {
        printf("Error: Missing required argument\n");
        usage(argv);
        exit(1);
    }
}

Cache * InitCache(Parm * parm_value)
{
    Cache * cache = malloc(sizeof(Cache));
    cache->S = pow(2, parm_value->s);

    Set * set_array = malloc(sizeof(Set) * cache->S);
    for (int i = 0; i < cache->S; i++)
    {
        Line * line_array = malloc(sizeof(Line) * parm_value->E);
        for (int j = 0; j < parm_value->E; j++) 
        {
            line_array[j].line_tag = 0;
            line_array[j].is_vaild = 0;
        }

        set_array[i].set_line = line_array;
    }

    cache->cache_set = set_array;
    cache->E = parm_value->E;
    cache->B = pow(2, parm_value->b);
    return cache;
}

int GetSetIndexByAddr(uint64_t ref_addr, Parm * parm_value)
{
    ref_addr >>= parm_value->b;
    ref_addr &= ~((unsigned)-1 << parm_value->s);
    int addr_set = ref_addr;
    return addr_set;
}

Line * GetLRULine(Cache * cache, int set_index)
{
    assert(cache);
    assert(cache->E >= 1);

    Line * line_array = cache->cache_set[set_index].set_line;               
    Line * line_eviction = & line_array[0];

    for (int i = 1; i < cache->E ; i++)
    {
        if (line_array[i].hit_count < line_eviction->hit_count) 
        {
            line_eviction = & line_array[i];
        }
    }

    return line_eviction;
}

void Settle(int tmp_hit, int tmp_miss, int tmp_eviction)
{
    hit_count += tmp_hit;  
    miss_count += tmp_miss;  
    eviction_count += tmp_eviction;  
    printf("Hit %d , Miss %d , Eviction %d \n", tmp_hit, tmp_miss, tmp_eviction);
}

void Calculate(Cache * cache, char cmd_type, int addr_set, uint64_t addr_tag)
{
    assert(addr_set < cache->S);
    Set * set = & (cache->cache_set[addr_set]);
    Line * line_array = set->set_line, * line_eviction = NULL;
    int tmp_miss = 0, tmp_hit = 0, tmp_eviction = 0;
    
    for (int i = 0 ; i < cache->E; i++)
    {
        if (line_array[i].is_vaild == 0)
        {
            line_eviction = & (line_array[i]);
            continue;
        }

        if (line_array[i].line_tag == addr_tag)
        {
            tmp_hit += 1; 
            line_array[i].hit_count += 1; 
            printf(" set %d , tag %lx \n", addr_set, addr_tag);
            Settle(tmp_hit, tmp_miss, tmp_eviction);
            return;
        }
    }

    if (line_eviction == NULL)
    {
        tmp_eviction += 1;
        line_eviction = GetLRULine(cache, addr_set);
    }

    tmp_miss += 1;
    line_eviction->is_vaild = 1;
    line_eviction->line_tag = addr_tag;
    printf(" set %d , tag %lx \n", addr_set, addr_tag);

    Settle(tmp_hit, tmp_miss, tmp_eviction);
}

void SimByTraceFile(Cache * cache, Parm * parm_value)
{
    assert(parm_value);
    assert(cache);

    FILE* fp_trace_file = fopen(parm_value->trace_file, "r");
    assert(fp_trace_file);

    // read from file
    char cmd_type;
    uint64_t ref_addr = 0;
    int left_move_count = parm_value->s + parm_value->b;

    while(fscanf(fp_trace_file, " %c %lx,%*d", &cmd_type, &ref_addr) != EOF)
    {
        // ignore I 
        if (cmd_type == 'I')
        {
            continue;
        }

        printf("%c %lx \n", cmd_type, ref_addr); 
        int addr_set = GetSetIndexByAddr(ref_addr, parm_value);  
        uint64_t addr_tag = ref_addr >> left_move_count;
        //printf("set idx : %d , tag : %lx \n", addr_set, addr_tag); 
        
        Calculate(cache, cmd_type, addr_set, addr_tag);

        if (cmd_type == 'M')
        {
            Calculate(cache, cmd_type, addr_set, addr_tag);
        }
    }

    fclose(fp_trace_file);
}

int main(int argc, char * argv[])
{
    Parm * parm_value = malloc(sizeof(Parm));
    assert(parm_value);
    ReadOption(argc, argv, parm_value);


    Cache * cache = InitCache(parm_value);
    assert(cache);

    SimByTraceFile(cache, parm_value);
    printSummary(hit_count, miss_count, eviction_count);
    return 0;
}
