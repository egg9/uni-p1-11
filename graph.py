from matplotlib.animation import FuncAnimation
import matplotlib.pyplot as plt
import random
import threading
import sys

# initial data
x = [] # days
y = [[] for _ in range(8)] # array of stats_t array that will save the stats_t struct comming from c

stats_t_enum = {
    "susceptible": 0,
    "infectious": 1,
    "recovered": 2,
    #
    "recovery_rate": 3,
    "transmission_rate": 4,
    "immunity_wane": 5,
    #
    "duration": 6,
    "R_t": 7
}
changed = False



# creating the first plot and frame
fig, ax = plt.subplots()
graphs = [
    ax.plot([], [], color = 'b', label = "susceptible")[0],
    ax.plot([], [], color = 'g', label = "infectious")[0],
    ax.plot([], [], color = 'r', label = "recovered")[0],
    ax.plot([], [], color = 'orange', label = "R_t")[0]
]
ax.legend(loc="upper right")
plt.ylim(0, 100)




def read_stdio():
    global changed

    for str_pipe in sys.stdin:
        inputs = str_pipe.replace("\n", " \n").split(" ")

        if (len(inputs) != 8):
            changed = True
            for i, input in enumerate( inputs ):

                if input != "\n":
                    # updating the data
                    y[i].append( float( input ) )
            x.append(len(x))

    plt.close('all')
    sys.exit(0)



    sys.stdin.flush()

threading.Thread(target = read_stdio, daemon=True ).start()


# updates the data and graph
def update(frame):
    global graphs
    global x
    global y
    global changed


    if changed:

        # creating a new graph or updating the graph
        for i in range( len( graphs ) ):

            graphs[i].set_xdata(x)
            graphs[i].set_ydata(y[i])

        plt.xlim(0, x[-1])

        changed = False

anim = FuncAnimation(fig, update, interval=200, frames = None)
plt.show()