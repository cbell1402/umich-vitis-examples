import uproot
import numpy as np

energy_val = 8
event_total = 1
run_num = 1

root_path = (
    rf"\\wsl.localhost\Ubuntu\home\chris\ldmx-sw-practice"
    rf"\{energy_val}GeV_samples/{event_total}_events"
    rf"/run{run_num}/e_gun_at_target_{energy_val}GeV_run{run_num}.root"
)

with uproot.open(root_path) as file:
    tree = file["LDMX_Events;1"]

    tid = tree["ecalTrigDigis_test.tid_"].array()
    energy = tree["ecalTrigHits_test.energy_"].array()


NUM_LAYERS = 32
NUM_MODULES = 7
NUM_CELLS = 48

with open(f"module0_1event.txt", "w") as f:
    num_events = len(energy)
    for evt in range(num_events):
        event_data = np.zeros(
            (NUM_LAYERS, NUM_MODULES, NUM_CELLS),
            dtype=np.float32,
        )

        for hit in range(len(energy[evt])):
            raw_tid = int(tid[evt][hit])

            cell = raw_tid & 0x7F
            module = (raw_tid >> 7) & 0x1F
            layer = (raw_tid >> 12) & 0x3F

            if (
                0 <= layer < NUM_LAYERS
                and 0 <= module < NUM_MODULES
                and 0 <= cell < NUM_CELLS
            ):
                event_data[layer][module][cell] = float(energy[evt][hit])

        for layer in range(NUM_LAYERS):
            module = 0          # only the first module
            for cell in range(NUM_CELLS):
                f.write(f"{event_data[layer, module, cell]:.6f}\n")

print(f"Wrote {num_events} events.")
print(f"Each event contains {NUM_LAYERS * NUM_MODULES * NUM_CELLS} energy values.")