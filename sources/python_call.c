#include "../headers/python_call.h"

static FILE *graph = NULL;

void open_graph()
{
    graph = popen("python graph.py 2>nul", "w");
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
    int total_population = st.susceptible + st.infectious + st.recovered;
    fprintf(graph, "%lf %lf %lf %lf %lf %lf %d %lf\n", total_population / st.susceptible, total_population / st.infectious, total_population / st.recovered, st.recovery_rate, st.transmission_rate, st.immunity_wane, st.duration, st.R_t);
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