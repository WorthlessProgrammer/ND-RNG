import numpy as np
from matplotlib import pyplot as plt

def plotData(x: np.array) -> None:
    print(x.std())

if __name__ == "__main__":
    x = np.array([69, 70, 67, 72, 67, 72, 72, 67, 72, 67, 72, 67, 67, 72, 67, 72, 72, 67, 67, 72, 67, 72, 67, 72, 71])
    plotData(x)
