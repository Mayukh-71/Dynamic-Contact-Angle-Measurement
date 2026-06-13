import pandas as pd
import matplotlib.pyplot as plt
# ==========================================
# USER SETTINGS
# ==========================================
filename = "Height close to the surface"
csv_file = "Output/" + filename + ".csv"
start_row = 388
end_row   = 2000
# ==========================================
df = pd.read_csv(csv_file)
df["AverageAngle"] = pd.to_numeric(df["AverageAngle"],errors="coerce")
# Select desired rows
df = df.iloc[start_row-1:end_row]
# Plot
plt.figure(figsize=(10,6))
plt.scatter(df["Time"],df["AverageAngle"],s=10)
plt.xlabel("Time (s)")
plt.ylabel("Average Angle (deg)")
plt.title("Average Contact Angle vs Time")
plt.grid(True)
plt.savefig(("Output/" + filename + ".png"),dpi=300,bbox_inches="tight")
#plt.tight_layout()
plt.show()