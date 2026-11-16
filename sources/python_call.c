#include "../headers/python_call.h"

#ifdef _WIN32
#define PLOT_CMD "python graph.py 2>nul"
#define popen _popen
#define pclose _pclose
#else
#define PLOT_CMD "python3 graph.py 2>/dev/null"
#endif

static FILE *graph = NULL;

void open_graph()
{

    graph = popen(PLOT_CMD, "w");
    if (!graph)
    {
        fprintf(stderr, "Can't open graph");
        exit(1);
        return;
    }
    return;
}

void append_day_graph(stats_t st)
{
    double total_population = st.susceptible + st.infectious + st.recovered;
    printf("%lf", total_population);
    fprintf(graph, "%lf %lf %lf %lf %lf %lf %d %lf\n", st.susceptible / total_population * 100, st.infectious / total_population * 100, st.recovered / total_population * 100, st.recovery_rate, st.transmission_rate, st.immunity_wane, st.duration, st.R_t);
    if (fflush(graph) != 0)
    {
        fprintf(stderr, "Can't see the graph, starting a new session");

        open_graph();
    }
}

bool close_graph()
{
    if (graph != NULL)
    {
        pclose(graph);
        return true;
    }
    return false;
}