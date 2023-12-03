# Made by a FIBER
# This program will play different matches with random seeds to allow
# you to test your program multiple times at once
#
# You may need to install ($pip3 install subprocess)
# To run it ($python3 multiple_games.py)

from subprocess import Popen, PIPE
import random
import os

def main():
    n_games = "50"
    p1 = "DM5"
    p2 = "Dummy"
    p3 = "Dummy"
    p4 = "Dummy"
    info = "y"
    victories = {p1:0, p2:0, p3:0, p4:0}
    print("\nPlaying... (this process might take some time)\n")
    for i in range(0, int(n_games)):
        n_random = random.randint(0, 100000000)
        nom_sortida = str(n_random)+".res"
        process = Popen(["./Game", p1, p2, p3, p4, "-s", str(n_random), "-i", "default.cnf", "-o", nom_sortida], stderr=PIPE)
        stderr = process.communicate()
        r = str(stderr).split()
        r = r[len(r)-6]
        if(info == "y"): print(str(i+1) + " of " + n_games + " played")
        victories[r] += 1
        os.remove(os.getcwd()+"/"+nom_sortida)

    print("\n----------------------")
    print("Victory rates:")
    print(p1 + " : " + str(100*(victories[p1]/int(n_games))) + " %")
    print(p2 + " : " + str(100*(victories[p2]/int(n_games))) + " %")
    print(p3 + " : " + str(100*(victories[p3]/int(n_games))) + " %")
    print(p4 + " : " + str(100*(victories[p4]/int(n_games))) + " %")
    print("----------------------\n")

if __name__ == "__main__":
	main()