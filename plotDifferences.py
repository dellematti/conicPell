import matplotlib.pyplot as plt
import numpy as np
from matplotlib import colors
from matplotlib.ticker import PercentFormatter
import matplotlib.ticker as ticker



with open('time512bitC.txt', 'r') as file:
    # Read each line in the file
    sum = 0
    arr=[0]
    for line in file:
        #arr.append( int(line.strip())/10 )
        arr.append( float(line.strip()))
f = np.array(arr)        



# modo per vedere il numero ideale di bins (Freedman–Diaconis number of bins)
q25, q75 = np.percentile(f, [25, 75])
bin_width = 2 * (q75 - q25) * len(f) ** (-1/3)
n_bins = round((f.max() - f.min()) / bin_width)

# se invece voglio un bin per millisecondo
n_bins=17


fig, axs = plt.subplots(1, 2, tight_layout=True)


# ########## grafico sinistra (C)


# N is the count in each bin, bins is the lower-limit of the bin
N, bins, patches = axs[0].hist(f, bins=n_bins, density=True)
# We'll color code by height, but you could use any scalar
fracs = N / N.max()
# we need to normalize the data to 0..1 for the full range of the colormap
norm = colors.Normalize(fracs.min(), fracs.max())
# Now, we'll loop through our objects and set the color of each accordingly
for thisfrac, thispatch in zip(fracs, patches):
    color = plt.cm.viridis(norm(thisfrac))
    thispatch.set_facecolor(color)





# ##########    grafico destra (python)
# axs[1].hist(f, bins=n_bins, density=True)


N2, bins2, patches2 = axs[1].hist(f, bins=n_bins, density=True)
fracs2 = N2 / N2.max()
norm2 = colors.Normalize(fracs2.min(), fracs2.max())
for thisfrac, thispatch in zip(fracs2, patches2):
    color2 = plt.cm.viridis(norm(thisfrac))
    thispatch.set_facecolor(color2)




# setto i ticks a 5
axs[0].xaxis.set_major_locator(ticker.MultipleLocator(5))
axs[1].xaxis.set_major_locator(ticker.MultipleLocator(5))






# Now we format the y-axis to display percentage
axs[0].yaxis.set_major_formatter(PercentFormatter(xmax=1))
axs[1].yaxis.set_major_formatter(PercentFormatter(xmax=1))

plt.show()