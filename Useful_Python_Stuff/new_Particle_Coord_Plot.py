# Import your libraries.

import matplotlib
import matplotlib.pyplot as plt
import uproot
import awkward as ak
import numpy as np

    # At the moment, "e_gun_config.py" is edited in PyCharm, then copied into and ran in WSL manually;
    # I need to figure out how to keep it all in one location for ease of use, if possible.
# The below values must be matched with "e_gun_config.py".
energy_val = 8 # Energy in GeV
event_total = 100 # Number of events
run_num = 1 # Run seed number.
root_path = rf"\\wsl.localhost\Ubuntu\home\chris\ldmx-sw-practice\test\{energy_val}GeV_samples/{event_total}_events/run{run_num}/e_gun_at_target_{energy_val}GeV_run{run_num}.root"

# Uproot the root file to make it readable by Python.
# You will need to change name and location accordingly.
with uproot.open(root_path) as file:
    tree = file["LDMX_Events;1"]

    # Open the data from the respective histograms as awkward arrays.
    x = tree["ecalTrigHits_test.position_x_"].array()
    y = tree["ecalTrigHits_test.position_y_"].array()
    z = tree["ecalTrigHits_test.position_z_"].array()
    layer = tree["ecalTrigHits_test.layer_"].array()
    e = tree["ecalTrigHits_test.energy_"].array()

    # For future reference, cluster variables, etc. are labeled with "c" at the beginning;
        # this is because it is nearly the same code and logic for the hits and clusters.
    cx = tree["ecalTrigClusters_test.x_"].array()
    cy = tree["ecalTrigClusters_test.y_"].array()
    cz = tree["ecalTrigClusters_test.z_"].array()
    ce = tree["ecalTrigClusters_test.e_"].array()

# Flatten to make readable; convert to numpy just for ease of use.
x_flat = ak.to_numpy(ak.flatten(x))
y_flat = ak.to_numpy(ak.flatten(y))
z_flat = ak.to_numpy(ak.flatten(z))
layer_flat = ak.to_numpy(ak.flatten(layer))
e_flat = ak.to_numpy(ak.flatten(e))

cx_flat = ak.to_numpy(ak.flatten(cx))
cy_flat = ak.to_numpy(ak.flatten(cy))
cz_flat = ak.to_numpy(ak.flatten(cz))
ce_flat = ak.to_numpy(ak.flatten(ce))


# Create event array in order to make mask.
event = ak.local_index(x, axis=0)
event = ak.broadcast_arrays(event, x)[0]
event_flat = ak.to_numpy(ak.flatten(event))

cevent = ak.local_index(cx, axis=0)
cevent = ak.broadcast_arrays(cevent, cx)[0]
cevent_flat = ak.to_numpy(ak.flatten(cevent))


# Create mask variables to show a range of specified layers within a range of specified events.
LEvent = 0
HEvent = 0
LLayer = 0
HLayer = 32
events_to_show = np.arange(LEvent,(HEvent+1))
layers_to_show = np.arange(LLayer,(HLayer+1))


# Create/instate mask using mask variables.
mask = (
    np.isin(event_flat, events_to_show)
    & np.isin(layer_flat, layers_to_show)
)
    # Note, there is no "layer" equivalent for the cluster centroids, hence the difference.
cmask = (
    np.isin(cevent_flat, events_to_show)
)

# Create figure and plot.
matplotlib.use('qtagg')
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

scatterParticles = ax.scatter(
    x_flat[mask],
    y_flat[mask],
    z_flat[mask],
#    layer_flat[mask],
    c=e_flat[mask],
    s=3,
    cmap='jet'
)
    # The above code plots the hits in the layer range and event range.
    # Note that "layer" can be replaced with "z" (or vice versa) in the scatterplot
        # but not in the preceding code. If done so, correct the plot labels below.

scatterClusters = ax.scatter(
    cx_flat[cmask],
    cy_flat[cmask],
    cz_flat[cmask],
    color='black',
    s=20
)

# Label the graph and colorbar.
ax.set_xlabel("x")
ax.set_ylabel("y")
ax.set_zlabel("z") # Make sure to match with what is shown in the scatterplot.
#ax.set_zlabel("Layer")
ax.set_title("Particle & Cluster Coordinate Plot")

cbar = plt.colorbar(scatterParticles)
cbar.set_label("Energy")

plt.show()
