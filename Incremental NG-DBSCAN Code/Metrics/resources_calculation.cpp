#include "sys/times.h"
#include "sys/vtimes.h"

static clock_t lastCPU, lastSysCPU, lastUserCPU;
static int numProcessors;
static unsigned long long lastTotalUser, lastTotalUserLow, lastTotalSys, lastTotalIdle;

int GetCPULoad() 
{
    fstream f;
    char FileBuffer[1024];
    float load;

    f.open("/proc/loadavg", ios::in);
    if(!f) {
        return -1; 
    }
    f.read(FileBuffer, sizeof(FileBuffer) - 1);
    sscanf(FileBuffer, "%f", &load);
    f.close();
    return (int)(load * 100);
}

int parseLine(char* line)
{
    // This assumes that a digit will be found and the line ends in " Kb".
    int i = strlen(line);
    const char* p = line;
    while (*p <'0' || *p > '9') p++;
    line[i-3] = '\0';
    i = atoi(p);
    return i;
}

int getValue_virtual_memory()
{   
    // Note: this value is in KB
    FILE* file = fopen("/proc/self/status", "r");
    int result = -1;
    char line[128];
    while(fgets(line, 128, file) != NULL){
        if(strncmp(line, "VmSize:", 7) == 0){
            result = parseLine(line);
            break;
        }
    }
    fclose(file);
    return result;
}

int getValue_physical_memory()
{   
    // Note: this value is in KB
    FILE* file = fopen("/proc/self/status", "r");
    int result = -1;
    char line[128];
    while(fgets(line, 128, file) != NULL)
    {
        if(strncmp(line, "VmRSS:", 6) == 0){
            result = parseLine(line);
            break;
        }
    }
    fclose(file);
    return result;
}