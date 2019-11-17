import numpy as np
import matplotlib.pyplot as plt
import matplotlib.patches as mpatches
import matplotlib.animation as anim
import sys

def collatz_mapper(amax, bmax, div=2, nlim=20):
    """
    Returns a Numpy array with the Collatz Map. Utilizes ints to build the map.

    Parameters
    ----------
    amax: int
        Maximum positive 'a' value of the map (horizontal axis). The map goes
        from -amax to amax.
    bmax: int
        Maximum positive 'b' value of the map (vertical axis). The map goes
        from -bmax to bmax.
    div: int
        Divisor for the generalized Collatz Problem.
    nlim: int
        Maximimum number of integers to search for convergence.
    """
    a_range = range(-amax, amax)
    b_range = range(-bmax,bmax)
    d = div

    collatz_map = np.zeros((len(b_range), len(a_range)))

    n_currs = range(1,nlim+1)
    n_min_init = 999999 #initialization value for n_min, so that it is bigger than n_curr
    n_max = 1000000000
    calc_steps = 10
    max_mini_steps = 100 #maximum steps in collatz sequence to check for convergence
    escape_value = np.pi #value given to list of fixed points if number of steps exceded.

    for a in a_range:
        for b in b_range:
            min_fix = []
            for n_curr in n_currs:
                #print('a, b, n = ',a, b, n_curr)
                step = 1
                escaped = False
                for _ in range(calc_steps):
                    if n_curr%d == 0:
                        if n_curr == 0:
                           n_min = 0
                           break
                        else:
                           n_curr = n_curr // d
                    else:
                        n_curr = a*n_curr + b
                n_min = n_curr + n_min_init
                while n_min != n_curr:
                    #print('n_curr=', n_curr, ', n_min=', n_min)
                    n_min = min(n_min, n_curr)
                    if n_curr%d == 0:
                        if n_curr == 0:
                           n_min = 0
                           break
                        else:
                           n_curr = n_curr // d
                    else:
                        n_curr = a*n_curr + b
                    step += 1
                    if step > max_mini_steps or abs(n_curr) > n_max:
                        #print('escaped')
                        escaped = True
                        break
                if escaped:
                    min_fix.append(escape_value)
                    escaped = False
                else:
                    min_fix.append(n_min)
            #adding point to map
            min_fix_setlist = list(set(min_fix))
            if np.pi in min_fix_setlist:
                if [np.pi]==min_fix_setlist:
                    collatz_map[b + bmax, a + amax] = 0
                else:
                    collatz_map[b + bmax, a + amax] = 1
            else:
                if len(min_fix_setlist) == 1:
                    collatz_map[b + bmax, a + amax] = 3
                else:
                    collatz_map[b + bmax, a + amax] = 2
    #
    return collatz_map
#
def collatz_plotter(col_map, div = 0, cmap='inferno', legend=True):
    """
    Plots the collatz map.

    Parameters
    ----------
    colmap: numpy array
        Contains the map.
    div: int
        Used as figure number and for filename if empty.
    save_fig: boolean
        Declares whether to save the figure or not.
    savename: string
        Name of the file where figure will be saved.
    cmap: string or colormap
        Set by default to 'inferno'.
    """
    if div==0:
        fig = plt.figure()
        div = ''
    else:
        fig = plt.figure(div)
    ax=fig.add_subplot(1,1,1)
    values = np.unique(col_map)
    image = plt.imshow(col_map, cmap=cmap)
    colors = [image.cmap(image.norm(value)) for value in values]
    labels = ['no convergence', 'convergence for some', 'convergence for all at diff', 'convergence for all at same']
    patches = [mpatches.Patch(color=colors[i], label=labels[i]) for i in range(len(values))]
    if legend:
        plt.legend(handles=patches, bbox_to_anchor=(1.05, 1), loc=2, borderaxespad=0.)
    if div!=0:
        plt.title('divisor = '+str(div))
    plt.axis('off')
    plt.show()
#
def collatz_animation(amax, bmax, div):
    """
    Returns an animation object and saves it as Gif.
    """
    pass
#
if __name__ == '__main__':
    int_parameters = []
    for arg in sys.argv[1:]:
        int_parameters.append(int(arg))
    if all([type(elem)==int for elem in int_parameters]):
        amax, bmax, div, nlim = int_parameters[:4]
    else:
        amax, bmax, div, nlim = eval(input('enter all ints with commas: amax, bmax, div, nlim\n'))
    #amax, bmax, div, nlim = 1024, 1024, 2, 20
    print('parameters: amax=', amax, ', bmax=',bmax, ', div=',div, ', nlim=',nlim)
    collatz_map = collatz_mapper(amax, bmax, div, nlim)
    #Save collatz map to file
    filename = 'collatz_map_a'+str(amax)+'_b'+str(bmax)+'_div'+str(div)+'.colmap'
    with open(filename, 'w') as file:
        for row in range(2*amax):
            for column in range(2*bmax):
                file.write(str(collatz_map[row,column])+'\t')
            file.write('\n')
    #
    collatz_plotter(collatz_map, div)
