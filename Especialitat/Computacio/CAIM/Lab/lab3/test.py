import os
import math
import pandas as pd
from collections import defaultdict
from random import sample

file_path = "arxiv"
list_dirs = os.listdir(file_path)
list_files = []
aux = []
for dir_name in list_dirs:
    dir_path = os.path.join(file_path, dir_name)
    if os.path.isdir(dir_path):
        for filename in os.listdir(dir_path):
            full_path = os.path.join(dir_name, filename)
            aux.append(full_path)
    list_files.append(sample(aux, 200))
    aux = []

print(len(list_files))
